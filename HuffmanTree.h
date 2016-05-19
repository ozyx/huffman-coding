/**************************************************************************
 * AUTHOR: Jesse Mazzella
 * CLASS : CS1D
 * DATE  : 05-16-2016
 * ASSIGN: Huffman Coding Extra Credit
 *************************************************************************/
#ifndef CS1D_ASSIGNMENT5_BINARYTREE_BINARYTREE_H
#define CS1D_ASSIGNMENT5_BINARYTREE_BINARYTREE_H

#include <stddef.h>
#include <iostream>
#include <iomanip>
#include <deque>
#include <math.h>
#include <sstream>
#include <fstream>

/**
 * @class HuffmanTree
 * @author Jesse Mazzella
 */
class HuffmanTree
{
public:

    /**
     * A HuffmanTree Node containing a frequency value and character.
     */
    struct Node
    {
        unsigned int freq; //< frequency value
        unsigned char c;   //< character
        Node *left;        //< left child
        Node *right;       //< right child

        /// Default Constructor
        Node() : freq(0), c('\0'), left(NULL), right(NULL) {}
    };

    /// Default constructor
    HuffmanTree();

    /// Destructor
    ~HuffmanTree();

    /// Equate two HuffmanTrees
    const HuffmanTree &operator=(const HuffmanTree &);

    /// Copy Constructor
    HuffmanTree(const HuffmanTree &otherTree);

    //Accessors

    /// Check if the tree is empty
    bool isEmpty() const;

    /// Perform an inorder traversal from the root
    void inorderTraversal() const;

    /// Perform a preorder traversal from the root
    void preorderTraversal() const;

    /// Perform a postorder traversal from the root
    void postorderTraversal() const;

    /// Retrieve the height of the tree
    int treeHeight() const;

    /// Get the character value stored at the root
    unsigned char getChar() const;

    /// Get the frequency value stored at the root
    unsigned int getFreq() const;

    /// Decode a Huffman Code using this tree
    std::string decode(std::string file) const;

    /// Retrieve a pointer to the root of the tree
    Node *getRoot() const;

    /// Get the Huffman Code for a particular character stored in the tree
    void getHuffCode(Node *node, unsigned char c, std::string str, std::string &s) const;

    //Mutators

    /// Clear the tree
    void burnTree();

    /// Set the frequency value of the tree root
    void setFreq(unsigned int freq);

    /// Set the character value of the tree root
    void setChar(unsigned char ch);

    /// Set the left child of the root of the tree
    void setLeft(Node *node);

    /// Set the right child of the root of the tree
    void setRight(Node *node);

    /// Comparator for comparing two Huffman Trees
    struct comp
    {
        bool operator()(const HuffmanTree *h1, const HuffmanTree *h2) const
        {
            return h1->getFreq() < h2->getFreq();
        }
    };

    /// Helper function for printing the tree
    void padding(char ch, int n);

    /// Print the tree (rotated 90 degrees)
    void printTree(Node *root, int level = 0);

private:

    /// Pointer to the root of the tree
    Node *root;

    /// Copy one tree into another
    void copyTree(Node *&copiedTreeRoot, Node *otherTreeRoot);

    /// Delete a node and its children
    void burn(Node *&p);

    /// Perform an inorder traversal from a given Node
    void inorder(Node *p) const;

    /// Perform a preorder traversal from a given Node
    void preorder(Node *p) const;

    /// Perform a postorder traversal from a given Node
    void postorder(Node *p) const;

    /// Retrieve the height from a given Node
    int height(Node *p) const;

    /// Compare two values and return the greater of the two
    int max(int x, int y) const;

};

#endif //CS1D_ASSIGNMENT5_BINARYTREE_BINARYTREE_H

/**
 * @brief HuffmanTree::isEmpty
 * Check if the HuffmanTree has any nodes in it.
 * @author Jesse Mazzella
 * @return true if the tree is empty
 */
bool HuffmanTree::isEmpty() const
{
    return (root == NULL);
}

/// Default Constructor
HuffmanTree::HuffmanTree()
{
    root = new Node;
}

/**
 * @brief inorderTraversal
 * Perform an inorder traversal.
 * @author Jesse Mazzella
 */
void HuffmanTree::inorderTraversal() const
{
    inorder(root);
}

/**
 * @brief preorderTraversal
 * Perform a preorder traversal.
 * @author Jesse Mazzella
 */
