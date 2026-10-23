
#pragma once

#include <string>
#include <vector>
#include <unordered_map>

struct Posting {
    int documentID;
    int termFrequency;
};

struct DocumentInfo {
    int documentLength;
};

class Indexer {
private:
    // Term -> documents containing that term
    std::unordered_map<std::string, std::vector<Posting>> invertedIndex;

    // Document ID -> document metadata
    std::unordered_map<int, DocumentInfo> documents;

    // Term -> number of documents containing that term
    std::unordered_map<std::string, int> documentFrequency;

    // Total number of tokens across indexed documents
    long long totalDocumentLength = 0;

public:
    // Add a document to the index
    void addDocument(int documentID, const std::string& content);

    // Remove a document from the index
    void removeDocument(int documentID);

    // Retrieve the total number of indexed documents
    size_t getDocumentCount() const;

    // Retrieve the average document length
    double getAverageDocumentLength() const;

};
