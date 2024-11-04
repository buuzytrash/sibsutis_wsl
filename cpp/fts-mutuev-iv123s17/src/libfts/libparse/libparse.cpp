#include <libfts/libparse.hxx>

namespace common {
NgramParser::NgramParser(const std::string& t_configPath)
    : configPath(std::move(t_configPath)) {
  XML doc;
  if (!doc.load_file(configPath.c_str())) {
    std::cout << "Failed to load config.xml" << std::endl;
    return;
  }

  pugi::xml_node parserNode = doc.child("fts").child("parser");
  minNgramlength = parserNode.attribute("ngram_min_length").as_uint();
  maxNgramlength = parserNode.attribute("ngram_max_length").as_uint();

  pugi::xml_node stopWordsNode = parserNode.child("stop_words");
  for (auto wordNode : stopWordsNode.children("word")) {
    stopWords.push_back(wordNode.child_value());
  }
}

NgramParser::NgramParser() {
  XML doc;
  if (!doc.load_file(configPath.c_str())) {
    std::cout << "Failed to load config.xml" << std::endl;
    return;
  }

  pugi::xml_node parserNode = doc.child("fts").child("parser");
  minNgramlength = parserNode.attribute("ngram_min_length").as_uint();
  maxNgramlength = parserNode.attribute("ngram_max_length").as_uint();

  pugi::xml_node stopWordsNode = parserNode.child("stop_words");
  for (auto wordNode : stopWordsNode.children("word")) {
    stopWords.push_back(wordNode.child_value());
  }
}

Map NgramParser::parse(const std::string& s_text) const {
  std::string text = (std::move(s_text));

  // rmPunct();
  auto it = std::remove_if(text.begin(), text.end(), ::ispunct);
  text.erase(it, text.end());

  // convToLowCase();
  std::transform(text.begin(), text.end(), text.begin(), [](unsigned char c) {
    return std::tolower(c);
  });

  // splitWords();
  Words words;

  std::istringstream iss(text);
  std::string str;
  while (iss >> str) {
    words.push_back(str);
  }
  // rmstopWords();
  words.erase(
      std::remove_if(
          words.begin(),
          words.end(),
          [this](const std::string& word) {
            return std::find(stopWords.begin(), stopWords.end(), word) !=
                stopWords.end();
          }),
      words.end());

  // generateNgrams();
  size_t t = 0;
  Map ngrams;

  for (const auto& word : words) {
    for (auto i = minNgramlength; i <= maxNgramlength; i++) {
      std::string ngram = word.substr(0, i);
      ngrams[ngram].push_back(t);
      if (i == word.length() && maxNgramlength > word.length()) {
        break;
      }
    }
    t++;
  }
  return ngrams;
}

void NgramParser::printRes(const Map& ngrams) {
  for (const auto& ngram : ngrams) {
    std::cout << "NGram: " << ngram.first << ", Positions: ";
    for (const auto& position : ngram.second) {
      std::cout << position << " ";
    }
    std::cout << std::endl;
  }
}

}  // namespace common