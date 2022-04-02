#ifndef AVL_H
#define AVL_H
//--------------------------------------------------------------------
// An AVL tree class
// Compiled under MS Visual C++.Net 2005
// by Paul Bladek
// May, 2008
//--------------------------------------------------------------------

#include "bst.h"
using namespace std;


namespace PB_BST
{
//--------------------------------------------------------------------
// AVL Tree
//   Class: avl<T>: public bst<T>
//   REQUIRES Type T be able convert from int & have < & == defined
//
//   File: avl.h
//   Title: avl template Class -- inherits from bst<T>
//   Description: This file contains the class definition for avl
//
//   Programmer:  Paul Bladek
// 
//   Date:  May 2008
//   Version: 1.0
// 
//   Environment: Hardware: IBM Pentium 
//   Software: Windows XP or .Net Framework for execution;
//
//   Compiles under Microsoft Visual C++.Net 2005
// 
//   class avl<T>:
//
//
//     Methods:
// 
//       inline: 
//			avl() -- default constructor
//			avl(const avl<T>& t) -- copy constructor (deep copy)
//			avl<T>& operator+=(const T d) -- adds an element to the tree
//			avl<T> operator+(const T d) -- adds an element to the tree
//			void insert(T d) -- adds an element to the tree
//			~avl() -- destructor	
//
//       non-inline:
//			avl<T>& operator=(const avl<T>& t) -- deep copy
//			avl<T>& operator+=(const avl<T>& t) -- adds an element to the tree
//			void insert(T d, node<T>* &cur) -- adds an element to the tree
//			T popnode(node<T>* &cur) -- returns element in node deleted
//			T poplow(node<T>* &cur) -- returns element in leftmost node (deleted)
//			T popfirst(const T& d, node<T>* np)
//				-- returns element in first node matching d (deleted)
//		protected:
//			node<T>* rotateRight(node<T> *nodeN) -- balances tree	
//			node<T>* rotateLeft(node<T> *nodeN) -- balances tree
//			node<T>* rotateRightLeft(node<T> *nodeN) -- balances tree
//			node<T>* rotateLeftRight(node<T> *nodeN) -- balances tree
//			node<T>* rebalance(node<T> *&nodeN) -- balances tree
//			int getHeightDifference(const node<T> *const nodeN)const
//				-- returns the height difference between the left & right subtrees 
//
//
//   History Log: 
//     May 20, 2008, PB  completed version 1.0 
//------------------------------------------------------------------- 
	template<class T>
	class avl: public bst<T>
	{    
	public:
		avl() : bst<T>(){}
		avl(const avl<T>& t) : bst<T>(t){}
		avl<T>& operator=(const avl<T>& t);
		avl<T>& operator+=(const avl<T>& t);
		avl<T>& operator+=(const T d){insert(d); return *this;}
		avl<T> operator+(const T d)
		{avl<T> temp = *this; temp.insert(d); return temp;}
		bool insert(T d) { return insert(d, bst<T>::root);}
		bool insert(T d, node<T>* &cur);
		T popnode(node<T>* &cur);
		T poplow(node<T>* &cur);
		T popfirst(const T& d, node<T>* np);
		~avl() { bst<T>::delTree();}
	protected:
		node<T>* rotateRight(node<T> *nodeN);	
		node<T>* rotateLeft(node<T> *nodeN);
		node<T>* rotateRightLeft(node<T> *nodeN);
		node<T>* rotateLeftRight(node<T> *nodeN);
		node<T>* rebalance(node<T> *&nodeN);
		int getHeightDifference(const node<T> *const nodeN)const;
	};

	//////////////////////////////////////////////////////////
	// Define function - inline function
	//////////////////////////////////////////////////////////
	template<class T>
	inline avl<T>& avl<T>::operator=(const avl<T>& t)
	{
		if (this != &t)
		{
			// Check current tree is empty or not. if not empty, clear tree
			if (!this->isempty())
				this->delTree(bst<T>::root);
			// Check the source tree empty or not
			if (!t.isempty())
			{
				bst<T>::root = new node<T>(*(t.root));
			}
		}
		return *this;
	}