void HuffmanTree::preorderTraversal() const
{
    preorder(root);
}

/**
 * @brief postorderTraversal
 * Perform a postorder traversal.
 * @author Jesse Mazzella
 */
void HuffmanTree::postorderTraversal() const
{
    postorder(root);
}

/**
 * @brief HuffmanTree::treeHeight
 * @author Jesse Mazzella
 * @return the height from the root of the tree
 */
int HuffmanTree::treeHeight() const
{
    return height(root);
}

/**
 * @brief HuffmanTree::inorder
 * Perform and print an inorder traversal starting from a given Node.
 * @author Jesse Mazzella
 * @param p The node to begin the inorder traversal from
 */
void HuffmanTree::inorder(Node *p) const
{
    if (p != NULL)
    {
        inorder(p->left);
        std::cout << p->c << '(' << p->freq << ')' << " ";
        inorder(p->right);
    }
}

/**
 * @brief HuffmanTree::preorder
 * Perform and print a preorder traversal starting from a given Node.
 * @author Jesse Mazzella
 * @param p The node to begin the preorder traversal from
 */
void HuffmanTree::preorder(Node *p) const
{
    if (p != NULL)
    {
        std::cout << p->c << '(' << p->freq << ')' << " ";
        preorder(p->left);
        preorder(p->right);
    }
}

/**
 * @brief HuffmanTree::postorder
 * Perform and print a postorder traversal starting from a given Node.
 * @author Jesse Mazzella
 * @param p The node to begin the postorder traversal from
 */
void HuffmanTree::postorder(Node *p) const
{
    if (p != NULL)
    {
        postorder(p->left);
        postorder(p->right);
        std::cout << p->c << '(' << p->freq << ')' << " ";
    }
}

/**
 * @brief HuffmanTree::height
 * Retrieve the height of the HuffmanTree starting at a certain node.
 * @author Jesse Mazzella
 * @param p The node to find the height from.
 */
int HuffmanTree::height(Node *p) const
{
    if (p == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + max(height(p->left), height(p->right));
    }
}

/**
 * @brief HuffmanTree::max
 * @author Jesse Mazzella
 * @param x
 * @param y
 * @return the element with the higher value
 */
int HuffmanTree::max(int x, int y) const
{
    if (x >= y)
    {
        return x;
    }
    else
    {
        return y;
    }
}

/**
 * @brief HuffmanTree::copyTree
 * Copy a huffman tree.
 * @author Jesse Mazzella
 * @param copiedTreeRoot The tree to copy
 * @param otherTreeRoot The tree to copy into
 */
void HuffmanTree::copyTree(Node *&copiedTreeRoot,
                           Node *otherTreeRoot)
{
    if (otherTreeRoot == NULL)
        copiedTreeRoot = NULL;
    else
    {
        copiedTreeRoot = new Node;
        copiedTreeRoot->freq = otherTreeRoot->freq;
        copiedTreeRoot->c = otherTreeRoot->c;
        copyTree(copiedTreeRoot->left, otherTreeRoot->left);
        copyTree(copiedTreeRoot->right, otherTreeRoot->right);
    }
}

/**
 * @brief HuffmanTree::burn
 * Delete a node and its children
 * @author Jesse Mazzella
 * @param p The node to delete
 */
void HuffmanTree::burn(Node *&p)
{
    if (p != NULL)
    {
        burn(p->left);
        burn(p->right);
        delete p;
        p = NULL;
    }
}

/**
 * @brief HuffmanTree::burnTree
 * Delete the entire tree.
 * @author Jesse Mazzella
 */
void HuffmanTree::burnTree()
{
    burn(root);
}

/// Copy Constructor
HuffmanTree::HuffmanTree(const HuffmanTree &otherTree)
{
    if (otherTree.root == NULL)
    {
        root = NULL;
    }
    else
    {
        copyTree(root, otherTree.root);
    }
}

/// Destructor
HuffmanTree::~HuffmanTree()
{
    burn(root);
}

/// Overload '=' operator
const HuffmanTree &HuffmanTree::operator=(
    const HuffmanTree &otherTree)
{
    if (this != &otherTree)
    {
        if (root != NULL)
        {
            burn(root);
            if (otherTree.root == NULL)
            {
                root = NULL;
            }
            else
            {
                copyTree(root, otherTree.root);
            }
            return *this;
        }
    }
}

