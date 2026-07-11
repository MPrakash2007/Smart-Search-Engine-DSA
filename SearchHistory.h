#ifndef SEARCHHISTORY_H
#define SEARCHHISTORY_H

#include <iostream>
#include <queue>
#include <string>

using namespace std;

class SearchHistory
{
private:

    queue<string> history;
    int maxHistory;

public:

    // Constructor
    SearchHistory();

    // Add a searched word
    void addSearch(const string& word);

    // Display search history
    void displayHistory();

    // Remove all history
    void clearHistory();

    // Check if history is empty
    bool isEmpty();
};

#endif