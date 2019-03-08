#ifndef TRIENODE_HPP
#define TRIENODE_HPP
#include <iostream>
#include <iomanip>
using namespace std;

class TrieNode {

public:

    TrieNode(const char d) : data(d) {
        left = middle = right = 0;
        end = false;
        frequency = 1;
    }

    TrieNode* left;
    TrieNode* right;
    TrieNode* middle;
    bool end;
    char const data;
    unsigned int frequency;
};
#endif // TRIENODE_HPP
