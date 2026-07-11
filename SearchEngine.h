#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include <iostream>
#include <vector>
#include <string>

#include "Trie.h"
#include "RankingSystem.h"
#include "SearchHistory.h"
#include "SpellChecker.h"
#include "InvertedIndex.h"

using namespace std;

class SearchEngine
{
private:

    Trie trie;
    RankingSystem rankingSystem;
    SearchHistory searchHistory;
    SpellChecker spellChecker;
    InvertedIndex invertedIndex;

public:

    //==========================================
    // Constructor
    //==========================================

    SearchEngine();

    //==========================================
    // Build Search Engine
    //==========================================

    void buildSearchEngine(const vector<string>& documentFiles);

    //==========================================
    // Search
    //==========================================

    vector<SearchResult> searchWord(const string& word);

    //==========================================
    // Autocomplete
    //==========================================

    vector<string> autocomplete(const string& prefix);

    //==========================================
    // Spell Checker
    //==========================================

    vector<string> spellCheck(const string& word);

    //==========================================
    // Dictionary Operations
    //==========================================

    void addWord(const string& word);

    bool deleteWord(const string& word);

    //==========================================
    // Search History
    //==========================================

    void showHistory();

    void clearHistory();

    //==========================================
    // Trending Searches
    //==========================================

    void showTrendingWords();

    //==========================================
    // Debugging
    //==========================================

    void displayIndex();
};

#endif