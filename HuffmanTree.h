#ifndef CS1D_ASSIGNMENT5_BINARYTREE_BINARYTREE_H
#define CS1D_ASSIGNMENT5_BINARYTREE_BINARYTREE_H

#include <stddef.h>
#include <iostream>
#include <iomanip>
#include <deque>
#include <math.h>
#include <sstream>
#include <fstream>

class HuffmanTree
{
private:

    struct Node
    {
        unsigned int freq;
        unsigned char c;
        Node *left;
        Node *right;

        Node(void)
            : freq(0), c('\0'), left(NULL), right(NULL)
        { }
    };

public:
    HuffmanTree();

    ~HuffmanTree();

    const HuffmanTree &operator=(const HuffmanTree &);

    HuffmanTree(const HuffmanTree &otherTree);

    //Accessors
    bool isEmpty() const;

    void inorderTraversal() const;

    void preorderTraversal() const;

    void postorderTraversal() const;

    int treeHeight() const;

    unsigned char getChar() const;

    unsigned int getFreq() const;

    std::string decode(std::string file) const;

//    int treeNodeCount() const;
//
//    int treeLeavesCount() const;

    Node *getRoot() const;

    void getHuffCode(Node *node, unsigned char c, std::string str, std::string &s) const;

    //Mutators
    void burnTree();

    void setFreq(unsigned int freq);

    void setChar(unsigned char ch);

    void setLeft(Node *node);

    void setRight(Node *node);

    struct comp
    {
        bool operator()(const HuffmanTree *h1, const HuffmanTree *h2) const
        {
            return h1->getFreq() < h2->getFreq();
        }
    };

    /**
* Helper function for printing the binary tree to console
*/
    void padding(char ch, int n)
    {
        int i;
        for (i = 0; i < n; i++)
            putchar(ch);
    }

/**
 * Prints a binary tree to the console. Tree is rotated 90 degrees
 * to make it easier to print.
 */
    void printTree(Node *root, int level = 0)
    {
        int i;
        if (root == NULL)
        {
            padding('\t', level);
            puts("-");
        }
        else
        {
            printTree(root->right, level + 1);
            padding('\t', level);
            printf("%c, %d\n", root->c, root->freq);
//            if(root->c == '\0'){ padding ('\t', level); puts ( "-" ); }
            printTree(root->left, level + 1);
        }
    }


private:

    Node *root;

    void copyTree(Node *&copiedTreeRoot, Node *otherTreeRoot);

    void burn(Node *&p);

    void inorder(Node *p) const;

    void preorder(Node *p) const;

    void postorder(Node *p) const;

    int height(Node *p) const;

    int max(int x, int y) const;

//    int nodeCount(Node *p) const;
//
//    int leavesCount(Node *p) const;
};

#endif //CS1D_ASSIGNMENT5_BINARYTREE_BINARYTREE_H


bool HuffmanTree::isEmpty() const
{
    return (root == NULL);
}


HuffmanTree::HuffmanTree()
{
    root = new Node;
}


void HuffmanTree::inorderTraversal() const
{
    inorder(root);
}


void HuffmanTree::preorderTraversal() const
{
    preorder(root);
}


void HuffmanTree::postorderTraversal() const
{
    postorder(root);
}


int HuffmanTree::treeHeight() const
{
    return height(root);
}


//int HuffmanTree::treeNodeCount() const
//{
//  return nodeCount(root);
//}


//int HuffmanTree::treeLeavesCount() const
//{
//  return leavesCount(root);
//}


void HuffmanTree::inorder(Node *p) const
{
    if (p != NULL)
    {
        inorder(p->left);
        std::cout << p->c << '(' << p->freq << ')' << " ";
        inorder(p->right);
    }
}


void HuffmanTree::preorder(Node *p) const
{
    if (p != NULL)
    {
        std::cout << p->c << '(' << p->freq << ')' << " ";
        preorder(p->left);
        preorder(p->right);
    }
}


void HuffmanTree::postorder(Node *p) const
{
    if (p != NULL)
    {
        postorder(p->left);
        postorder(p->right);
        std::cout << p->c << '(' << p->freq << ')' << " ";
    }
}

int HuffmanTree::height(Node *p) const
{
    if (p == NULL)
        return 0;
    else
        return 1 + max(height(p->left), height(p->right));
}


int HuffmanTree::max(int x, int y) const
{
    if (x >= y)
        return x;
    else
        return y;
}


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


void HuffmanTree::burnTree()
{
    burn(root);
}


HuffmanTree::HuffmanTree(const HuffmanTree &otherTree)
{
    if (otherTree.root == NULL)
        root = NULL;
    else
        copyTree(root, otherTree.root);
}


HuffmanTree::~HuffmanTree()
{
    burn(root);
}


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

void HuffmanTree::setFreq(unsigned int freq)
{
    root->freq = freq;
}

HuffmanTree::Node *HuffmanTree::getRoot() const
{
    return root;
}

void HuffmanTree::setChar(unsigned char ch)
{
    root->c = ch;
}

void HuffmanTree::setLeft(Node *node)
{
    root->left = node;
}

void HuffmanTree::setRight(Node *node)
{
    root->right = node;
}

unsigned char HuffmanTree::getChar() const
{
    return root->c;
}

unsigned int HuffmanTree::getFreq() const
{
    return root->freq;
}

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

std::string HuffmanTree::decode(std::string file) const
{
    std::ostringstream out;
    std::ifstream fin;
    fin.open(file.c_str());
    std::string code;
    fin >> code;

    Node *node = root;


    for (char c : code)
    {
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
















