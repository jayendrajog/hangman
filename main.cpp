/**
 Hangman with console output
 Implemented by using hashtables and multimaps
 **/
#include <iostream>
#include <fstream>
#include <string.h>
#include <unordered_map>
#include <map>
#include <stdlib.h>
using namespace std;
string printhangman(int input)
{
    switch(input)
    {
        case 0: return "";
        case 1: return "    ***\n   *   *\n    ***\n";//head
        case 2: return "    ***\n   *   *\n    ***\n     *\n     *\n     *\n     *\n";//torso
        case 3: return "    ***\n   *   *\n    ***\n     *\n  *******\n     *\n     *\n";//arms
        case 4: return "    ***\n   *   *\n    ***\n     *\n 0*******0\n     *\n     *\n";//hands
        case 5: return "    ***\n   *   *\n    ***\n     *\n 0*******0\n     *\n     *\n    * *\n   *   *\n  *     *\n";//legs
        case 6: return "    ***\n   *   *\n    ***\n     *\n 0*******0\n     *\n     *\n    * *\n   *   *\n  *     *\n _       _\n";//feet
        case 7: return "    ***\n   *- -*\n    ***\n     *\n 0*******0\n     *\n     *\n    * *\n   *   *\n  *     *\n _       _\n";//face
    }
   return "Error, enter correct input";
}
int main(int argc, const char * argv[])
{
    //copied the stock dictionary present in macs into my Hangman directory
    ifstream dictionary("/Users/Jayendra/Desktop/CSProjects/Hangman/words.txt");
    const int num_words_in_dictionary = 235886;
    srand(time(NULL));
    //randomly select a number correlating to one of the dictionary words
    int random = rand()%num_words_in_dictionary;
    string word;
    int linenum = 0;
    //sets 'word' equal to the word correlating to the random line number
    while(1)
    {
        getline(dictionary, word);
        linenum++;
        if(linenum == random)
        {
            break;
        }
    }
    string hiddenWord = ""; //this is the hidden version of the word the user sees, ex. your word is pr_gramming
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    int hangman_counter = 0;
    
    //hashtable maps each letter to the number of instances of that letter in the word, ex. in beet, a->0, b->1, ..., e->2, etc.
    unordered_map<char, int>hashtable;
    unsigned long size = word.size();
    //hashtable2 maps each letter to it's index in the word
    multimap<char, int>hashtable2;
    //set up the hashtable
    cout << "The word has " << size << " letters. Good luck!" <<endl;
    //sets up the hashtable and multimap based off the random word
    for(unsigned long i = 0; i < size; i++)
    {
        char temp = tolower(word[i]);
        unordered_map<char, int>::const_iterator it = hashtable.find(temp);
        if(it == hashtable.end())
            hashtable.emplace(temp,1);
        else hashtable.emplace(temp,hashtable.at(temp)+1);
        hiddenWord += "_";
        hashtable2.emplace(temp, i);
    }
    while (1)
    {
        if(hiddenWord.find('_') == string::npos)
        {
            cout << "CONGRATULATIONS. You are victorious" << endl;
            break;
        }
        char guess;
        cout <<"Enter a letter" << endl;
        cin >> guess;
        guess = tolower(guess);
        if(alphabet.find(guess) == string::npos)
        {
            cout << "Letter already entered or is invalid" << endl;
            continue;
        }
        else
        {
            alphabet[alphabet.find(guess)] = ' ';
        }
        unordered_map<char, int>::const_iterator it = hashtable.find(guess);
        //if not in the table
        if(it == hashtable.end())
        {
            cout << printhangman(++hangman_counter);
            cout << "The word: " << hiddenWord << endl;
            if(hangman_counter>=7)
            {
                cout << "GAME OVER. YOU HAVE LOST. The word was " << word << ". Better luck next time" << endl;
                break;
            }
        }
        else{
            multimap<char, int>::const_iterator it2 = hashtable2.find(guess);
            cout << "Letter is present!" << endl;
            while(it2 != hashtable2.end())
            {
                hiddenWord[it2->second] = guess;
                hashtable2.erase(it2);
                it2 = hashtable2.find(guess);
            }
            cout << "The word: " << hiddenWord << endl;
        }
    }
}

