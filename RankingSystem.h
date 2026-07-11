#ifndef RANKINGSYSTEM_H
#define RANKINGSYSTEM_H

#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>

using namespace std;

//==========================================
// Word Information
//==========================================

struct WordInfo
{
    int frequency;

    WordInfo()
    {
        frequency = 0;
    }

    WordInfo(int freq)
    {
        frequency = freq;
    }
};

//==========================================
// Heap Comparator
//==========================================

class CompareWords
{
public:

    bool operator()(const pair<string, int>& a,
                    const pair<string, int>& b) const
    {
        // Higher frequency gets higher priority
        if (a.second != b.second)
            return a.second < b.second;

        // If frequency is same,
        // sort alphabetically
        return a.first > b.first;
    }
};

//==========================================
// Ranking System
//==========================================

class RankingSystem
{

private:

    unordered_map<string, WordInfo> wordFrequency;

public:

    RankingSystem();

    void increaseFrequency(const string& word);

    int getFrequency(const string& word);

    vector<string> rankSuggestions(
            vector<string>& words);

    void displayTrendingWords();

};

#endif