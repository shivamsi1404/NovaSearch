// ========================== PHASE 3 ============================ // 

// Inverse Indexing 

#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream> 
#include <string>
#include <vector>
#include <map>
#include <set>
using namespace std;

/*

here we take care of inverse indexing along with counting marks the beginning of Phase 3

*/

// <sstream> lets you read and write strings as if they were streams like cin and cout

// Inverted Index:
// This data structure maps each word to the set of files in which that word appears.
// Instead of storing:  file → words,
// we store:            word → files.
// This allows fast searching because we can directly find all documents containing
// a given word without scanning every file again.
// thats done with index map

string cleaner(string &s)
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

vector<string> splitword(string &s)
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

vector<pair<string, int>> maptovector(map<string, int> &score)
{
    vector<pair<string, int>> result;

    for (auto &entry : score)
    {
        result.push_back(entry);
        // entry is already a pair<string, int>
    }

    return result;
}

int main()
{
    // created a vector to insert all the file names
    vector<string> files = {
        "Batman.txt", "IronMan.txt", "Nightwing.txt", "SpiderMan.txt", "Thor.txt"};

    cout << endl
         << endl;

    // a map that stores: word -> set of files

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
    cout << endl
         << endl;
    cout << "Hello User" << endl;
    cout << "Press 1. To Search" << endl;
    cout << "      2. Exit" << endl;
    int choice;
    cin >> choice;
    while (choice == 1)
    {
        cout << endl
             << endl;
        cout << "Enter Your Query : ";
        // Take users query input
        string s;
        // getline() is skipped because of cin >> choice
        cin.ignore();
        getline(cin, s);
        cout << "Searching..." << endl;
        string cleaned_s = cleaner(s);

        vector<string> query = splitword(cleaned_s);

        map<string, int> score;

        for (string i : query)
        {
            // “Does this word exist in my inverse index or not?”
            string query_input = i;
            // index.end() means “One position after the last element.”
            // Searches for word in the map index
            if (index.find(query_input) != index.end())
            {
                // Word exists in inverse index
                for (auto targetfiles : index[query_input])
                // This loop goes through every file name present in that sub map
                {
                    string filename = targetfiles.first;
                    int frequency = targetfiles.second;

                    score[filename] += frequency;
                }
            }
        }

        vector<pair<string, int>> result = maptovector(score);

        sort(result.begin(), result.end(), [](auto &a, auto &b)
             { return a.second > b.second; });

        int rank = 1;
        for (int i = 0; i < result.size(); i++)
        {
            cout << rank << ". " << result[i].first << " -->  Results found : " << result[i].second << endl;
            rank++;
        }
        if (result.empty())
        {
            cout << "No result Found" << endl;
        }

        cout << "Press 1 to Search again " << endl
             << "Press 2 to Exit" << endl;
        cout << "choice : ";
        cin >> choice;
    }
    return 0;
}

/*
At this level This project lacks multiple words search character search
and number search which we will take care in the next chapter
With this I mark the end of Phase 3
With Regards ,
Shivam Singh  
*/