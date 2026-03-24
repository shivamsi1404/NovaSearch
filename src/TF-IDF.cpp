// ==========================   PHASE 5  ============================ //
// ========================== NOVASEARCH ============================ //

/*

Documentation :- This stage marks the implementation of TF IDF  .

PHASE 5

*/

#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <climits>
#include <string>
#include <limits>
#include <vector>
#include <cmath>
#include <map>
#include <set>
using namespace std;

// Function 1 - Word cleaner

string cleaner(const string &s)
{
    // meant to remove punctuation and case sensitivity
    string temp = "";
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] >= 'a' && s[i] <= 'z')
        {
            temp.push_back(s[i]);
        }
        else if (s[i] >= 'A' && s[i] <= 'Z')
        {
            // Logic behind conversion
            temp.push_back(s[i] - 'A' + 'a');
        }
        else
        {
            // ignore punctuations
        }
    }
    return temp;
}

// Function 2 - Query cleaner that allows spaces to exist

string Querycleaner(const string &s)

{
    // meant to remove punctuation and case sensitivity
    string temp = "";
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] >= 'a' && s[i] <= 'z')
        {
            temp.push_back(s[i]);
        }
        else if (s[i] >= 'A' && s[i] <= 'Z')
        {
            // Logic behind conversion
            temp.push_back(s[i] - 'A' + 'a');
        }
        else if (s[i] == ' ')
        {
            temp.push_back(s[i]);
        }
        else
        {
            // ignore punctuations
        }
    }
    return temp;
}

// Function 3 - Splits word from the query by using that space

vector<string> splitword(const string &s)
{
    // meant to get all the query seperate their words
    // same can be done without sstream
    vector<string> store;
    stringstream ss(s);
    string temp = "";

    while (ss >> temp)
    {
        store.push_back(temp);
    }

    return store;
}

// Function 4 - File Opener and Iverted Index Builder

map<string, map<string, int>> InvertedIndex(vector<string> &files)
{
    cout << endl
         << endl;
    map<string, map<string, int>> index;
    string temp;

    for (int i = 0; i < files.size(); i++)
    {
        // ifstream file("../Documents//files[i]"); this wont work cuz cpp wont allow those string to combine

        string path = "../Documents/" + files[i];
        ifstream file(path);
        if (!file)
        {
            cout << files[i] << " " << "failed to open" << endl;
            continue;
        }
        else
        {
            cout << files[i] << " opened successfully" << endl;
        }
        // Read each word from the file
        while (file >> temp)
        {

            string cleanversiontemp = cleaner(temp);
            // If after cleaning the word becomes empty (like "!!!" → ""), skip it and move to the next word.
            if (cleanversiontemp.empty())
            {
                continue;
            }
            // rest store every word from the document
            // Increase count of this word in this file

            index[cleanversiontemp][files[i]]++;
        }

        file.close();
    }
    return index;
}

// Function 5 - User Interaction

string calluser()
{
    cout << "Search your query below or type 'exit' to quit:\n";

    string input;
    getline(cin, input);

    return input;
}

// Function 6 - TF IDF Scoring System  

map<string, double> TFIDFscore(vector<string> &QueryWords, map<string, map<string, int>> &index , int totaldocuments)
{
    map<string, double> Finalscore;
    for (const string &word : QueryWords)
    {
        if (index.find(word) != index.end())
        {
            
            int docscontaining = index[word].size(); 

            // IDF calculation 

            double idf = log((double)totaldocuments/ (docscontaining+1));

            for (auto &FileEntry : index[word])
            {
                const string &Filename = FileEntry.first;
                int frequency = FileEntry.second;

                double tf = 1 + log(frequency);
                double tfidf = tf * idf ; 
                
                Finalscore[Filename] += tfidf;
            }
        }
    }
    return Finalscore;
}

// Function 7 - To convert The final score to vector for displaying

vector<pair<string, double>> Results(map<string, double> &GlobalWordScore)
{
    vector<pair<string, double>> finalResults;

    for (auto &entry : GlobalWordScore)
    {
        finalResults.push_back(entry);
    }
    return finalResults;
}

