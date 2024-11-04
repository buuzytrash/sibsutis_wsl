#pragma once
#include <picosha2.h>
#include <filesystem>
#include <fstream>
#include <libfts/libparse.hxx>
#include <memory>
#include <string>
namespace indexer {

using DocId = std::size_t;
using Doc = std::string;
using Docs = std::unordered_map<DocId, Doc>;
using IndexMap = std::unordered_map<DocId, std::vector<std::size_t>>;
using Term = std::string;
using Entries = std::unordered_map<Term, IndexMap>;

class Index {
 public:
  explicit Index() = default;

  Docs& GetDocs() {
    return docs;
  }
  Entries& GetEntries() {
    return entries;
  }

 private:
  Docs docs;
  Entries entries;
};

class IndexBuilder {
 public:
  explicit IndexBuilder(const std::string& t_configPath)
      : index_{std::make_shared<Index>()},
        parser_{std::make_shared<common::NgramParser>(t_configPath)} {
  }

  void AddDocument(DocId document_id, const Doc& document_name);

  Index* GetIndex() {
    return index_.get();
  }

 private:
  std::shared_ptr<Index> index_;
  std::shared_ptr<common::NgramParser> parser_;
};

class IndexWriter {
 public:
  IndexWriter() = default;
  IndexWriter(const IndexWriter& other) = default;
  IndexWriter(IndexWriter&& other) = delete;

  virtual void Write(const std::filesystem::path& index_path, Index* index) = 0;
  virtual ~IndexWriter() = default;
};

class TextIndexWriter : virtual public IndexWriter {
 public:
  void Write(const std::filesystem::path& index_path, Index* index) override;
  ~TextIndexWriter() override = default;
};
}  // namespace indexer