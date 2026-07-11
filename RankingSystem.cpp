#include "RankingSystem.h"

using namespace std;

//==========================================
// Constructor
//==========================================

RankingSystem::RankingSystem()
{
    // No initialization needed
}

//==========================================
// Increase Search Frequency
//==========================================

void RankingSystem::increaseFrequency(const string& word)
{
    wordFrequency[word].frequency++;
}

//==========================================
// Get Frequency
//==========================================

int RankingSystem::getFrequency(const string& word)
{
    if (wordFrequency.find(word) != wordFrequency.end())
    {
        return wordFrequency[word].frequency;
    }

    return 0;
}

//==========================================
// Rank Suggestions (Top 5)
//==========================================

vector<string> RankingSystem::rankSuggestions(vector<string>& words)
{
    priority_queue<
        pair<string, int>,
        vector<pair<string, int>>,
        CompareWords
    > pq;

    // Push all suggestions into heap
    for (const string& word : words)
    {
        pq.push({word, getFrequency(word)});
    }

    vector<string> rankedWords;

    // Return only Top 5 suggestions
    int limit = 5;

    while (!pq.empty() && limit--)
    {
        rankedWords.push_back(pq.top().first);
        pq.pop();
    }

    return rankedWords;
}

//==========================================
// Display Top Trending Words
//==========================================

void RankingSystem::displayTrendingWords()
{
    priority_queue<
        pair<string, int>,
        vector<pair<string, int>>,
        CompareWords
    > pq;

    for (const auto& item : wordFrequency)
    {
        pq.push({item.first, item.second.frequency});
    }

    cout << "\n========== Top Trending Searches ==========\n";

    int rank = 1;

    while (!pq.empty() && rank <= 10)
    {
        cout << rank << ". "
             << pq.top().first
             << " ("
             << pq.top().second
             << " searches)"
             << endl;

        pq.pop();
        rank++;
    }

    cout << endl;
}