// Function 8 - Sort the result storing vector

void sortthevectorpair(vector<pair<string, double>> &finalResults)
{
    sort(finalResults.begin(), finalResults.end(), [](const auto &a, const auto &b)
         { return a.second > b.second; });
}

// Function 9 - Display Results

void displayresults(vector<pair<string, double>> &finalResults)
{
    cout << "\n======= RESULTS =======\n";

    int rank = 1;

    for (auto &res : finalResults)
    {
        cout << rank << ". " << res.first
             << " -----> Score: " << res.second << endl;
        rank++;
    }

    if (finalResults.empty())
    {
        cout << "No results found\n";
    }
}

// main

int main(int argc, char const *argv[])
{
    // vector storing all file names (this could be improved)

    vector<string> files = {"Batman.txt", "IronMan.txt", "Nightwing.txt", "SpiderMan.txt", "Thor.txt", "Shruti.txt"};
    int totaldocuments = files.size();

    // inverse indexing

    map<string, map<string, int>> index = InvertedIndex(files);

    // insystem

    cout << "======== Hello User ========" << endl;

    while (true)
    {
        // user interaction

        string Queryorquit = calluser();

        // cleaning query

        string cleanedqueryorquit = Querycleaner(Queryorquit);

        // to exit

        if (Queryorquit == "exit")
        {
            break;
        }

        // to search

        else
        {
            cout << "\nSearching for: " << Queryorquit << endl;

            // make a vector to store all the words of the query

            vector<string> QueryWords = splitword(cleanedqueryorquit);

            if (QueryWords.empty())
            {
                cout << "Empty query\n";
                continue;
            }

            // creat a map that saves the score of every query word

            map<string, double> GlobalWordScore = TFIDFscore(QueryWords, index, totaldocuments);

            // convert the map to vector to record and display final result

            vector<pair<string, double>> finalResults = Results(GlobalWordScore);

            // Sort the vector

            sortthevectorpair(finalResults);

            // Display Results

            displayresults(finalResults);
        }
    }

    return 0;
}

/*

========================== NOVASEARCH DOCUMENTATION ==========================

Project : NovaSearch Engine (Phase 5 - TF-IDF Ranking Upgrade)

This phase marks the transition from basic frequency-based ranking to a more
intelligent and relevance-driven scoring system using TF-IDF.

------------------------------ CORE CONCEPT ------------------------------

TF-IDF (Term Frequency - Inverse Document Frequency) is a ranking technique
used to evaluate how important a word is to a document relative to a collection.

Formula used:

    Score = (1 + log(TF)) × log(1 + N / (DF + 1))

Where:
- TF (Term Frequency): Number of times a word appears in a document
- DF (Document Frequency): Number of documents containing the word
- N  (Total Documents): Total number of documents in the system

------------------------------ INTUITION ------------------------------

- Words appearing frequently in a document → more important (TF ↑)
- Words appearing in many documents → less important (IDF ↓)

Thus:
- Common words (e.g., "the", "is") get lower scores
- Rare, meaningful words get higher influence in ranking

------------------------------ IMPLEMENTATION ------------------------------

1. For each query word:
   - Calculate IDF using total documents and document frequency

2. For each document containing the word:
   - Compute TF using log scaling:
         TF = 1 + log(frequency)

3. Multiply TF and IDF:
         TF-IDF = TF × IDF

4. Accumulate scores across all query words:
         FinalScore[doc] += TF-IDF

------------------------------ IMPACT ------------------------------

- Improves relevance of search results
- Reduces dominance of frequent but unimportant words
- Introduces a mathematically grounded ranking system

------------------------------ LIMITATIONS ------------------------------

- Does not consider word position (no phrase awareness)
- No semantic understanding (purely statistical)
- Can be further improved using advanced models (e.g., BM25)

------------------------------ CONCLUSION ------------------------------

With TF-IDF integration, NovaSearch evolves from a basic keyword matcher
into a relevance-aware search engine. This phase lays the foundation for
future enhancements in ranking and data processing.

--------------------------------------------------------------------------

With Regards,  
Shivam Singh  

========================================================================

*/