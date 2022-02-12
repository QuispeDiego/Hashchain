#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <unordered_map> //hash
#include "chainhash.h"

using namespace std;

vector<pair<string, string>> loadCSV(string file);

int main()
{
    vector<pair<string, string>> data = loadCSV("smalldata.csv");
    //unordered_map<string, string> hash; //reeamplazar por su propia implementacion de hash
    ChainHash<string, string> hash;

    for (size_t i = 0; i < data.size(); i++)
        hash.set(data[i].first, data[i].second);

    cout << "Size of Hash Table: " << hash.bucket_count() << endl;
    
    for (int i = 0; i < hash.bucket_count(); ++i)
    {
        cout << "bucket #" << i << " contains " << hash.bucket_size(i) << " elements: ";
        for (auto it = hash.begin(i); it != hash.end(i); ++it)
            cout << std::flush << it->key << " -> ";
        cout << std::flush << "\n";
    }
    
}

vector<pair<string, string>> loadCSV(string file)
{
    vector<pair<string, string>> data;
    fstream fin;
    fin.open(file, ios::in);
    vector<string> row;
    string line, word, temp;
    int i = 0;
    while (!fin.eof())
    {
        row.clear();
        getline(fin, line);
        if (i++ == 0)
            continue;
        stringstream s(line);
        while (getline(s, word, ';'))
        {
            row.push_back(word);
        }
        if (row.size() == 2)
            data.push_back({ row[0], row[1] });
    }
    return data;
}
