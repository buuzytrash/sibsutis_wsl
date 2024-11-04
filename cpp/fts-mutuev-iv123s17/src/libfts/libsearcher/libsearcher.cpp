#include <libfts/libsearcher.hxx>
#include <optional>

namespace searcher {

std::string TextIndexAccessor::LoadDocument(std::size_t document_id) const {
  std::ifstream file(path_to_index_ / "docs" / std::to_string(document_id));
  return std::string{
      std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
}

std::size_t TextIndexAccessor::TotalDocs() const {
  using std::filesystem::directory_iterator;
  return 1 +
      std::distance(directory_iterator(path_to_index_), directory_iterator{});
}

indexer::Entries TextIndexAccessor::ParseTextEntry(
    const std::filesystem::path& path_to_entries) {
  std::ifstream file(path_to_entries);

  indexer::Entries entries;
  std::istringstream stream;
  for (std::string line; std::getline(file, line);) {
    stream.str(line);

    std::string term{};
    stream >> term;

    std::size_t doc_count{};
    stream >> doc_count;

    for (std::size_t i = 0; i < doc_count; ++i) {
      std::size_t document_id{};
      stream >> document_id;

      std::size_t pos_count{};
      stream >> pos_count;

      entries[term][document_id].reserve(pos_count);
      for (std::size_t j = 0; j < pos_count; ++j) {
        std::size_t pos{};
        stream >> pos;
        entries[term][document_id].push_back(pos);
      }
    }
  }

  return entries;
}

std::vector<std::size_t> TextIndexAccessor::GetDocsByTerm(
    const std::string& term) const {
  std::string hash_hex_term;
  picosha2::hash256_hex_string(term, hash_hex_term);
  const auto entries =
      ParseTextEntry(path_to_index_ / "entries" / hash_hex_term.substr(0, 6));

  auto it = entries.find(term);
  if (it == entries.end()) {
    throw std::runtime_error("Term not found");
  }

  std::vector<std::size_t> docs;
  for (const auto& [document_id, positions] : entries.at(term)) {
    docs.push_back(document_id);
  }

  return docs;
}

std::size_t TextIndexAccessor::GetCountTermsInDocs(
    const std::string& term,
    size_t document_id) const {
  std::string hash_hex_term;
  picosha2::hash256_hex_string(term, hash_hex_term);
  const auto entries =
      ParseTextEntry(path_to_index_ / "entries" / hash_hex_term.substr(0, 6));

  return entries.at(term).at(document_id).size();
}

std::vector<Result> Search(
    const common::NgramParser& parser,
    const IndexAccessor& index_accessor,
    const std::string& query) {
  auto parsed_query = parser.parse(query);

  auto N = static_cast<double>(index_accessor.TotalDocs());

  std::unordered_map<std::size_t, double> score_of_doc;
  for (const auto& [term, indexes] : parsed_query) {
    auto docs = index_accessor.GetDocsByTerm(term);
    const auto df = static_cast<double>(docs.size());

    for (const auto& document_id : docs) {
      const auto tf = static_cast<double>(
          index_accessor.GetCountTermsInDocs(term, document_id));
      score_of_doc[document_id] += tf * std::abs(std::log(N / df));
    }
  }

  std::vector<Result> result;
  for (const auto& [document_id, score] : score_of_doc) {
    const auto name_of_doc = index_accessor.LoadDocument(document_id);
    result.push_back({score, document_id, name_of_doc});
  }

  std::sort(result.begin(), result.end(), [](const auto& lhs, const auto& rhs) {
    return lhs.score != rhs.score ? lhs.score > rhs.score
                                  : lhs.document_id < rhs.document_id;
  });

  return result;
}

}  // namespace searcher
