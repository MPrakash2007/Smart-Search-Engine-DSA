#include "Trie.h"
#include <cctype>
#include <algorithm>
// ==========================================
// TrieNode Constructor
// ==========================================
TrieNode::TrieNode()
{
    isEndOfWord = false;

    for (int i = 0; i < 26; i++)
    {
        children[i] = nullptr;
    }
}

// ==========================================
// Trie Constructor
// ==========================================
Trie::Trie()
{
    root = new TrieNode();
}

// ==========================================
// Get Root
// ==========================================
TrieNode* Trie::getRoot()
{
    return root;
}

// ==========================================
// Insert Word
// ==========================================
void Trie::insertWord(const string& word)
{
    TrieNode* current = root;

    for (char ch : word)
    {
        if (!isalpha(ch))
            continue;

        char lower = tolower(ch);
        int index = lower - 'a';

        if (current->children[index] == nullptr)
        {
            current->children[index] = new TrieNode();
        }

        current = current->children[index];
    }

    current->isEndOfWord = true;
}

// ==========================================
// Search Word
// ==========================================
bool Trie::searchWord(const string& word)
{
    TrieNode* current = root;

    for (char ch : word)
    {
        if (!isalpha(ch))
            continue;

        char lower = tolower(ch);
        int index = lower - 'a';

        if (current->children[index] == nullptr)
        {
            return false;
        }

        current = current->children[index];
    }

    return current->isEndOfWord;
}

// ==========================================
// Check if Node has Children
// ==========================================
bool Trie::isEmpty(TrieNode* node)
{
    for (int i = 0; i < 26; i++)
    {
        if (node->children[i] != nullptr)
            return false;
    }

    return true;
}

// ==========================================
// Delete Helper (Recursive)
// ==========================================
bool Trie::deleteHelper(TrieNode* node, const string& word, int depth)
{
    if (node == nullptr)
        return false;

    if (depth == word.length())
    {
        if (!node->isEndOfWord)
            return false;

        node->isEndOfWord = false;

        return isEmpty(node);
    }

    int index = tolower(word[depth]) - 'a';

    if (deleteHelper(node->children[index], word, depth + 1))
    {
        delete node->children[index];
        node->children[index] = nullptr;

        return (!node->isEndOfWord && isEmpty(node));
    }

    return false;
}

// ==========================================
// Delete Word
// ==========================================
bool Trie::deleteWord(const string& word)
{
    if (!searchWord(word))
        return false;

    deleteHelper(root, word, 0);

    return true;
}

// ==========================================
// DFS for Autocomplete
// ==========================================
void Trie::collectWords(
    TrieNode* node,
    string currentWord,
    vector<string>& suggestions)
{
    if (node == nullptr)
        return;

    if (node->isEndOfWord)
    {
        suggestions.push_back(currentWord);
    }

    for (int i = 0; i < 26; i++)
    {
        if (node->children[i] != nullptr)
        {
            char nextChar = 'a' + i;

            collectWords(
                node->children[i],
                currentWord + nextChar,
                suggestions
            );
        }
    }
}

// ==========================================
// Autocomplete
// ==========================================
vector<string> Trie::autocomplete(const string& prefix)
{
    vector<string> suggestions;

    TrieNode* current = root;

    for (char ch : prefix)
    {
        if (!isalpha(ch))
            continue;

        char lower = tolower(ch);
        int index = lower - 'a';

        if (current->children[index] == nullptr)
        {
            return suggestions;
        }

        current = current->children[index];
    }

    collectWords(current, prefix, suggestions);

    return suggestions;
}
//==========================================
// Return All Words in Trie
//==========================================

vector<string> Trie::getAllWords()
{
    vector<string> words;

    collectWords(root, "", words);

    return words;
}