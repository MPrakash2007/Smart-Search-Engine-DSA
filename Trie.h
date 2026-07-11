#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//==========================================
// Trie Node
//==========================================

class TrieNode
{
public:

    TrieNode* children[26];
    bool isEndOfWord;

    TrieNode();
};

//==========================================
// Trie
//==========================================

class Trie
{
private:

    TrieNode* root;

    // Helper Functions
    void collectWords(TrieNode* node,
                      string currentWord,
                      vector<string>& suggestions);

    bool deleteHelper(TrieNode* node,
                      const string& word,
                      int depth);

    bool isEmpty(TrieNode* node);

public:

    // Constructor
    Trie();

    // Basic Operations
    void insertWord(const string& word);

    bool searchWord(const string& word);

    bool deleteWord(const string& word);

    // Autocomplete
    vector<string> autocomplete(const string& prefix);

    // NEW : Return every word stored in Trie
    vector<string> getAllWords();

    // Getter
    TrieNode* getRoot();
};

#endif