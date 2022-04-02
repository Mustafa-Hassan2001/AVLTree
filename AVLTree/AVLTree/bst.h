
#ifndef BST_H
#define BST_H
//--------------------------------------------------------------------
// A rudimentary Binary Search Tree program
// Compiled under MS Visual C++.Net 2005, 2010, 2013
// allows duplicates
// by Paul Bladek
// December, 2000
// revised April, 2005
// revised May, 2008
// revised May, 2012
// revised June, 2013
//--------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <exception>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

namespace PB_BST
{
	// CLASS DEFINITIONS 
	template<class T>
	//--------------------------------------------------------------------
	// BST NODE
	// REQUIRES Type T be able to convert from int & have < & == defined
	//--------------------------------------------------------------------
	class node
	{
	public: 
		node(T d = 1) : m_data(d), m_height(1), left(nullptr),
			right(nullptr){}
		node(const node<T>& n); // Copy Constructor
		node<T>& operator=(const node<T>& n);
		T value() const {return m_data;}    // Accessor
		operator T() const {return m_data;}  // cast to data type
		void setdata(T d) {m_data = d;}
		int getHeight() const {return m_height;}
		int setHeight();
	private: 
		T m_data;
		int m_height;
	public:  // to freely use these
		node<T>* left;
		node<T>* right;
	}; 

	//--------------------------------------------------------------------
	// COPY CONSTRUCTOR
	// throws bad_alloc
	//--------------------------------------------------------------------
	template <class T>
	node<T>::node(const node<T>& n)
		: m_data(n.m_data), m_height(n.getHeight()), left(nullptr),
			right(nullptr)	
	{
		if(n.left != nullptr)
			left = new node<T>(*(n.left));
		if(n.right != nullptr)
			right = new node<T>(*(n.right));
	}

	//--------------------------------------------------------------------
	// = operator
	// throws bad_alloc
	//--------------------------------------------------------------------
	template <class T>
	node<T>& node<T>::operator=(const node<T>& n)  // overloaded =
	{
	   if(this != &n)
	   {
		m_data = n.m_data;
		m_height = n.getHeight();
		if(n.left != nullptr)
			left = new node<T>(*(n.left));
		else
			left = nullptr;
		if(n.right != nullptr)
			right = new node<T>(*(n.right));
		else
			right = nullptr;
	   }
	   return *this;
	} 

	
	//--------------------------------------------------------------------
	// recursively sets the Height of the node
	//--------------------------------------------------------------------
	template <class T>
	int node<T>::setHeight()
	{
		int lHeight = 0;
		int rHeight = 0;
		m_height = 1;

		if(left != nullptr)	
			lHeight = left->setHeight();
		if(right != nullptr)
			rHeight = right->setHeight();
		return (m_height += (lHeight > rHeight) ? lHeight : rHeight);
	}

	//--------------------------------------------------------------------
	// Binary Search Tree -- Basic Implementation
	//--------------------------------------------------------------------
	template <class T>
	class bst
	{    
	public:
		bst() : root(nullptr), parentptr(&root) {}
		bst(const bst<T>& t) : root(nullptr), parentptr(&root)
			{if(t.root != nullptr) root = new node<T>(*(t.root));}
	
		node<T>* &getroot() {return root;}

	  	bool isempty() const {return (root == nullptr);}
	  
		bst<T>& operator=(const bst<T>& t);
		bst<T>& operator+=(const bst<T>& t);
		bst<T>& operator+=(const T d){insert(d, root); return *this;}
	 	bst<T> operator+(const T d) {bst<T> temp = *this;
			temp.insert(d, temp.root); return temp;}  
	  	void findFirstOf(const T& d, node<T>* &np, node<T>* &match);
	  	virtual bool insert(T d);
		void delTree() {delTree(root);}
		void print(ostream& out)const {print(root, out);}
		void print(node<T>* cur, ostream& out) const;
		void printXlevel(ostream& out) const {printXlevel(root, out);}
		void printXlevel(node<T>* cur, ostream& out) const;
		//void print(node<T>* cur, ostream& out, int level2print) const;
		T popNode(node<T>* &cur);
		T popLow(node<T>* &cur);
		T popHigh(node<T>* &cur);
		T popFirstOf(const T& d) {return popFirstOf(d, root);}
		T popFirstOf(const T& d, node<T>*& np);
		int getHeight() const
			{if(isempty()) return 0; return root->getHeight();}
		void setHeight() {if(root != nullptr) root->setHeight();}
		
