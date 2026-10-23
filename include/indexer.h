#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <cstddef>

#include "tokenizer.h"

class Indexer {
private:
    // Represents a term's occurrence in a document
    struct Posting {
        int docId;
        int termFrequency;
    };

    // Stores metadata associated with a document
    struct DocumentInfo {
        int documentLength;
        std::vector<std::string> terms;
    };

    // Term -> list of documents containing that term
    std::unordered_map<std::string, std::vector<Posting>> invertedIndex;

    // Document ID -> document metadata
    std::unordered_map<int, DocumentInfo> documents;

    // Term -> number of documents containing the term
    std::unordered_map<std::string, int> documentFrequency;

    // Collection statistics
    int totalDocuments = 0;
    long long totalDocumentLength = 0;

    // Tokenizes document content
    Tokenizer tokenizer;

public:
    // Document management
    bool addDocument(int docId, const std::string& text);
    bool removeDocument(int docId);
    bool updateDocument(int docId, const std::string& text);

    // Collection statistics
    std::size_t getDocumentCount() const;
    double getAverageDocumentLength() const;
};
