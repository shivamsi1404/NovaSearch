// ========================== PHASE 3 UPGRADE 2 ============================ //

/*

1. Sorting Upgrades 

*/

#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <vector>
#include <map>
#include <set>
using namespace std;

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

string Querycleaner(string s)
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

vector<pair<string, vector<pair<string, int>>>> maptovector(map<string, map<string, int>> &score)
{
    vector<pair<string, vector<pair<string, int>>>> result;

    for (auto &outer : score)
    {
        vector<pair<string, int>> Filecount;
        for (auto &inner : outer.second)
        {
            Filecount.push_back({inner.first, inner.second});
        }
        result.push_back({outer.first, Filecount});
        // entry is already a pair<string, int>
    }

    return result;
}

int main()
{
    //=============================== INDEXING =========================================

    // created a vector to insert all the file names
    vector<string> files = {
        "Batman.txt", "IronMan.txt", "Nightwing.txt", "SpiderMan.txt", "Thor.txt", "Shruti.txt"};

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

    // ========================== User Input Query ==================================

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
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, s);
        cout << "Searching..." << endl;
        string cleaned_s = Querycleaner(s);

        vector<string> query = splitword(cleaned_s);

        map<string, map<string, int>> score;

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

                    score[query_input][filename] += frequency;
                }
            }
        }

        vector<pair<string, vector<pair<string, int>>>> result = maptovector(score);

        //Sorting algorithm

        for (auto &outer : result)
        {
            sort(outer.second.begin(), outer.second.end(),
                 [](const auto &a, const auto &b)
                 {
                     return a.second > b.second; // higher score first
                 });
        }

        sort(result.begin(), result.end(),
             [](const auto &a, const auto &b)
             {
                 return a.first < b.first;
             });



        int serialno = 1;

        for (int i = 0; i < result.size(); i++)
        {
            cout << endl;
            cout << "Result : " << serialno << ". " << result[i].first << endl;
            vector<pair<string, int>> test = result[i].second;
            int rank = 1;
            for (int j = 0; j < test.size(); j++)
            {
                cout << rank << ". " << test[j].first << " ----->  Result Found : " << test[j].second << endl;
                rank++;
            }
            serialno++;
        }

        if (result.empty())
        {
            cout << "No Result Found" << endl;
        }

        cout << "Press 1 to Search again " << endl
             << "Press 2 to Exit" << endl;
        cout << "choice : ";
        cin >> choice;
    }
    return 0;
}

/*
Documentation 

At this Stage this Program is complete for Multiword Query Search 
With this i mark the end of the Student level MiniSearch engine and
beggining of the Major Expansion of this project ; 

With Regards 
Shivam Singh 
*/
