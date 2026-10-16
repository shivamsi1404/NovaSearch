
#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "tokenizer.h"

class Indexer {
private:
    struct Posting {
        int docId;
        int termFrequency;
    };

    struct DocumentInfo {
        int documentLength;
        std::vector<std::string> terms;
    };

    std::unordered_map<std::string, std::vector<Posting>> invertedIndex;

    std::unordered_map<int, DocumentInfo> documents;

    int totalDocuments = 0;
    long long totalDocumentLength = 0;

public:
    bool addDocument(int docId, const std::string& text);
    bool removeDocument(int docId);
    bool updateDocument(int docId, const std::string& text);
};