	template<class T>
	inline avl<T>& avl<T>::operator+=(const avl<T>& t)
	{
		avl<T> tmp = t;
		while (!tmp.isempty())
		{
			T tmpValue = bst<T>::popNode(tmp.getroot());
			insert(tmpValue, this->root);
		}
		tmp.delTree();
		return *this;
	}

	template<class T>
	inline bool avl<T>::insert(T d, node<T>* &cur)
	{
		if (cur != nullptr)
		{
			if (d < cur->value())
			{
				insert(d, cur->left);
				rebalance(cur);
			}
			else if (d > cur->value())
			{
				insert(d, cur->right);
				rebalance(cur);
			}
			else
			{
				// Node was existed. Return false
				return false;
			}
			if (bst<T>::root != nullptr)
			{
				bst<T>::root->setHeight();
			}
		}
		else
		{
			cur = new node<T>(d);
			if (this->isempty())
			{
				bst<T>::root = cur;
			}
		}
		return true;
	}

	template<class T>
	T avl<T>::popnode(node<T>* &cur)
	{
		T conents = bst<T>::popNode(cur);
		rebalance(cur);
		return conents;
	}

	template<class T>
	T avl<T>::poplow(node<T>* &cur)
	{
		T conents = bst<T>::popLow(cur);
		rebalance(cur);
		return conents;
	}

	template<class T>
	T avl<T>::popfirst(const T& d, node<T>* np)
	{
		node<T>* parent = *bst<T>::parentptr;
		T contents = bst<T>::popFirstOf(d, np);
		rebalance(np);
		if (!contents)
		{
			return 0;
		}
		return contents;
	}

	template<class T>
	node<T>* avl<T>::rotateRight(node<T> *nodeN)
	{
		node<T> *tmp;
		tmp = nodeN->left;
		nodeN->left = tmp->right;
		tmp->right = nodeN;
		nodeN->setHeight();
		tmp->setHeight();
		return tmp;
	}

	template<class T>
	node<T>* avl<T>::rotateLeft(node<T> *nodeN)
	{
		node<T> *tmp;
		tmp = nodeN->right;
		nodeN->right = tmp->left;		
		tmp->left = nodeN;
		nodeN->setHeight();
		tmp->setHeight();
		return tmp;
	}

	template<class T>
	node<T>* avl<T>::rotateRightLeft(node<T> *nodeN)
	{
		node<T> *tmp;
		tmp = nodeN->right;
		nodeN->right = rotateRight(tmp);		
		return rotateLeft(nodeN);
	}

	template<class T>
	node<T>* avl<T>::rotateLeftRight(node<T> *nodeN)
	{
		node<T> *tmp;
		tmp = nodeN->left;		
		nodeN->left = rotateLeft(tmp);
		return rotateRight(nodeN);
	}

	template<class T>
	node<T>* avl<T>::rebalance(node<T> *&nodeN)
	{
		int balance = getHeightDifference(nodeN);
		if (nodeN == NULL)
			return nodeN;	
		if (balance > 1)
		{
			if (getHeightDifference(nodeN->left) > 0)
			{
				nodeN = rotateRight(nodeN);
			}
			else
			{
				nodeN = rotateLeftRight(nodeN);
			}
		}
		else if (balance < -1)
		{
			if (getHeightDifference(nodeN->right) < 0)
			{
				nodeN = rotateLeft(nodeN);
			}
			else
			{
				nodeN = rotateRightLeft(nodeN);
			}
		}
		return nodeN;
	}

	template<class T>
	int avl<T>::getHeightDifference(const node<T> *const nodeN)const
	{
		int leftHeight = 0;
		int rightHeight = 0;
		if (nodeN == nullptr)
			return 0;
		if (nodeN->left != nullptr)
			leftHeight = (nodeN->left)->getHeight();

		if (nodeN->right != nullptr)
			rightHeight = (nodeN->right)->getHeight();

		return leftHeight - rightHeight;
	}
}
#endif
