#include <cxxopts.hpp>
#include <libfts/libindex.hxx>
#include <libfts/libparse.hxx>
#include <libfts/libsearcher.hxx>
#include <pugixml.hpp>
#include <replxx.hxx>

int main(int argc, char** argv) {
  cxxopts::Options options("textparser");
  try {
    options.add_options()(
        "text",
        "Enable text",
        cxxopts::value<std::string>()->default_value(""))(
        "config",
        "Enable config",
        cxxopts::value<std::string>()->default_value("config.xml"))(
        "query", "Enable your query", cxxopts::value<std::string>());
    const auto result = options.parse(argc, argv);
    if (result.count("text") != 1 && result.count("query") != 1) {
      std::cout << options.help() << "\n";
      return 0;
    }

    std::string s_text = result["text"].as<std::string>();
    std::string config = result["config"].as<std::string>();
    std::string user_query = result["query"].as<std::string>();

    // common::Map ngram;
    // common::NgramParser NgramParser(config);
    //   ngram = NgramParser.parse(s_text);

    // NgramParser.printRes(ngram);

    auto index_build = std::make_shared<indexer::IndexBuilder>(config);
    std::vector<std::string> docums = {
        "Harry Potter and the Half-Blood Prince",
        "Harry Potter and the Order of the Phoenix",
        "You Suck ",
        "The Hitchhiker's Guide to the Galaxy",
        "Alice's Adventures in Wonderland & Through the Looking",
        "Hello world Mr. Jeckson trivia Hello world Mr. Jeckson borrowed "
        "trivia"};
    for (int i = 0; i < 6; i++) {
      index_build->AddDocument(i, docums[i]);
    }

    auto writter = std::make_shared<indexer::TextIndexWriter>();
    writter->Write("./index", index_build->GetIndex());

    common::NgramParser parser("config.xml");
    searcher::TextIndexAccessor index_accessor("./index");

    auto PrintResult = [&](const std::string& query) {
      auto search_result = searcher::Search(parser, index_accessor, query);
      std::cout << "id\tscore\ttext" << std::endl;
      for (const auto& result : search_result) {
        std::cout << result.document_id << "\t" << result.score << "\t"
                  << result.name_of_doc << std::endl;
      }
    };

    if (user_query.empty()) {
      replxx::Replxx editor;
      editor.clear_screen();
      while (true) {
        const char* input{nullptr};
        do {
          input = editor.input("> ");
        } while ((input == nullptr) && (errno == EAGAIN));

        if (std::strcmp(input, "!exit") == 0) {
          break;
        }

        std::string query{input};
        if (query.empty()) {
          continue;
        }

        try {
          PrintResult(query);
        } catch (const std::exception& e) {
          std::cerr << e.what() << std::endl;
        }
      }
    } else {
      PrintResult(user_query);
    }

  } catch (const std::exception& error) {
    std::cerr << error.what() << std::endl;
    return 1;
  }
  return 0;
}