/**
 * @brief HuffmanTree::setFreq
 * Set the frequency value of the root of this HuffmanTree.
 * @author Jesse Mazzella
 * @param freq the frequency value to set
 */
void HuffmanTree::setFreq(unsigned int freq)
{
    root->freq = freq;
}

/**
 * @brief HuffmanTree::getRoot
 * Retrieve a pointer to the root of this HuffmanTree
 * @author Jesse Mazzella
 * @return a pointer to the root of the huffman tree.
 */
HuffmanTree::Node *HuffmanTree::getRoot() const
{
    return root;
}

/**
 * @brief HuffmanTree::setChar
 * Set the character value at the root to the passed in value
 * @author Jesse Mazzella
 * @param ch the character to set
 */
void HuffmanTree::setChar(unsigned char ch)
{
    root->c = ch;
}

/**
 * @brief HuffmanTree::setLeft
 * @author Jesse Mazzella
 * @param Set the left child of the root to point at another node
 */
void HuffmanTree::setLeft(Node *node)
{
    root->left = node;
}

/**
 * @brief HuffmanTree::setRight
 * @author Jesse Mazzella
 * @param Set the right child of the root to point at another node
 */
void HuffmanTree::setRight(Node *node)
{
    root->right = node;
}

/**
 * @brief HuffmanTree::getChar
 * @author Jesse Mazzella
 * @return The character value for the root of the tree.
 */
unsigned char HuffmanTree::getChar() const
{
    return root->c;
}

/**
 * @brief HuffmanTree::getFreq
 * @author Jesse Mazzella
 * @return The frequency value of the root of the tree.
 */
unsigned int HuffmanTree::getFreq() const
{
    return root->freq;
}

/**
 * @brief HuffmanTree::getHuffCode
 * Use the current Huffman Tree to generate a code for a particular
 * character.
 * @author Jesse Mazzella
 * @param node Node from which to start the binary search from.
 * @param c The character to search for.
 * @param str Procedurally build the huffman code with this string.
 * @param s Result will be passed by reference through this string.
 */
void HuffmanTree::getHuffCode(Node *node, unsigned char c, std::string str, std::string &s) const
{
    if (node != NULL)
    {
        if (node->c != '\0' && node->c == c)
        {
            s = str;
        }
        else
        {
            if (node->left != NULL)
            {
                getHuffCode(node->left, c, str + "0", s);
            }
            if (node->right != NULL)
            {
                getHuffCode(node->right, c, str + "1", s);
            }
        }
    }
}

/**
 * @brief HuffmanTree::decode
 * Read a file containing a Huffman code and decode it using this
 * Huffman tree.
 * @author Jesse Mazzella
 * @param file A string containing the filename of the file containing
 * the huffman code to decode.
 * @return The decoded huffman code as a c-string
 */
std::string HuffmanTree::decode(std::string file) const
{
    std::ostringstream out; //< output stream
    std::ifstream fin;      //< input file stream
    std::string code;       //< string to contain Huffman Code

    // Open the file containing the Huffman Code
    fin.open(file.c_str());

    // Read Huffman Code from file into string variable.
    fin >> code;

    // Create a new node and point it at the root of the Huffman tree
    Node *node = root;

    // For every character in the code, if it is a 0, traverse the tree
    // left. If it is a 1, traverse the tree right. When a character is
    // found, output the character to the output stream and start at
    // the root of the tree again.
    for (char c : code)
    {
        // If node has no children, output character and go to the root.
        if (node->left == NULL && node->right == NULL)
        {
            out << node->c;
            node = root;
        }

        if (c == '0')
        {
            node = node->left;
        }
        else if (c == '1')
        {
            node = node->right;
        }
    }

    out << node->c;

    return out.str().c_str();
}

/**
* Helper function for printing the binary tree to console
*/
void HuffmanTree::padding(char ch, int n)
{
    int i;
    for (i = 0; i < n; i++)
        putchar(ch);
}

/**
 * Prints a binary tree to the console. Tree is rotated 90 degrees
 * to make it easier to print.
 */
void HuffmanTree::printTree(Node *root, int level)
{
    if (root == NULL)
    {
        padding('\t', level);
        puts("-");
    }
    else
    {
        printTree(root->right, level + 1);
        padding('\t', level);
        if(root->c == '\0')
        {
            printf("(%d)\n", root->freq);
        }
        else
        {
            printf("[%c](F:%d)\n", root->c, root->freq);
        }

        printTree(root->left, level + 1);
    }
}