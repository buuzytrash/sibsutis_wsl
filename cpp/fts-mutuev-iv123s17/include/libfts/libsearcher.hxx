#pragma once
#include <libfts/libindex.hxx>
#include <libfts/libparse.hxx>

#include <cmath>
#include <sstream>

namespace searcher {
class IndexAccessor {
 public:
  IndexAccessor() = default;
  IndexAccessor(const IndexAccessor& other) = default;
  IndexAccessor(IndexAccessor&& other) = delete;
  IndexAccessor& operator=(const IndexAccessor& other) = default;
  IndexAccessor& operator=(IndexAccessor&& other) = delete;

  virtual std::string LoadDocument(std::size_t document_id) const = 0;
  virtual std::size_t TotalDocs() const = 0;
  virtual std::vector<std::size_t> GetDocsByTerm(
      const std::string& term) const = 0;
  virtual std::size_t GetCountTermsInDocs(
      const std::string& term,
      size_t document_id) const = 0;
  virtual ~IndexAccessor() = default;
};

class TextIndexAccessor : public IndexAccessor {
 public:
  explicit TextIndexAccessor(std::filesystem::path path_to_index)
      : path_to_index_(std::move(path_to_index)){};
  std::string LoadDocument(std::size_t document_id) const override;
  std::size_t TotalDocs() const override;
  std::vector<std::size_t> GetDocsByTerm(
      const std::string& term) const override;
  std::size_t GetCountTermsInDocs(const std::string& term, size_t document_id)
      const override;

 private:
  static indexer::Entries ParseTextEntry(
      const std::filesystem::path& path_to_entries);
  std::filesystem::path path_to_index_;
};

struct Result {
  double score;
  std::size_t document_id;
  std::string name_of_doc;
};

std::vector<Result> Search(
    const common::NgramParser& parser,
    const IndexAccessor& index_accessor,
    const std::string& query);
}  // namespace searcher