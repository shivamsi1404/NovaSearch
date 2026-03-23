// ==========================   PHASE 4  ============================ //
// ========================== NOVASEARCH ============================ //

/*

Documentation :- This stage marks the major expansion of this project turning it from
mini search engine to NOVASEARCH Project .

PHASE 4 stage 1

*/

#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <climits>
#include <string>
#include <limits>
#include <vector>
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

// Function 6 - Global Scoring System

map<string, int> Globalscore(vector<string> &QueryWords, map<string, map<string, int>> &index)
{
    map<string, int> Finalscore;
    for (const string &word : QueryWords)
    {
        if (index.find(word) != index.end())
        {
            for (auto &FileEntry : index[word])
            {
                const string &Filename = FileEntry.first;
                int frequency = FileEntry.second;

                Finalscore[Filename] += frequency;
            }
        }
    }
    return Finalscore;
}

// Function 7 - To convert The final score to vector for displaying

vector<pair<string, int>> Results(map<string, int> &GlobalWordScore)
{
    vector<pair<string, int>> finalResults;

    for (auto &entry : GlobalWordScore)
    {
        finalResults.push_back(entry);
    }
    return finalResults;
}

// Function 8 - Sort the result storing vector

void sortthevectorpair(vector<pair<string, int>> &finalResults)
{
    sort(finalResults.begin(), finalResults.end(), [](const auto &a, const auto &b)
         { return a.second > b.second; });
}

// Function 9 - Display Results

void displayresults(vector<pair<string, int>> &finalResults)
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

            map<string, int> GlobalWordScore = Globalscore(QueryWords, index);

            // convert the map to vector to record and display final result

            vector<pair<string, int>> finalResults = Results(GlobalWordScore);

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

Project : NovaSearch Engine (Phase 4 - Core Engine Completion)

This phase marks the transformation of the project from a basic mini-search
tool into a structured and scalable search engine core.

------------------------------ CORE TECHNIQUES ------------------------------

1. Inverted Indexing:
An inverted index is a data structure that maps each word to the list of
documents in which it appears along with its frequency.

Structure used:
    word → { file → frequency }

Purpose:
- Enables fast lookup of documents for any given word
- Forms the backbone of search engines

--------------------------------------------------------------------------

2. Query Processing:
User input is processed in three steps:
- Cleaning: removes punctuation and normalizes case
- Tokenization: splits query into individual words
- Validation: ensures non-empty queries

--------------------------------------------------------------------------

3. Global Scoring (Ranking Algorithm):
Instead of evaluating each word separately, NovaSearch computes a unified
score per document.

Formula:
    Score(file) = Σ frequency of all query words in that file

Implementation:
    finalScore[file] += frequency

Purpose:
- Combines relevance across multiple query words
- Produces a ranked list of documents

--------------------------------------------------------------------------

4. Sorting Mechanism:
Results are converted into a vector and sorted in descending order based on
their computed score.

Purpose:
- Displays most relevant documents first

--------------------------------------------------------------------------

5. System Workflow (Pipeline):

    User Input
        ↓
    Cleaning
        ↓
    Tokenization
        ↓
    Global Scoring
        ↓
    Sorting
        ↓
    Display Results

--------------------------------------------------------------------------

6. System Capabilities:

✔ Supports multi-word queries
✔ Case-insensitive search
✔ Ignores punctuation
✔ Ranks documents based on relevance
✔ Efficient lookup using map-based indexing

--------------------------------------------------------------------------

7. Limitations:

- Does not use semantic understanding
- No phrase-based or positional indexing
- No TF-IDF weighting (planned upgrade)
- Limited to small/medium datasets due to in-memory maps

--------------------------------------------------------------------------

8. Performance Scope:

This engine performs efficiently for:
- Small to moderately sized datasets
- Text-based document collections
- Educational and prototype-level search systems

For large-scale systems, further optimizations like TF-IDF, indexing
compression, and distributed processing are required.

--------------------------------------------------------------------------

============================== CONCLUSION ==============================

With this, I mark the successful completion of Phase 4 of the NovaSearch
project. The system now functions as a complete search engine core with
efficient indexing, query handling, and ranking capabilities.

This lays a strong foundation for future enhancements such as TF-IDF based
ranking, advanced query processing, and integration with a user interface.

--------------------------------------------------------------------------

With Regards,  
Shivam Singh  
Developer - NovaSearch Engine

========================================================================

*/
