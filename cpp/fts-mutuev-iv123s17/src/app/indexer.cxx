#include <rapidcsv.h>
#include <cxxopts.hpp>
#include <libfts/libindex.hxx>
#include <libfts/libparse.hxx>
#include <libfts/libsearcher.hxx>
#include <pugixml.hpp>
#include <replxx.hxx>

struct IndexOpt {
  std::filesystem::path path_to_csv;
  std::filesystem::path path_to_index;
  std::filesystem::path path_to_config;
};

int main(int argc, char** argv) {
  cxxopts::Options options("indexer");
  try {
    options.add_options()(
        "csv", "Enable csv doc", cxxopts::value<std::string>())(
        "config",
        "Enable config",
        cxxopts::value<std::string>()->default_value("config.xml"))(
        "index", "Enable index path", cxxopts::value<std::string>());

    const auto result = options.parse(argc, argv);
    if (result.count("csv") != 1 && result.count("index") != 1) {
      std::cout << options.help() << "\n";
      return 0;
    }

    auto opt = std::make_shared<IndexOpt>();
    opt->path_to_csv = result["csv"].as<std::string>();
    opt->path_to_index = result["index"].as<std::string>();

    if (result.count("config") != 1) {
      opt->path_to_config = "../../../../config.xml";
    } else {
      opt->path_to_config = result["config"].as<std::string>();
    }

    auto index_build =
        std::make_shared<indexer::IndexBuilder>(opt->path_to_config);
    auto document = std::make_shared<rapidcsv::Document>(opt->path_to_csv);
    std::vector<indexer::DocId> ids =
        document->GetColumn<indexer::DocId>("bookID");
    std::vector<indexer::Doc> names =
        document->GetColumn<indexer::Doc>("title");

    for (std::size_t i = 0; i < ids.size(); i++) {
      index_build->AddDocument(ids[i], names[i]);
    }

    auto writter = std::make_shared<indexer::TextIndexWriter>();
    writter->Write("./index", index_build->GetIndex());

  } catch (const std::exception& error) {
    std::cerr << error.what() << std::endl;
    return 1;
  }
  return 0;
}