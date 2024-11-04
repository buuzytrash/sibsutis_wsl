#pragma once
#include <algorithm>
#include <cctype>
#include <cstring>
#include <iostream>
#include <pugixml.hpp>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace common {

using Word = std::string;
using Words = std::vector<Word>;
using WordIndex = std::vector<std::size_t>;
using Map = std::unordered_map<Word, WordIndex>;
using XML = pugi::xml_document;

class Parser {
 public:
  virtual Map parse(const std::string& s_text) const = 0;
  virtual ~Parser() = default;
};

class NgramParser : public Parser {
 private:
  Words stopWords;
  size_t minNgramlength;
  size_t maxNgramlength;
  std::string configPath = "../../../../config.xml";

 public:
  NgramParser();
  explicit NgramParser(const std::string& t_configPath);
  Map parse(const std::string& s_text) const override;
  void printRes(const Map& ngrams);
  ~NgramParser() override = default;
};
}  // namespace common