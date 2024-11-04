#include <rapidcsv.h>
#include <cxxopts.hpp>
#include <libfts/libindex.hxx>
#include <libfts/libparse.hxx>
#include <libfts/libsearcher.hxx>
#include <pugixml.hpp>
#include <replxx.hxx>

struct SearchOpt {
  std::filesystem::path path_to_index;
  std::filesystem::path path_to_config;
  std::string query;
};

int main(int argc, char** argv) {
  cxxopts::Options options("searcher");
  try {
    options.add_options()(
        "index", "Enable index", cxxopts::value<std::string>())(
        "config",
        "Enable config",
        cxxopts::value<std::string>()->default_value("config.xml"))(
        "query",
        "Enable your query",
        cxxopts::value<std::string>()->default_value(""));

    const auto result = options.parse(argc, argv);
    if (result.count("index") != 1) {
      std::cout << options.help() << "\n";
      return 0;
    }

    auto opt = std::make_shared<SearchOpt>();
    opt->path_to_index = result["index"].as<std::string>();
    opt->query = result["query"].as<std::string>();
    if (result.count("config") != 1) {
      opt->path_to_config = "../../../../config.xml";
    } else {
      opt->path_to_config = result["config"].as<std::string>();
    }

    common::NgramParser parser(opt->path_to_config);
    searcher::TextIndexAccessor index_accessor(opt->path_to_index);

    auto PrintResult = [&](const std::string& query) {
      auto search_result = searcher::Search(parser, index_accessor, query);
      std::cout << "id\tscore\ttext" << std::endl;
      for (const auto& result : search_result) {
        std::cout << result.document_id << "\t" << result.score << "\t"
                  << result.name_of_doc << std::endl;
      }
    };

    if (opt->query.empty()) {
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
      PrintResult(opt->query);
    }

  } catch (const std::exception& error) {
    std::cerr << error.what() << std::endl;
    return 1;
  }
  return 0;
}