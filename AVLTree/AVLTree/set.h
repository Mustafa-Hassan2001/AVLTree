#include "avl.h"
using namespace std;
namespace PB_BST
{
	template<class T>
	class set : public avl<T>
	{
	public:
		using avl<T>::avl;
		bool insert(T d) { return avl<T>::insert(d, this->root); }
		void print(ostream& out)const { this->print(this->root, out); }
		void print(node<T>* cur, ostream& out) const;
		void printXlevel(ostream& out) const { this->printXlevel(this->root, out); }
		void printXlevel(node<T>* cur, ostream& out) const;
		bool remove(T noderemove);
		bool isMember(T searchNode);
		set<T> Union(set<T> rhs);
		set<T> intersection(set<T> rhs);

		~set() { this->delTree(); }
	protected:
		node<T>* &getroot() { return this->root; }
	};


	template<class T>
	void set<T>::print(node<T>* cur, ostream& out) const
	{
		bst<T>::print(cur, out);
	}

	template<class T>
	void set<T>::printXlevel(node<T>* cur, ostream& out) const
	{
		bst<T>::printXlevel(cur, out);
	}

	template<class T>
	bool set<T>::remove(T noderemove)
	{
		try {
			this->popFirstOf(noderemove);
		}
		catch (invalid_argument) {
			return false;
		}
		return true;
	}

	template <class T>
	bool set<T>::isMember(T searchNode)
	{
		node<T>* marker = nullptr;
		bst<T>::findFirstOf(searchNode, getroot(), marker);
		return marker != nullptr;
	}


	template<class T>
	set<T> set<T>::Union(set<T> rhs)
	{
		set<T> newTree = *this;
		newTree.addTree(rhs.getroot());
		return newTree;
	}

	template<class T>
	set<T> set<T>::intersection(set<T> rhs)
	{
		set<T> newTree;
		set<T> tmp = rhs;
		while (!tmp.isempty())
		{
			T tmpValue = bst<T>::popNode(tmp.getroot());
			if (isMember(tmpValue))
				newTree.insert(tmpValue);
		}
		return newTree;
	}
}