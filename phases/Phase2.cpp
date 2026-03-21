// ========================== PHASE 2 ============================ // 

// Multiple File test 

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

// this version works to find the the word in multiple find also manage case sensitivity 
// along with punctuations 

string cleaner(string &s)
{
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

int main()
{
    // created a vector to insert all the file names 
    vector<string> files = {
        "Batman.txt", "IronMan.txt", "Nightwing.txt", "SpiderMan.txt", "Thor.txt","Shruti.txt"};

    cout << endl
         << endl;

    // this works as the input 
    string Search;
    cout << "Enter the Word : ";
    cin >> Search;
    cout << "Searching..." << endl
         << endl;

    // its the cleaner to manage case and punctuations     
    string cleanversionsearch = cleaner(Search);

    // a map that inputs file name and count 
    map<string, int> result;
    int count = 0;
    string temp;

    for (int i = 0; i < files.size(); i++)
    {
        // ifstream file("../Documents//files[i]"); this wont work cuz cpp wont allow those string to combine

        string path = "../Documents/" + files[i];
        ifstream file(path);
        if (!file)
        {
            cout << files[i] << " " << "opened successfully" << endl;
            continue;
        }
        // making count 0 to count every file seperately 
        count = 0; 
        while (file >> temp)
        {

            string cleanversiontemp = cleaner(temp);
            if (cleanversiontemp == cleanversionsearch)
            {
                count++;
            }
        }
        result[files[i]] = count; // defining the map 
        file.close();
    }

    // auto lets the compiler automatically figure out the type for you
    for (auto &entry : result)
    {
        cout << entry.first << " --> " << entry.second << endl;
    }
    return 0;
}

/*

With this Upgrade , this program now Searches a word throughout all the files and count 
them , along with the function of cleaner . This Marks the beginning of crazy stuff and
the end of Phase 2.
With regards,
Shivam Singh 

*/