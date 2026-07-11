#include <iostream>
#include <vector>
#include <string>

#include "SearchEngine.h"

using namespace std;


//==========================================
// Main Function
//==========================================

int main()
{
    SearchEngine engine;


    //==========================================
    // Load Documents
    //==========================================

    vector<string> documents =
    {
        "documents/DSA.txt",
        "documents/CPP.txt",
        "documents/DBMS.txt",
        "documents/OS.txt",
        "documents/CN.txt"
    };


    // Build Search Engine

    engine.buildSearchEngine(documents);



    int choice;


    do
    {
        cout << "\n=====================================\n";
        cout << "        SMART SEARCH ENGINE\n";
        cout << "=====================================\n";

        cout << "1. Search\n";
        cout << "2. Autocomplete\n";
        cout << "3. Add Word\n";
        cout << "4. Delete Word\n";
        cout << "5. Search History\n";
        cout << "6. Trending Searches\n";
        cout << "7. Display Index\n";
        cout << "8. Exit\n";

        cout << "\nEnter choice : ";
        cin >> choice;



        switch(choice)
        {

        //==================================
        // Search
        //==================================

        case 1:
        {
            string word;

            cout << "\nEnter search word : ";
            cin >> word;


            vector<SearchResult> results =
                engine.searchWord(word);



            if(results.empty())
            {
                cout << "\nWord not found.\n";


                vector<string> suggestions =
                    engine.spellCheck(word);


                if(!suggestions.empty())
                {
                    cout << "\nDid you mean:\n";

                    for(string s : suggestions)
                    {
                        cout << "- "
                             << s
                             << endl;
                    }
                }

            }

            else
            {
                cout << "\n========== SEARCH RESULTS ==========\n";


                int count = 1;


                for(SearchResult result : results)
                {
                    cout << count
                         << ". "
                         << result.documentName
                         << endl;


                    cout << "   Matches : "
                         << result.frequency
                         << endl;


                    count++;
                }
            }


            break;
        }



        //==================================
        // Autocomplete
        //==================================

        case 2:
        {
            string prefix;


            cout << "\nEnter prefix : ";
            cin >> prefix;


            vector<string> suggestions =
                engine.autocomplete(prefix);



            if(suggestions.empty())
            {
                cout << "\nNo suggestions found.\n";
            }

            else
            {
                cout << "\nSuggestions:\n";


                int i = 1;

                for(string word : suggestions)
                {
                    cout << i
                         << ". "
                         << word
                         << endl;

                    i++;
                }
            }


            break;
        }



        //==================================
        // Add Word
        //==================================

        case 3:
        {
            string word;

            cout << "\nEnter word : ";
            cin >> word;


            engine.addWord(word);

            break;
        }



        //==================================
        // Delete Word
        //==================================

        case 4:
        {
            string word;


            cout << "\nEnter word : ";
            cin >> word;


            engine.deleteWord(word);

            break;
        }



        //==================================
        // History
        //==================================

        case 5:
        {
            engine.showHistory();

            break;
        }



        //==================================
        // Trending
        //==================================

        case 6:
        {
            engine.showTrendingWords();

            break;
        }



        //==================================
        // Display Index
        //==================================

        case 7:
        {
            engine.displayIndex();

            break;
        }



        //==================================
        // Exit
        //==================================

        case 8:
        {
            cout << "\nThank you for using Smart Search Engine.\n";
            break;
        }



        default:
        {
            cout << "\nInvalid Choice.\n";
        }

        }


    }while(choice != 8);



    return 0;
}