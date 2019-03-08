#ifndef TST_HPP
#define TST_HPP
#include "TrieNode.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class TST {

protected:
  /** Pointer to the root of this BST, or 0 if the BST is empty */
  TrieNode* root;


public:
 //Default Constructor
  TST() : root(0){}
  
  TST(const vector<string>& words)
  {
  	this->build(words);
  }

//Default destructor
  virtual ~TST() 
  {
    deleteAll(root);
  }

//find a word and it returns the end node of the word.
    TrieNode* find(const string & word)
    {
        if(word.empty()) return 0;
        TrieNode* curr = this->root;
        unsigned int index = 0;
        unsigned int length = word.length();
        char letter = word[index];
        while(curr)
        {
	    if(letter < curr->data)
            {
		if(curr->left) curr = curr->left;
                else
                {
                    return 0;
                }
            }
            else if(letter > curr->data)
            {
                if(curr->right) curr = curr->right;
                else
                {
                    return 0;
                }
            }
            else //letter == curr->data
            {
		if(letter == word[length-1] && (index==length-1))
                {
		     return curr;
                }
		else if (curr->middle!=0)
                {
		    curr = curr->middle;
		    letter = word[++index];
		}
		else
                {
		    return 0;
                }
            }
        }
        return 0;
    }

private:

	void build(const vector<string> words)
  	{
  		if(words.empty()) return;
  		this->root = 0;
		for(string str : words)
  		{
  			unsigned int wordLen = str.length();
            		this->root = insertWord(this->root, str, 0, wordLen);
  		}
  	}

	TrieNode* insertWord(TrieNode* currNode, string & word, unsigned int letterIndex, const unsigned int& wordLength)
	{
        if(word.length() == 0) return 0;

	char letter = word[letterIndex];
       
	if(!currNode)
	{
	        currNode = new TrieNode(letter);	
	}
	    
    	if((unsigned int)letter < (unsigned int)currNode->data)
	{
		currNode->left = insertWord(currNode->left, word, letterIndex, wordLength);
	} 
        
	else if((unsigned int)letter > (unsigned int)currNode->data)
	{
			
		currNode->right = insertWord(currNode->right, word, letterIndex, wordLength);
	}
        
	else if(letterIndex < wordLength-1)
	{
 		  
		currNode->middle = insertWord(currNode->middle, word, ++letterIndex, wordLength);
	}
        
	else// if(letterIndex == wordLength-1) 
	{
		if(currNode->end)
		{
			++(currNode->frequency);
		}
            	else
		{
			currNode->end = true;
		}
	}
		
	    return currNode;
	
	}
	
	/* A helper function to delete all nodes of 
 	 * the given ternary trie
 	 */  
	static void deleteAll(TrieNode* n)
  	{
    		if(!n) return;
        	deleteAll(n->left);
    		deleteAll(n->middle);
    		deleteAll(n->right);
    		delete n;
  	}

};
#endif //TST_HPP
	
