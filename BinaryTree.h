/**************************************************************************
 * AUTHOR : Jesse Mazzella
 * CLASS  : CS1D
 * DATE   : 2-24-2016
 * ASSIGN5: Binary Trees
 *************************************************************************/
#ifndef CS1D_ASSIGNMENT5_BINARYTREE_BINARYTREE_H
#define CS1D_ASSIGNMENT5_BINARYTREE_BINARYTREE_H

#include <stddef.h>
#include <iostream>
#include <iomanip>


template<class T>
struct Node
{
    T value;
    Node<T> *left;
    Node<T> *right;
};

template<class T>
class BinaryTree
{
public:
    const BinaryTree<T> &operator=(const BinaryTree<T> &);

    bool isEmpty() const;

    void inorderTraversal() const;

    void preorderTraversal() const;

    void postorderTraversal() const;

    int treeHeight() const;

    int treeNodeCount() const;

    int treeLeavesCount() const;

    void burnTree();

    virtual bool search(const T &searchItem) const = 0;

    virtual void insert(const T &insertItem) = 0;

    virtual void deleteNode(const T &deleteItem) = 0;

    BinaryTree(const BinaryTree<T> &otherTree);

    void printTree() const;

    BinaryTree();

    ~BinaryTree();

protected:
    Node<T> *root;

private:
    void copyTree(Node<T> *&copiedTreeRoot, Node<T> *otherTreeRoot);

    void burn(Node<T> *&p);

    void inorder(Node<T> *p) const;

    void preorder(Node<T> *p) const;

    void printTreePrivate(Node<T> *p, int indent = 0) const;

    void postorder(Node<T> *p) const;

    int height(Node<T> *p) const;

    int max(int x, int y) const;

    int nodeCount(Node<T> *p) const;

    int leavesCount(Node<T> *p) const;
};

#endif //CS1D_ASSIGNMENT5_BINARYTREE_BINARYTREE_H

template<class T>
bool BinaryTree<T>::isEmpty() const
{
  return (root == NULL);
}

template<class T>
BinaryTree<T>::BinaryTree()
{
  root = NULL;
}

template<class T>
void BinaryTree<T>::inorderTraversal() const
{
  inorder(root);
}

template<class T>
void BinaryTree<T>::preorderTraversal() const
{
  preorder(root);
}

template<class T>
void BinaryTree<T>::postorderTraversal() const
{
  postorder(root);
}

template<class T>
int BinaryTree<T>::treeHeight() const
{
  return height(root);
}

template<class T>
int BinaryTree<T>::treeNodeCount() const
{
  return nodeCount(root);
}

template<class T>
int BinaryTree<T>::treeLeavesCount() const
{
  return leavesCount(root);
}

template<class T>
void BinaryTree<T>::inorder(Node<T> *p) const
{
  if (p != NULL)
  {
    inorder(p->left);
    std::cout << p->value << " ";
    inorder(p->right);
  }
}

template<class T>
void BinaryTree<T>::preorder(Node<T> *p) const
{
  if (p != NULL)
  {
    std::cout << p->value << " ";
    preorder(p->left);
    preorder(p->right);
  }
}

template<class T>
void BinaryTree<T>::postorder(Node<T> *p) const
{
  if (p != NULL)
  {
    postorder(p->left);
    postorder(p->right);
    std::cout << p->value << " ";
  }
}

template<class T>
void BinaryTree<T>::printTree() const
{
  printTreePrivate(this->root);
}

template<class T>
int BinaryTree<T>::height(Node<T> *p) const
{
  if (p == NULL)
    return 0;
  else
    return 1 + max(height(p->left), height(p->right));
}

template<class T>
int BinaryTree<T>::max(int x, int y) const
{
  if (x >= y)
    return x;
  else
    return y;
}

template<class T>
void BinaryTree<T>::copyTree(Node<T> *&copiedTreeRoot,
                             Node<T> *otherTreeRoot)
{
  if (otherTreeRoot == NULL)
    copiedTreeRoot = NULL;
  else
  {
    copiedTreeRoot = new Node<T>;
    copiedTreeRoot->value = otherTreeRoot->value;
    copyTree(copiedTreeRoot->left, otherTreeRoot->left);
    copyTree(copiedTreeRoot->right, otherTreeRoot->right);
  }
}

template<class T>
void BinaryTree<T>::burn(Node<T> *&p)
{
  if (p != NULL)
  {
    burn(p->left);
    burn(p->right);
    delete p;
    p = NULL;
  }
}

template<class T>
void BinaryTree<T>::burnTree()
{
  burn(root);
}

template<class T>
BinaryTree<T>::BinaryTree(const BinaryTree<T> &otherTree)
{
  if (otherTree.root == NULL)
    root = NULL;
  else
    copyTree(root, otherTree.root);
}

template<class T>
BinaryTree<T>::~BinaryTree()
{
  burn(root);
}

template<class T>
const BinaryTree<T> &BinaryTree<T>::operator=(
    const BinaryTree<T> &otherTree)
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

template<class T>
void BinaryTree<T>::printTreePrivate(Node<T> *p, int indent) const
{
  if (p != NULL)
  {
    if (p->right)
    {
      printTreePrivate(p->right, indent + 2);
    }
    if (indent)
    {
      std::cout << std::setw(indent) << ' ';
    }
    if (p->right)
    {
      std::cout << "/\n" << std::setw(indent) << ' ';
    }
  }
  std::cout << p->value << "\n ";
  if (p->left)
  {
    std::cout << std::setw(indent) << ' ' << "\\\n";
    printTreePrivate(p->left, indent + 2);
  }
}


