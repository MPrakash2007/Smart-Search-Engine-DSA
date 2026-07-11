#include "SpellChecker.h"

#include <algorithm>

using namespace std;

//==========================================
// Constructor
//==========================================

SpellChecker::SpellChecker()
{
}

//==========================================
// Load Dictionary
//==========================================

void SpellChecker::loadDictionary(const vector<string>& words)
{
    dictionary = words;
}

//==========================================
// Edit Distance (Dynamic Programming)
//==========================================

int SpellChecker::editDistance(const string& word1,
                               const string& word2)
{
    int m = word1.length();
    int n = word2.length();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    // Base Cases
    for (int i = 0; i <= m; i++)
        dp[i][0] = i;

    for (int j = 0; j <= n; j++)
        dp[0][j] = j;

    // Fill DP Table
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (word1[i - 1] == word2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = 1 + min({
                    dp[i - 1][j],     // Delete
                    dp[i][j - 1],     // Insert
                    dp[i - 1][j - 1]  // Replace
                });
            }
        }
    }

    return dp[m][n];
}

//==========================================
// Get Suggestions
//==========================================

vector<string> SpellChecker::getSuggestions(const string& word)
{
    vector<pair<int, string>> candidates;

    // Calculate edit distance for every word
    for (const string& dictionaryWord : dictionary)
    {
        int distance = editDistance(word, dictionaryWord);

        // Keep only reasonably close words
        if (distance <= 2)
        {
            candidates.push_back({distance, dictionaryWord});
        }
    }

    // Sort by distance first, then alphabetically
    sort(candidates.begin(), candidates.end());

    vector<string> suggestions;

    int limit = min(5, static_cast<int>(candidates.size()));

    for (int i = 0; i < limit; i++)
    {
        suggestions.push_back(candidates[i].second);
    }

    return suggestions;
}