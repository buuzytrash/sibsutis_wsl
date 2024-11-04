#include <algorithm>
#include <cctype>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class TextParser
{
public:
  TextParser (const std::string &text,
              const std::vector<std::string> &stopWords, size_t minNgramLength,
              size_t maxNgramLength)
      : text (text), stopWords (stopWords), minNgramLength (minNgramLength),
        maxNgramLength (maxNgramLength)
  {
  }

  void
  parseText ()
  {
    removePunctuation ();
    convertToLowerCase ();
    splitIntoWords ();
    removeStopWords ();
    generateNGrams ();
  }

  void
  printResult ()
  {
    for (const auto &ngram : ngrams)
      {
        std::cout << ngram.first << " ";
        for (const auto &position : ngram.second)
          {
            std::cout << position << " ";
          }
      }
    std::cout << std::endl;
  }

private:
  std::string text;
  std::vector<std::string> stopWords;
  size_t minNgramLength;
  size_t maxNgramLength;
  std::vector<std::string> words;
  std::unordered_map<std::string, std::vector<int> > ngrams;

  void
  removePunctuation ()
  {
    auto it = std::remove_if (text.begin (), text.end (), ::ispunct);
    text.erase (it, text.end ());
  }

  void
  convertToLowerCase ()
  {
    std::transform (text.begin (), text.end (), text.begin (),
                    [] (unsigned char c) { return std::tolower (c); });
  }

  void
  splitIntoWords ()
  {
    std::istringstream iss (text);
    std::string word;
    while (iss >> word)
      {
        words.push_back (word);
      }
  }

  void
  removeStopWords ()
  {
    words.erase (std::remove_if (words.begin (), words.end (),
                                 [this] (const std::string &word) {
                                   return std::find (stopWords.begin (),
                                                     stopWords.end (), word)
                                          != stopWords.end ();
                                 }),
                 words.end ());
  }

  void
  generateNGrams ()
  {
    int t = 0;

    for (const std::string &word : words)
      {
        for (auto i = minNgramLength; i <= maxNgramLength; i++)
          {

            std::string ngram = word.substr (0, i);
            ngrams[ngram].push_back (t);
            if (i == word.length () && maxNgramLength > word.length ())
              {
                break;
              }
          }
        t++;
      }
  }
};

int
main ()
{
  std::string text = "Dr. Jekyll and Mr. Hyde      jekyll";
  std::vector<std::string> stopWords = { "and", "dr", "mr" };
  size_t minNgramLength = 3;
  size_t maxNgramLength = 6;

  TextParser parser (text, stopWords, minNgramLength, maxNgramLength);
  parser.parseText ();
  parser.printResult ();

  return 0;
}