#include "InvertedIndex.h"

#include <algorithm>
#include <cctype>

using namespace std;

//==========================================
// Constructor
//==========================================

InvertedIndex::InvertedIndex()
{
}

//==========================================
// Normalize Word
//==========================================

string InvertedIndex::normalizeWord(string word)
{
    string result;

    for(char ch : word)
    {
        if(isalpha(ch))
        {
            result += tolower(ch);
        }
    }

    return result;
}

//==========================================
// Build Complete Index
//==========================================

void InvertedIndex::buildIndex(const vector<string>& documentFiles)
{
    clearIndex();

    for(const string& file : documentFiles)
    {
        addDocument(file);
    }
}

//==========================================
// Add Document
//==========================================

void InvertedIndex::addDocument(const string& filename)
{
    ifstream file(filename);

    if(!file.is_open())
    {
        cout << "Unable to open " << filename << endl;
        return;
    }

    string word;

    while(file >> word)
    {
        word = normalizeWord(word);

        if(word.empty())
            continue;

        // Increase frequency
        index[word][filename]++;
    }

    file.close();
}

//==========================================
// Delete Document
//==========================================

void InvertedIndex::deleteDocument(const string& filename)
{
    vector<string> removeWords;

    for(auto& entry : index)
    {
        entry.second.erase(filename);

        if(entry.second.empty())
        {
            removeWords.push_back(entry.first);
        }
    }

    for(const string& word : removeWords)
    {
        index.erase(word);
    }
}

//==========================================
// Search
//==========================================

vector<SearchResult> InvertedIndex::search(const string& word)
{
    vector<SearchResult> results;

    string key = normalizeWord(word);

    auto it = index.find(key);

    if(it == index.end())
    {
        return results;
    }

    for(const auto& document : it->second)
    {
        SearchResult result;

        result.documentName = document.first;
        result.frequency = document.second;

        results.push_back(result);
    }

    sort(results.begin(),
         results.end(),
         [](const SearchResult& a,
            const SearchResult& b)
         {
             return a.frequency > b.frequency;
         });

    return results;
}

//==========================================
// Get All Indexed Words
//==========================================

vector<string> InvertedIndex::getAllIndexedWords()
{
    vector<string> words;

    for(const auto& entry : index)
    {
        words.push_back(entry.first);
    }

    sort(words.begin(), words.end());

    return words;
}

//==========================================
// Display Complete Index
//==========================================

void InvertedIndex::displayIndex()
{
    cout << "\n========== INVERTED INDEX ==========\n\n";

    for(const auto& entry : index)
    {
        cout << entry.first << endl;

        for(const auto& document : entry.second)
        {
            cout << "   "
                 << document.first
                 << " ("
                 << document.second
                 << ")"
                 << endl;
        }

        cout << endl;
    }
}

//==========================================
// Clear Index
//==========================================

void InvertedIndex::clearIndex()
{
    index.clear();
}

//==========================================
// Check Empty
//==========================================

bool InvertedIndex::isEmpty()
{
    return index.empty();
}
//==========================================
// Add Individual Word
//==========================================

void InvertedIndex::addWordToIndex(const string& word)
{
    string key = normalizeWord(word);

    if(key.empty())
        return;


    index[key]["UserAddedWords.txt"]++;
}
//==========================================
// Delete Individual Word
//==========================================

void InvertedIndex::deleteWordFromIndex(
        const string& word)
{
    string key = normalizeWord(word);

    if(key.empty())
        return;


    auto it = index.find(key);


    if(it != index.end())
    {
        index.erase(it);
    }
}