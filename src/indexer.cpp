#include "indexer.h"

#include <unordered_map>

// Add a document to the index
bool Indexer::addDocument(int docId, const std::string& text)
{
    // Reject duplicate document IDs
    if (documents.find(docId) != documents.end())
    {
        return false;
    }

    // Convert document text into normalized tokens
    std::vector<std::string> terms = tokenizer.tokenize(text);

    // Count the frequency of each term in this document
    std::unordered_map<std::string, int> termFrequency;

    for (const std::string& term : terms)
    {
        termFrequency[term]++;
    }

    // Add each term's posting to the inverted index
    for (const auto& entry : termFrequency)
    {
        const std::string& term = entry.first;
        int frequency = entry.second;

        invertedIndex[term].push_back({docId, frequency});

        // This document contains this term
        documentFrequency[term]++;
    }

    // Store document metadata
    documents[docId] = {
        static_cast<int>(terms.size()),
        terms
    };

    // Update collection statistics
    totalDocuments++;
    totalDocumentLength += static_cast<long long>(terms.size());

    return true;
}


// Remove a document from the index
bool Indexer::removeDocument(int docId)
{
    auto documentIt = documents.find(docId);

    // Reject requests for nonexistent documents
    if (documentIt == documents.end())
    {
        return false;
    }

    const DocumentInfo& document = documentIt->second;

    // Count each term once for this document
    std::unordered_map<std::string, int> termFrequency;

    for (const std::string& term : document.terms)
    {
        termFrequency[term]++;
    }

    // Remove this document from each relevant posting list
    for (const auto& entry : termFrequency)
    {
        const std::string& term = entry.first;

        auto indexIt = invertedIndex.find(term);

        if (indexIt != invertedIndex.end())
        {
            auto& postings = indexIt->second;

            for (auto postingIt = postings.begin();
                 postingIt != postings.end();)
            {
                if (postingIt->docId == docId)
                {
                    postingIt = postings.erase(postingIt);
                }
                else
                {
                    ++postingIt;
                }
            }

            // Remove terms that no longer appear in any document
            if (postings.empty())
            {
                invertedIndex.erase(indexIt);
            }
        }

        // Update document frequency
        auto dfIt = documentFrequency.find(term);

        if (dfIt != documentFrequency.end())
        {
            dfIt->second--;

            if (dfIt->second <= 0)
            {
                documentFrequency.erase(dfIt);
            }
        }
    }

    // Update collection statistics
    totalDocuments--;
    totalDocumentLength -= document.documentLength;

    // Remove document metadata
    documents.erase(documentIt);

    return true;
}


// Update an existing document
bool Indexer::updateDocument(int docId, const std::string& text)
{
    // The document must already exist
    if (documents.find(docId) == documents.end())
    {
        return false;
    }

    // Remove the old version before inserting the new version
    if (!removeDocument(docId))
    {
        return false;
    }

    return addDocument(docId, text);
}


// Return the number of indexed documents
std::size_t Indexer::getDocumentCount() const
{
    return documents.size();
}


// Return the average number of tokens per document
double Indexer::getAverageDocumentLength() const
{
    if (totalDocuments == 0)
    {
        return 0.0;
    }

    return static_cast<double>(totalDocumentLength) / totalDocuments;
}
