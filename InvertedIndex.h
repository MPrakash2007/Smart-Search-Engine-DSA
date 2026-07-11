#ifndef INVERTEDINDEX_H
#define INVERTEDINDEX_H

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

//==========================================
// Search Result Structure
//==========================================

struct SearchResult
{
    string documentName;
    int frequency;
};

//==========================================
// Inverted Index Class
//==========================================

class InvertedIndex
{
private:

    // word -> (document -> frequency)
    unordered_map<string, unordered_map<string, int>> index;

    // Normalize word
    string normalizeWord(string word);

public:

    // Constructor
    InvertedIndex();

    // Build complete index
    void buildIndex(const vector<string>& documentFiles);

    // Add one document
    void addDocument(const string& filename);

    // Remove one document
    void deleteDocument(const string& filename);

    // Search a word
    vector<SearchResult> search(const string& word);

    // Return all unique indexed words
    vector<string> getAllIndexedWords();

    // Display entire index (Debug)
    void displayIndex();

    // Clear index
    void clearIndex();

    void addWordToIndex(const string& word);

    // Remove individual word
void deleteWordFromIndex(const string& word);

    // Check if index is empty
    bool isEmpty();


};

#endif