		void setLevel(node<T>* cur, vector<T>& levelVector,
			int level2print, int position = 0) const;
		int getNumberOfNodes() const {return getNumberOfNodes(root);}
		int getNumberOfNodes(node<T>* np) const;
		~bst(){delTree(root);}
	protected:
	  	virtual bool insert(T d, node<T>* &cur);
		node<T>* root; // root of this tree
		node<T>** parentptr; // holding pointer needed by some functions

		virtual void addTree(const node<T>* np); // used by +
	protected:
		void delTree(node<T>* &cur);
	}; 

	//--------------------------------------------------------------------
	// overloaded =
	// throws bad_alloc
	//--------------------------------------------------------------------
	template <class T>
	bst<T>& bst<T>::operator=(const bst<T>& t)   
	{
		if(this != &t)
		{
			if(!isempty())
				delTree(root);
			if(!t.isempty())
			{
				root = new node<T>(*(t.root));
			}
		}
		return *this;
	}

	//--------------------------------------------------------------------
	// overloaded +=
	// throws bad_alloc
	//--------------------------------------------------------------------
	template <class T>
	bst<T>& bst<T>::operator+=(const bst<T>& t)   
	{
		addTree(t.root);
		return *this;
	}

	//--------------------------------------------------------------------
	// recursively adds in the contents of a second tree
	//--------------------------------------------------------------------
	template <class T>
	void bst<T>::addTree(const node<T>* np) 	
	{
		if(np != nullptr)
		{
			addTree(np->left);
			addTree(np->right);
			insert(np->value(), root);
		}
	}

	//--------------------------------------------------------------------
	// recursively finds the first occurance of a data item
	// pre: match must be set to nullptr
	//--------------------------------------------------------------------
	template <class T>
	void bst<T>::findFirstOf(const T& d, node<T>* &np, node<T>* &match)
	{
		if(match != nullptr)
			return;
		if(np != nullptr)
		{
			findFirstOf(d, np->left, match);
			if(d == np->value())
			{	
				match = np;
				parentptr = &np;
				return;
			}
			findFirstOf(d, np->right, match);
		}
	}

	//--------------------------------------------------------------------
	// inserts a new element
	// into the tree
	//--------------------------------------------------------------------
	template <class T>
	bool bst<T>::insert(T d)
	{
		return insert(d, root);
	}
	//--------------------------------------------------------------------
	// inserts a new element
	// into the tree
	// throws bad_alloc
	//--------------------------------------------------------------------
	template <class T>
	bool bst<T>::insert(T d, node<T>* &cur)
	{
		if(cur == nullptr)
		{                       
			cur = new node<T>(d);
			if(isempty())
				root = cur;
		}
		else
		{
			if (d < cur->value())
				insert(d, cur->left);
			else if (d > cur->value())
				insert(d, cur->right);
			else
				// MODIFY: Don't allow insert duplicate node.
				return false;
			if(root != nullptr)
				root->setHeight();
		}
		return true;
	} 

	//-------------------------------------------------------------------- 
	// recursively prints out the tree inorder
	//--------------------------------------------------------------------
	template <class T>
	void bst<T>::print(node<T>* cur, ostream& out) const 
	{
		if(cur != nullptr)
		{
			print(cur->left, out);
			out << cur->value() << "(" << cur->getHeight() << ") ";
			print(cur->right, out);
		}
	} 
	
	//------------------------------------------------------------------------
	// recursuively sets levelVector to represent the specified level 
	//------------------------------------------------------------------------
	template <class T>
	void bst<T>::setLevel(node<T>* cur, vector<T>& levelVector,
		int level2print, int position) const 
	{	
		static int currentLevel = -1;
		if(level2print < 0)
			return;
		if(cur != nullptr)
		{
			currentLevel++;
			if(currentLevel < level2print)
				setLevel(cur->left, levelVector, level2print, position * 2);
			if(currentLevel == level2print)
				levelVector[position] = cur->value();
			if(currentLevel < level2print)
				setLevel(cur->right, levelVector, level2print,
					position * 2 + 1);
			currentLevel--;
		}
	} 

