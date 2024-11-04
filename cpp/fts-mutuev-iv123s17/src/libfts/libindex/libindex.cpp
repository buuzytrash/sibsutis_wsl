#include <libfts/libindex.hxx>

namespace indexer {
void IndexBuilder::AddDocument(DocId document_id, const Doc& document_name) {
  if (index_->GetDocs().find(document_id) == index_->GetDocs().end()) {
    index_->GetDocs()[document_id] = document_name;

    const auto map = parser_->parse(document_name);

    for (const auto& [term, positions] : map) {
      index_->GetEntries()[term][document_id] = positions;
    }
  }
}

void TextIndexWriter::Write(
    const std::filesystem::path& index_path,
    Index* index) {
  std::filesystem::remove_all(index_path);

  // прямой индекс
  std::filesystem::create_directories(index_path / "docs");
  for (const auto& [doc_id, doc] : index->GetDocs()) {
    std::ofstream out(index_path / "docs" / std::to_string(doc_id));
    out << doc;
  }
  // обратный индекс
  std::filesystem::create_directories(index_path / "entries");
  for (const auto& [term, index_map] : index->GetEntries()) {
    std::string term_hash;
    picosha2::hash256_hex_string(term, term_hash);

    std::ofstream out(
        index_path / "entries" / term_hash.substr(0, 6), std::ios_base::app);
    out << term + ' ' + std::to_string(index_map.size());

    for (const auto& [doc_id, vector_pos] : index_map) {
      out << ' ' + std::to_string(doc_id) + ' ' +
              std::to_string(vector_pos.size());
      for (const auto& pos : vector_pos) {
        out << ' ' + std::to_string(pos);
      }
    }
    out << ' ' << std::endl;
  }
}
}  // namespace indexer