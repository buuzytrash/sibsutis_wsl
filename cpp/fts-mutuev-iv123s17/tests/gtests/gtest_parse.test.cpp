#include <gtest/gtest.h>
#include <libfts/libparse.hxx>
#include <pugixml.hpp>

TEST(FuncGetNgrams, CorrectNgrams) {
  common::Map ngram;
  std::string text =
      "THE CP,p i!!??S !LANGUage!  i!s t.he?  ,bE!s?t, the l!ANG&ua,ge ";
  common::NgramParser test_parser;
  ngram = test_parser.parse(text);
  test_parser.printRes(ngram);

  common::Map map{
      {"best", {2}},
      {"langua", {1, 3}},
      {"langu", {1, 3}},
      {"lang", {1, 3}},
      {"lan", {1, 3}},
      {"bes", {2}},
      {"cpp", {0}}};

  EXPECT_EQ(ngram, map);
}