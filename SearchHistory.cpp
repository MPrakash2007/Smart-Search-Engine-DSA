#include "SearchHistory.h"
#include <vector>

using namespace std;

//==========================================
// Constructor
//==========================================

SearchHistory::SearchHistory()
{
    maxHistory = 10;
}

//==========================================
// Add Search
//==========================================

void SearchHistory::addSearch(const string& word)
{
    // Remove oldest search if history is full
    if (history.size() >= maxHistory)
    {
        history.pop();
    }

    history.push(word);
}

//==========================================
// Display Search History
//==========================================

void SearchHistory::displayHistory()
{
    if (history.empty())
    {
        cout << "\nNo Search History Available.\n";
        return;
    }

    queue<string> temp = history;
    vector<string> searches;

    // Copy queue contents into vector
    while (!temp.empty())
    {
        searches.push_back(temp.front());
        temp.pop();
    }

    cout << "\n========== Recent Searches ==========\n";

    // Display newest to oldest
    for (int i = static_cast<int>(searches.size()) - 1; i >= 0; i--)
    {
        cout << searches.size() - i
             << ". "
             << searches[i]
             << endl;
    }

    cout << endl;
}

//==========================================
// Clear Search History
//==========================================

void SearchHistory::clearHistory()
{
    while (!history.empty())
    {
        history.pop();
    }

    cout << "\nSearch History Cleared Successfully.\n";
}

//==========================================
// Check if History is Empty
//==========================================

bool SearchHistory::isEmpty()
{
    return history.empty();
}