	//------------------------------------------------------------------------ 
	// prints out the tree in level order
	// pre: -1 must be able to be cast to T
	//------------------------------------------------------------------------
	template <class T>
	void bst<T>::printXlevel(node<T>* cur, ostream& out) const 
	{	
		if(cur == nullptr)
			return;
		const size_t SPACER = 64;
		const T NO_NODE = static_cast<T>(-1);
		const int PRINT_MAX = 6;
		vector<vector<T>> treeVector(cur->getHeight());
		
		for(int i = 0; i < cur->getHeight(); i++)
		{
			out << "level " << i + 1 << ": ";
			if(i < PRINT_MAX)
			{
				int size = static_cast<int>(pow(2.0, i));
				treeVector[i] = vector<T>(size, NO_NODE);
				setLevel(cur, treeVector[i], i);
				out << string(SPACER / (2 * size), ' '); 
				for(int j = 0; j < static_cast<int>(treeVector[i].size());
					j++)
				{
					if(treeVector[i][j] != NO_NODE)
						out  << treeVector[i][j];
					else
						out  << ' ';
					out << string(SPACER / size - 1, ' ');
				}
			}
			else 
				out << "  . . .";
			
			out << endl;
		}
	} 

	//-------------------------------------------------------------------- 
	// recursively deletes out the subtree
	//--------------------------------------------------------------------
	template <class T>
	void bst<T>::delTree(node<T>* &cur)   
	{
		if(cur != nullptr)
		{
			delTree(cur->left);
			delTree(cur->right);
			delete cur;
			cur = nullptr;
			if(root != nullptr)
				root->setHeight();
		}
	} 

	//-------------------------------------------------------------------- 
	// pops a given node
	//--------------------------------------------------------------------
	template <class T>
	T bst<T>::popNode(node<T>* &cur)  
	{ 
		if(cur == nullptr)
			throw (invalid_argument("Pointer does not point to a node"));
		T contents = cur->value();
		if(cur->left == nullptr && cur->right == nullptr)
		{ // no children
			delete cur;
			cur = nullptr;
		}
		else if(cur->left == nullptr)
		{ // only right child
			node<T>* temp = cur->right;
			delete cur;
			cur = temp;
		}
		else if(cur->right == nullptr)
		{ // only left child
			node<T>* temp = cur->left;
			delete cur;
			cur = temp;
		}
		else
		{ // two children
			cur->setdata(popHigh(cur->left));
			// pops leftmost node of right child and
			// places that value into the current node
		}
		if(root != nullptr)
			root->setHeight();
		return contents;
	}
	
	//-------------------------------------------------------------------- 
	// pops out the leftmost child of cur
	//--------------------------------------------------------------------
	template <class T>
	T bst<T>::popLow(node<T>* &cur)  
	{
		if(cur == nullptr)
			throw (invalid_argument("Pointer does not point to a node"));
		if(cur->left == nullptr)
		{
			T temp = cur->value();
			node<T>* temptr = cur->right;
			delete cur;
			cur = temptr;
			if(root != nullptr)
				root->setHeight();
			return temp;
		}
		return popLow(cur->left);
	}

	//------------------------------------------------------------------------
	// pops out the rightmost child of cur
	// throws invalid_argument
	//------------------------------------------------------------------------
	template <class T>
	T bst<T>::popHigh(node<T>* &cur)  
	{
		if(cur == nullptr)
			throw(invalid_argument("Pointer does not point to a node"));
		if(cur->right == nullptr)
		{
			T temp = cur->value();
			node<T>* temptr = cur->left;
			delete cur;
			cur = temptr;
			if(root != nullptr)
				root->setHeight();
			return temp;
		}
		return popHigh(cur->right);
	}

	//-------------------------------------------------------------------- 
	// pops first node matching d
	//--------------------------------------------------------------------
	template <class T>
	T bst<T>::popFirstOf(const T& d, node<T>*& np)
	{
		node<T>* matchptr = nullptr;
		findFirstOf(d, np, matchptr);
		if(*parentptr != nullptr)
		{
			if((*parentptr)->value() == d)
				return popNode((*parentptr));
		}
		if(root != nullptr)
			root->setHeight();
		return 0;
	}

	//-------------------------------------------------------------------- 
	// returns the number of nodes in the tree
	// recursive
	//--------------------------------------------------------------------
	template <class T>
	int bst<T>::getNumberOfNodes(node<T>* np) const
	{
		int count  = 1;
		if(np != nullptr)
		{ 
			count += getNumberOfNodes(np->left);			
			count += getNumberOfNodes(np->right);
			return count;
		}
		return 0;
	}

	//--------------------------------------------------------------------  
	// Overloaded << for bst<T>
	//--------------------------------------------------------------------
	template <class T>
	ostream& operator<<(ostream& out, bst<T> tree)
	{
		tree.print(tree.getroot(), out);
		return out;
	}

} // end namespace PB_BST

#endif
