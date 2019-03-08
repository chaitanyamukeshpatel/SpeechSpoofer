#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include "TST.cpp"
#include "TrieNode.hpp"
#include "Autocomplete.hpp"
#include "AutocompleteUtils.hpp"
using namespace std;

/**
 * A simple test driver for the BST class template.
 * P1 CSE 100 2013
 * Author: P. Kube (c) 2013
 */
int main() {

  /*Create an STL vector of some ints test*/
  vector<string> v;
  v.push_back("wasn't");
  v.push_back("mexican");
  v.push_back("apple");
  v.push_back("appleA");
  v.push_back("appleA");
  v.push_back("appleA");
  v.push_back("appleA");
  v.push_back("appleA");
  v.push_back("appleA");
  v.push_back("appleB");
  v.push_back("appleC");
  v.push_back("appleD");
  v.push_back("appleE");
  v.push_back("appleE");
  v.push_back("appleE");
  v.push_back("appleE");
  v.push_back("appleE");
  v.push_back("appleF");
  v.push_back("appl");
  v.push_back("appleA");
  v.push_back("appleB");
  v.push_back("appleC");
  v.push_back("appleD");
  v.push_back("bat");
  v.push_back("zebra");
  v.push_back("xmen");
  v.push_back("violion");
  v.push_back("apples");
  v.push_back("applesssss");
  v.push_back("mexican");	
  v.push_back("mexican");	
  v.push_back("mexican");	
  v.push_back("apples");
  v.push_back("zebbba");
  v.push_back("zxyy");  
  v.push_back("zeb1");
  v.push_back("zeb3");
  v.push_back("zeb89ad7");
  v.push_back("zet");
  v.push_back("zoez");
  v.push_back("zeol");
  v.push_back("zebl");
  v.push_back("zebraA");
  v.push_back("zebraB");
  v.push_back("zebraC");
  //TST tree = TST(v);
  //  TrieNode* node = tree.find("apple");
   // cout << "apple's last char : " << node->data << endl;
    //tree.find("appleaa");
  // Insert a few data items. 
 //tree.printoneWord(); 
    Autocomplete* myAutocomplete= new Autocomplete(v); 
    //Autocomplete myAC(v);
    //cout << "after creating a var myAutocomplete" << endl;
    vector<string> strContainer = myAutocomplete->predictCompletions("app");
    //vector<string> strContainer = myAC.predictCompletions("appl");
    for(auto str : strContainer)
    {
        cout << str << endl;
    }
    delete myAutocomplete;



  return 0;
}

