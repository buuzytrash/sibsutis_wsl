#include <iostream>
#include <map>
#include <vector>
#include <string>

class Document {
public:
    int id;
    std::string text;
};

class Term {
public:
    std::string term;
    std::map<int, std::vector<int>> entries;
};

class InvertedIndex {
public:
    std::map<std::string, Term> index;

    void indexDocument(Document doc, std::map<std::string, std::vector<int>> terms) {
        for (auto const& term : terms) {
            if (index.find(term.first) == index.end()) {
                Term newTerm;
                newTerm.term = term.first;
                newTerm.entries[doc.id] = term.second;
                index[term.first] = newTerm;
            } else {
                index[term.first].entries[doc.id] = term.second;
            }
        }
    }

    Term lookupTerm(std::string term) {
        if (index.find(term) != index.end()) {
            return index[term];
        } else {
            Term emptyTerm;
            return emptyTerm;
        }
    }
};

int main() {
    InvertedIndex invertedIndex;

    Document doc1;
    doc1.id = 1;
    doc1.text = "This is a sample document.";

    std::map<std::string, std::vector<int>> terms;
    terms["this"] = {0};
    terms["is"] = {5};
    terms["a"] = {8};
    terms["sample"] = {10};
    terms["document"] = {13};

    invertedIndex.indexDocument(doc1, terms);

    Term term = invertedIndex.lookupTerm("document");

    std::cout << "Term: " << term.term << std::endl;
    for (auto const& entry : term.entries) {
        std::cout << "Document ID: " << entry.first << ", Positions: ";
        for (int pos : entry.second) {
            std::cout << pos << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}