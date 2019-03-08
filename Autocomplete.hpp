/**
 *  CSE 100 PA2 C++ Autocomplete
 *  Author: Jonathan Margoliash
 *  Modified from code authored by: Jor-el Briones, Christine Alvarado
 */

#ifndef AUTOCOMPLETE_HPP
#define AUTOCOMPLETE_HPP

#include <vector>
#include <string>
#include "TST.cpp"
#include <utility>
#include <algorithm>
using namespace std;

/* A function to sort the elements in the vector by frquency,
 * if the frquency is same, they will be sorted in 
 * alphabetical order
 */
bool sortbyFreq(const pair<string, unsigned int> &a, const pair<string, unsigned int> &b)
{
    if(a.second==b.second)
    {
	return (a.first < b.first);
    }
    else
    {
	return (a.second > b.second);
    }
}
/**
 *  You may implement this class as either a mulit-way trie
 *  or a ternary search trie.
 */
class Autocomplete
{
protected:
   TST* tst;
public:

  /* 
  Create an Autocomplete object.
  This object should be trained on the words vector
  That is - the predictCompletions() function below should pull autocomplete
  suggestions from this vector

  Input: words. Must be all lowercase, with most  non-word characters removed (e.g. ',' ';' '%' etc.)
  In addition to alphabetic characters, words may contain digits, single apostrophes, dashes etc.
  */
  Autocomplete(const vector<string> words) {
    tst = new TST(words);
  }
  /* Return up to 10 of the most frequent completions
   * of the prefix, such that the completions are words in the dictionary.
   * These completions should be listed from most frequent to least.
   * If there are fewer than 10 legal completions, this
   * function returns a vector with as many completions as possible.
   * Otherwise, 10 completions should be returned.
   * If no completions exist, then the function returns a vector of size 0.
   * The prefix itself might be included in the returned words if the prefix
   * is a word (and is among the 10 most frequent completions
   * of the prefix)
   * If you need to choose between two or more completions which have the same frequency,
   * choose the one that comes first in alphabetical order.
   *
   * Inputs: prefix. The prefix to be completed. Must be of length >= 1.
   * Return: the vector of completions
   */
  vector<string> predictCompletions(const string prefix) {
    if(prefix.length() == 0) 
    {
	return {};
    }
    vector< pair <string, unsigned int> > completions;
    vector<string> retContainer;
    string newPrefix = prefix;
    TrieNode* prefixRoot = this->tst->find(prefix);
    if(prefixRoot!=0 && prefixRoot->end==true)
    {
        completions.push_back(make_pair(prefix, prefixRoot->frequency));
    }
    if(prefixRoot!=0 && prefixRoot->middle!=0)
    {
        prefixRoot = prefixRoot->middle;
        newPrefix = (newPrefix+ (prefixRoot->data));
    }
    inorder(prefixRoot, newPrefix, completions);
    sort(completions.begin(), completions.end(), sortbyFreq);
    if(completions.size()>10)
    {
        completions.resize(10);
    }
    /*for(auto str : completions)
    {
	cout << str.first << " " << str.second << endl;

    }*/
    for( auto str :  completions)
    {	
        if(retContainer.size()>0)
	{
	    if(retContainer.back() != str.first)
	    {
	        retContainer.push_back(str.first);
	    }

	}
	else
	{
	    retContainer.push_back(str.first);
	}
    }
    return retContainer;
  }

  /* Destructor */
  ~Autocomplete() {
    delete this->tst;
  }


private:
    /* A helper function to find all possible words from a given node 
     * and store them in a vector along with the word's frequency
     */
    void inorder(TrieNode* node, string prefixBuffer, vector< pair<string, unsigned int> > & completions)
    {
        if(!node) return;
        if(node->left)
        {
            inorder(node->left, prefixBuffer.substr(0, prefixBuffer.size()-1)+node->left->data, completions);
        }  
        if(node->end)
        {
            completions.push_back( make_pair(prefixBuffer, node->frequency));
	}
        if(node->middle) 
        {
            inorder(node->middle, (prefixBuffer + node->middle->data), completions);
        }
        if(node->right)
        {
            inorder(node->right, prefixBuffer.substr(0,prefixBuffer.size()-1)+node->right->data, completions);
        }
    }
};





#endif // AUTOCOMPLETE_HPP
