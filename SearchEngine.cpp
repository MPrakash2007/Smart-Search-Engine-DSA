#include "SearchEngine.h"

using namespace std;

//==========================================
// Constructor
//==========================================

SearchEngine::SearchEngine()
{
}

//==========================================
// Build Complete Search Engine
//==========================================

void SearchEngine::buildSearchEngine(
        const vector<string>& documentFiles)
{
    // Step 1 : Build Inverted Index
    invertedIndex.buildIndex(documentFiles);

    // Step 2 : Get every indexed word
    vector<string> words =
        invertedIndex.getAllIndexedWords();

    // Step 3 : Insert every word into Trie
    for(const string& word : words)
    {
        trie.insertWord(word);
    }

    // Step 4 : Load Spell Checker
    spellChecker.loadDictionary(
        trie.getAllWords());

    cout << "\n=====================================\n";
    cout << " Search Engine Initialized Successfully\n";
    cout << " Indexed Documents : "
         << documentFiles.size() << endl;
    cout << " Indexed Words     : "
         << words.size() << endl;
    cout << "=====================================\n";
}

//==========================================
// Search Word
//==========================================

vector<SearchResult> SearchEngine::searchWord(
        const string& word)
{
    vector<SearchResult> results;

    // Check whether word exists
    if(!trie.searchWord(word))
    {
        return results;
    }

    // Increase search frequency
    rankingSystem.increaseFrequency(word);

    // Save in history
    searchHistory.addSearch(word);

    // Search documents
    results = invertedIndex.search(word);

    return results;
}
//==========================================
// Autocomplete
//==========================================

vector<string> SearchEngine::autocomplete(
        const string& prefix)
{
    // Get suggestions from Trie
    vector<string> suggestions =
        trie.autocomplete(prefix);

    // Rank suggestions based on search frequency
    suggestions =
        rankingSystem.rankSuggestions(suggestions);

    return suggestions;
}

//==========================================
// Spell Check
//==========================================

vector<string> SearchEngine::spellCheck(
        const string& word)
{
    return spellChecker.getSuggestions(word);
}

//==========================================
// Add Word
//==========================================

void SearchEngine::addWord(
        const string& word)
{
    // Check if already exists
    if(trie.searchWord(word))
    {
        cout << "\nWord already exists in dictionary.\n";
        return;
    }

    // Insert into Trie
    trie.insertWord(word);

    // Add to Inverted Index
    invertedIndex.addWordToIndex(word);

    // Reload Spell Checker dictionary
    spellChecker.loadDictionary(
        trie.getAllWords());

    cout << "\nWord added successfully.\n";
}

//==========================================
// Delete Word
//==========================================

bool SearchEngine::deleteWord(
        const string& word)
{
    bool deleted =
        trie.deleteWord(word);

    if(deleted)
    {
        // Reload Spell Checker
        spellChecker.loadDictionary(
            trie.getAllWords());

        // Delete from Inverted Index
            invertedIndex.deleteWordFromIndex(word);

        cout << "\nWord deleted successfully.\n";
    }
    else
    {
        cout << "\nWord not found.\n";
    }

    return deleted;
}
//==========================================
// Show Search History
//==========================================

void SearchEngine::showHistory()
{
    searchHistory.displayHistory();
}


//==========================================
// Clear Search History
//==========================================

void SearchEngine::clearHistory()
{
    searchHistory.clearHistory();
}


//==========================================
// Show Trending Searches
//==========================================

void SearchEngine::showTrendingWords()
{
    rankingSystem.displayTrendingWords();
}


//==========================================
// Display Inverted Index
//==========================================

void SearchEngine::displayIndex()
{
    invertedIndex.displayIndex();
}