/**
 * CSE 100 PA2 SpeechBuilder
 * Author: Jonathan Margoliash
 */

#ifndef DOCUMENT_GENERATOR_HPP
#define DOCUMENT_GENERATOR_HPP
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <string.h>
using namespace std;

class DocumentGenerator
{
protected:
	unordered_map< string, vector<string>> wordsMap; 

public:   
 /**
 * Builds a document generator from the documents in the given directory
 * This should open all files in the directory, reads them in, tokenize them into words,
 * and build the datastructure from that stream of words.
 *
 * To tokenize a document:
 * * remove all UNWANTED_CHARACTERS from the document
 * * split it into different tokens based on whitespace (treat all whitespace breaks equally)
 * * additionally split each PUNCTUATION character into its own token (so a single period is a 'word')
 * * from here on, we'll use the word "word" to refer to both strings like "hello" and punctuation strings like "." or ","
 *
 * So, for instance, the short sentence
 * "I like trains. Sally ju^mped over the moon, I think? I. I think."
 * Would be tokenized into ["I", "like", "trains", ".", "Sally",
 *   "jumped", "over", "the", "moon", ",", "I", "think", "?", "I", ".", "I" "think", "."]
 * and the frequencies of the words after "I" would be;
 *  like - 1
 *  think - 2
 *  . - 1
 *
 * You may use the utilities in AutocompleteUtils to help you with this
 * and you may rely on them working.
 * Note however that they do not deal with unwanted characters or split punctuation appropriately.
  * 
 * A few notes:
 * 1) you must treat words with different capitalizatoins differently
 * * (so "foo" and "Foo" are different words, and the frequencies of the words that follow (or precede)
 * * "foo" will be different than the frequencies of the words that follow (or precede) "Foo" )
 * 2) pretend that the first word in the document is preceeded by a periood (That way, it is considered when starting any new sentence)
 */
  DocumentGenerator(const string documentsDirectory) {
        const char* p = documentsDirectory.c_str();    
        DIR *dir;
	struct dirent *ent;
	if((dir = opendir(p)) != NULL) {
		while((ent = readdir(dir)) != NULL) {
			if(strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
				string new_str = documentsDirectory + "/" +  ent->d_name;
				ifstream infile;
				infile.open(new_str);//file->d_name);
			 	vector<string>* words = new vector<string>();
                		if (!infile)
                		{	
                   			 cerr << "Couldn't open: " << documentsDirectory << endl;
                   			 exit(1);
                		}
                		string line;
                		while(getline(infile, line))
                		{
                    			vector<string> wordsInLine = tokenize(line);
                    			words->insert(words->end(), wordsInLine.begin(), wordsInLine.end());
                		}
				for(std::vector<string>::const_iterator it=words->begin(); it != (words->end()-1); ++it)
				{
					if(wordsMap.find(*it) == wordsMap.end())
					{
						wordsMap[*it] = vector<string>(1, *(it + 1));
					}
					else
					{
						wordsMap[*it].push_back(*(it + 1));	
					}
				}
			 	delete words;				
                		infile.close();
   			}
		}
		closedir(dir);
		//cout << "Loop: " << loop << endl;
	}
	else {
		cerr <<"" << endl;
		exit(1);
	}
	srand (time(NULL));
   }
        
  

  /**
 * Suppose you're in the middle of generating a document and that you've just added the word prevWord
 * to the document. generateNextWord(prevWord) should generate the next word at random for the document,
 * according to the frequencies of all the words that followed prevWord in the input documents
 *
 * So, for instance, if in all the input documents the word "foo" was followed by the word "bar" twice and "baz" 8 times,
 * then 80% of the time generateNextWord("foo") should return "baz" and 20% of the time you should return "bar".
 * 
 * This method should return punctuation words like "." and "," as if they were any other word.
 * Likewise, it should be able to take punctuation words as input (generateNextWord(","))
 * 
 * You can assume that prevWord is always a word that's present in one of the documents you've read in.
 */
  string generateNextWord(const string prevWord) {
    return wordsMap[prevWord][rand() % (wordsMap[prevWord].size())];
  }

  /**
 * Generate a document with numWords words in it.
 *
 * See the docs on generateNextWord for a description of what it means to generate a word.
 * After generating all the words - concatenate them all into a single string representing the entire document, and return that string.
 *
 * Notes:
 * The first word you generate should be as if the previous word was '.'
 * Your document should not contain whitespace except for spaces.
 * Your should insert a single space in front of each word except:
 * * Don't insert spaces in front of punctuation marks
 * * Don't insert a space at the start of the document
 * 
 * The document will likely not end at the end of a sentence. That's okay.
 */
  string generateDocument(const int numWords) {
    string retString = "";
    string prevStr = ".";
    srand (time(NULL));
    for(int i = 0; i < numWords; i++)
    {
	string randStr = this->generateNextWord(prevStr);
	if(!(PUNCTUATION.find(randStr) == string::npos) )
	{
		retString.pop_back();
        }
        retString.append(randStr);
	retString.append(" ");
        prevStr = randStr;   
    }
    return retString;
  }

  ~DocumentGenerator() {	
  
   }
  
  //Feel free to put your own code here

private:
  const string PUNCTUATION = ".!,?";
  const string UNWANTED_CHARACTERS = ";:\"~()[]{}\\/^_<>*=&%@$+|`";
  const string whitespace = " \t\r\n\v\f";
  //Feel free to put your own code here

    //break a line over whitespace separators
    vector<string> tokenize(const string line) 
    {
	vector<string> words;
        vector<char> word;
        for (unsigned char c : line) 
        {
            if(PUNCTUATION.find(c) != string::npos)
            {
                if(word.size() > 0)
                {
                    words.push_back(string(word.begin(), word.end()));
                    word.clear();
                }
                words.push_back(string(1,c));
                //continue;
            }
	    else if(UNWANTED_CHARACTERS.find(c) != string::npos)
	    {
		continue;
	    }	
            else if (whitespace.find(c) == string::npos) 
            {
                word.push_back(c);
            }
            else if (word.size() > 0)
            {
		words.push_back(string(word.begin(), word.end()));
		word.clear();
            }
        }
        if (word.size() > 0) 
        {
            words.push_back(string(word.begin(), word.end()));
        }
        return words;
    }
    
};

#endif //DOCUMENT_GENERATOR_HPP

