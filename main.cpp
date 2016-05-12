#include <iostream>
#include <set>
#include "HuffmanTree.h"
#include "Heap.h"

using namespace std;

int main()
{
    HuffmanTree *huf = new HuffmanTree();
    Heap<HuffmanTree*, HuffmanTree::comp> hufHeap;
    int frequencies[256] = {0};
    set<char> charSet;

    string input ="Four score and seven years ago our fathers brought forth"
        " on this continent, a new nation, conceived in Liberty, and "
        "dedicated to the proposition that all men are created equal."
        "Now we are engaged in a great civil war, testing whether that "
        "nation, or any nation so conceived and so dedicated, can long endure. "
        "We are met on a great battle-field of that war. We have come to "
        "dedicate a portion of that field, as a final resting place for "
        "those who here gave their lives that that nation might live. It is"
        " altogether fitting and proper that we should do this."
        "But, in a larger sense, we cannot dedicate -- we cannot consecrate"
        " -- we cannot hallow -- this ground. The brave men, living and "
        "dead, who struggled here, have consecrated it, far above our poor "
        "power to add or detract. The world will little note, nor long "
        "remember what we say here, but it can never forget what they did "
        "here. It is for us the living, rather, to be dedicated here to the"
        " unfinished work which they who fought here have thus far so nobly"
        " advanced. It is rather for us to be here dedicated to the great "
        "task remaining before us -- that from these honored dead we take "
        "increased devotion to that cause for which they gave the last full "
        "measure of devotion -- that we here highly resolve that these dead "
        "shall not have died in vain -- that this nation, under God, shall "
        "have a new birth of freedom -- and that government of the people, "
        "by the people, for the people, shall not perish from the earth.";

    for(char c: input){
        charSet.insert(c);
        frequencies[c]++;
    }

    for(char c : charSet){
        huf = new HuffmanTree();
        huf->setChar(c);
        huf->setFreq(frequencies[c]);
        hufHeap.insert(huf);
    }

    HuffmanTree *left;
    HuffmanTree *right;
    while(hufHeap.size() > 1)
    {
        left  = hufHeap.removeMin();
        right = hufHeap.removeMin();
        huf = new HuffmanTree();
        huf->setLeft(left->getRoot());
        huf->setRight(right->getRoot());
        huf->setFreq(left->getFreq() + right->getFreq());
        hufHeap.insert(huf);
    }

    huf = hufHeap.removeMin();

//    huf->printTree(huf->getRoot());

    huf->inorderTraversal();



    return 0;
}