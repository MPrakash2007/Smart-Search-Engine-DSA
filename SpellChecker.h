#ifndef SPELLCHECKER_H
#define SPELLCHECKER_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class SpellChecker
{
private:

    vector<string> dictionary;

public:

    // Constructor
    SpellChecker();

    // Load dictionary words
    void loadDictionary(const vector<string>& words);

    // Calculate Edit Distance
    int editDistance(const string& word1,
                     const string& word2);

    // Get best suggestions
    vector<string> getSuggestions(const string& word);
};

#endif