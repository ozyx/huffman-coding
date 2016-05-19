/**************************************************************************
 * AUTHOR: Jesse Mazzella
 * CLASS : CS1D
 * DATE  : 05-16-2016
 * ASSIGN: Huffman Coding Extra Credit
 *************************************************************************/
#include <iostream>
#include <set>
#include "HuffmanTree.h"
#include "Heap.h"
#include <iomanip>
#include <map>
#include <fstream>
#include <queue>
#include <list>
using namespace std;
/**************************************************************************
 * EXTRA CREDIT - HUFFMAN CODING
 * ------------------------------------------------------------------------
 *
 *************************************************************************/
int main()
{
    HuffmanTree *tree; ///< a binary tree used for huffman coding
    Heap<HuffmanTree *, HuffmanTree::comp> hufHeap; // A minHeap sorting by frequency
    int frequencies[128] = {0}; // 128 size int array.. one for each ASCII value
    set<char> charSet; // A set of chars to find how many unique characters in input
    int compressed = 0; // initialize
    string str = ""; // initialize

    string input = "Four score and seven years ago our fathers brought forth"
        " on this continent, a new nation, conceived in Liberty, and "
        "dedicated to the proposition that all men are created equal. "
        "Now we are engaged in a great civil war, testing whether that "
        "nation, or any nation so conceived and so dedicated, can long endure. "
        "We are met on a great battle-field of that war. We have come to "
        "dedicate a portion of that field, as a final resting place for "
        "those who here gave their lives that that nation might live. It is"
        " altogether fitting and proper that we should do this. "
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

    int uncompressed = input.length() * 8; // Calculate amount of bits uncompressed
                                           // 1 character = 8 bits

    // Insert all characters in the input string into a set, and
    // increment the frequency value for each.
    for (char c: input)
    {
        charSet.insert(c);
        frequencies[c]++;
    }

    // For every character in the set, create a treeNode containing
    // that character and its frequency, and add it to a minHeap.
    for (char c : charSet)
    {
        tree = new HuffmanTree();
        tree->setChar(c);
        tree->setFreq(frequencies[c]);
        hufHeap.insert(tree);
    }

    // Left child
    HuffmanTree *left;
    // Right child
    HuffmanTree *right;

    // Build a huffman tree
    // Remove top two from the heap and create a new node with
    // frequency (left.freq + right.freq). Then make the lesser the left
    // child and the other the right child. Add it back into the heap
    // until heap size == 1.
    while (hufHeap.size() > 1)
    {
        left = hufHeap.removeMin();
        right = hufHeap.removeMin();
        tree = new HuffmanTree();
        tree->setLeft(left->getRoot());
        tree->setRight(right->getRoot());
        tree->setFreq(left->getFreq() + right->getFreq());
        hufHeap.insert(tree);
    }

    // Retrieve the newly constructed huffman tree.
    tree = hufHeap.removeMin();

    // Print the tree
    tree->printTree(tree->getRoot());


    // For every character in the set, find it in the huffman tree.
    // Determine the Huffman Code for each character.
    cout << "character" << setw(15) << "frequency" << setw(15) << "huffman code" << endl;
    for (char c : charSet)
    {
        tree->getHuffCode(tree->getRoot(), c, "", str);
        // increment number of compressed bits
        compressed += (str.length() * frequencies[c]);
//        printf("%10c - %10d\n", c, frequencies[c]);
        cout << '\'' << c << '\'' << ' ' << ',' << ' ' << setw(15) <<
        frequencies[c] << " - " << setw(15) << str << endl;
    }

    std::ostringstream out; // Create output stream

    // For every character in the input string, translate it into
    // a string of huffman code and append to the output stream.
    for (char c : input)
    {
        tree->getHuffCode(tree->getRoot(), c, "", str);
        out << str.c_str();
    }

    // write encoded string to file
    ofstream fout;
    fout.open("output.txt");
    fout << out.str();
    fout.close();
//    huf->inorderTraversal();

    // Decode the Huffman code and output it.
    cout << endl;
    cout << "DECODED HUFFMAN CODE:" << endl;
    cout << tree->decode("output.txt");

    // Calculate compression ratio.
    float ratio = (compressed / float(uncompressed)) * 100;

    cout << std::endl;
    cout << "\nuncompressed bits: " << uncompressed;
    cout << "\ncompressed bits: " << compressed;
    cout << "\ncompression ratio: " << ratio << '%';


    return 0;
}

