#include <iostream>
#include <cstdlib>
#include "set.h"
using namespace std;

//--------------------------------------------------------------------
// Test Driver for bst and node classes
// Compiled under MS Visual C++.Net 20013, Windows 7
// by Paul Bladek
// December, 2000
// revised April, 2005
// revised June, 2015
//--------------------------------------------------------------------
int main(void)
{
	using PB_BST::bst;
	using PB_BST::node;
	using PB_BST::avl;
	using PB_BST::set;
	try
	{
		//avl<char> tree;
		//node<char>* marker = nullptr;
		//char c;
		//cout << "enter some characters, followed by <enter>.\n" ;
		//do
		//{ 
		//	cin.get(c);
		//	if(c == '\n')
		//		break;
		//	tree.insert(c); 
		//}
		//while(true);
		////
		//tree.printXlevel(cout);
		//tree.popFirstOf('D', tree.getroot());

		//tree.printXlevel(cout);
		////
		//avl<char> tree2 = tree; // test overloaded =
		//tree2 += tree; // test overloaded +
		//cout << "tree 1:" << endl;		
		//cout << tree << " : " << tree.getNumberOfNodes()
		//	<< "nodes" << endl;  // test overloaded << and print()
		//tree.printXlevel(cout);
		//cout  << endl << "tree 2:" << tree2 
		//	<< tree.getNumberOfNodes() << "nodes" << endl;
		//tree2.printXlevel(cout);
		//cout << endl << endl << "Enter character to match: ";
		//cin >> c;
		//tree.findFirstOf(c, tree.getroot(), marker);
 
		//// set marker to first match of c
		//if(marker != nullptr)
		//	cout << marker->value();
		//else
		//	cout << "not found";
		//cout << "\n Enter character to delete: ";
		//cin >> c;
		//cin.ignore(FILENAME_MAX, '\n');
		//c = tree.popFirstOf(c);
  //
		//// test popFirstOf(), popnode(), poplow()	
		//cout << "<" << c << ">  " << tree << endl;
		//tree.delTree();  // delete first tree
		//tree2 += 'Z';     // add in another element , test +=
		//tree2 = tree2 + 'Y';  // test +		
		//cout << tree2 << endl;
		//cout << "tree 1:" << endl;		
		//cout << tree << " : " << tree.getNumberOfNodes()
		//	<< "nodes" << endl;  // test overloaded << and print()
		//tree.printXlevel(cout);
		//cout  << endl << "tree 2:" << tree2 
		//	<< tree.getNumberOfNodes() << "nodes" << endl;
		//tree2.printXlevel(cout);
		//cout << endl;
		//tree.delTree();  // delete second tree

		avl<char> tree1;
		node<char>* marker1 = nullptr;
		char c;
		cout << "****************** TEST AVL TREE *****************" << endl;
		cout << "=====Test INSERT function =======" << endl;
		cout << "Insert the first Tree:" << endl;
		cout << "enter some characters, followed by <enter>.\n" ;
		do
		{ 
			cin.get(c);
			//cout << c << endl;
			if(c == '\n')
				break;
			tree1.insert(c);
		}
		while(true);
		cout << "First tree after insert all node: " << endl;
		tree1.printXlevel(cout);
		cout << tree1 << " : " << tree1.getNumberOfNodes() << " nodes" << endl;  // test overloaded << and print()
		cout << endl << "=====Test Operator + ======" << endl;
		avl<char> tree2;
		node<char>* marker2 = nullptr;
		cout << endl << "**Add more node: " << endl;
		cout << "Enter value of new node: ";
		cin.get(c);
		cin.ignore(256, '\n');
		tree1 += c;
		cout << "New tree: " << endl;

		tree1.printXlevel(cout);
		cout << tree1 << " : " << tree1.getNumberOfNodes() << " nodes" << endl;  // test overloaded << and print()

		cout << endl << "**Insert the second Tree:" << endl;
		cout << "enter some characters, followed by <enter>.\n";
		do
		{
			cin.get(c);
			//cout << c << endl;
			if (c == '\n')
				break;
			tree2.insert(c);
		} while (true);
		cout << "Second tree after insert all node: " << endl;
		tree2.printXlevel(cout);
		cout << tree2 << " : " << tree2.getNumberOfNodes() << " nodes" << endl;  // test overloaded << and print()

		cout << endl << "AVL tree Total: FirstTree += SecondTree" << endl;
		tree1 += tree2;
		tree1.printXlevel(cout);
		cout << tree1 << " : " << tree1.getNumberOfNodes() << " nodes" << endl;  // test overloaded << and print()

		cout << endl << "===== Test popnode =====" << endl;
		cout << "**Pop root node." << endl;
		node<char>* tmpNode = tree1.getroot();
		tree1.popnode(tmpNode);
		cout << "New tree after pop root node: " << endl;
		tree1.printXlevel(cout);
		cout << tree1 << " : " << tree1.getNumberOfNodes() << " nodes" << endl;  // test overloaded << and print()

		cout << endl << "**Pop low node." << endl;
		tmpNode = tree1.getroot();
		tree1.poplow(tmpNode);
		cout << "New tree after pop low node: " << endl;
		tree1.printXlevel(cout);
		cout << tree1 << " : " << tree1.getNumberOfNodes() << " nodes" << endl;  // test overloaded << and print()

		cout << endl << "**Pop popfirst node." << endl;
		tmpNode = tree1.getroot();
		cout << "Enter the node want to pop from tree: ";
		cin.get(c);
		cin.ignore(256, '\n');
		tree1.popfirst(c, tmpNode);
		cout << "New tree after pop node: " << c << endl;
		tree1.printXlevel(cout);
		cout << tree1 << " : " << tree1.getNumberOfNodes() << " nodes" << endl;  // test overloaded << and print()

		cout << "******************END TEST AVL TREE *****************" << endl << endl;

		cout << "****************** TEST SET TREE *****************" << endl;
		set<char> testSet = set<char>();		
		cout << "enter some characters, followed by <enter>.\n";
		do
		{
			cin.get(c);
			//cout << c << endl;
			if (c == '\n')
				break;
			testSet.insert(c);
		} while (true);
		cout << "The  set tree" << c << endl;
		testSet.printXlevel(cout);
		cout << testSet << " : " << testSet.getNumberOfNodes() << " nodes" << endl;  // test overloaded << and print()

		cout << endl << "**Test isMember function" << endl;
		cout << "Enter the character want to check exist in set: ";
		cin.get(c);
		cin.ignore(256, '\n');
		if (testSet.isMember(c) == true)
		{
			cout << "Character " << c << " is the member of set" << endl;
		}
		else
		{
			cout << "Character " << c << " is NOT member of set" << endl;
		}

		cout << endl << "**Test Union function" << endl;
		cout << "Union selft: " << endl;
		set<char> newSet = testSet.Union(testSet);

		cout << "The  new set: " << c << endl;
		newSet.printXlevel(cout);
		cout << newSet << " : " << newSet.getNumberOfNodes() << " nodes" << endl;  // test overloaded << and print()

		set<char> newSet2 = set<char>();
		cout << endl << "Enter new set. \nenter some characters, followed by <enter>.\n";
		do
		{
			cin.get(c);
			//cout << c << endl;
			if (c == '\n')
				break;
			newSet2.insert(c);
		} while (true);

		cout << "The new set input: " << c << endl;
		newSet2.printXlevel(cout);
		cout << newSet2 << " : " << newSet2.getNumberOfNodes() << " nodes" << endl;  // test overloaded << and print()

		set<char> newSet3 = testSet.Union(newSet2);
		cout << "The union new set: " << c << endl;
		newSet3.printXlevel(cout);
		cout << newSet3 << " : " << newSet3.getNumberOfNodes() << " nodes" << endl;  // test overloaded << and print()

		cout << endl << "** Test intersection function" << endl;
		set<char> newSet4 = testSet.intersection(newSet2);
		cout << "The intersection new set: " << c << endl;
		newSet4.printXlevel(cout);
		cout << newSet4 << " : " << newSet4.getNumberOfNodes() << " nodes" << endl;  // test overloaded << and print()
		cout << "****************** END TEST SET TREE *****************" << endl;
	}
	catch(invalid_argument e)
	{
		cout << "Exception: " << e.what() << endl;
		cout << "press \"Enter\" to continue" << endl;
		cin.get(); // keep window open
		return EXIT_FAILURE;
	}
	catch(bad_alloc e)
	{
		cout << "Exception: " << e.what() << endl;
		cout << "press \"Enter\" to continue" << endl;
		cin.get(); // keep window open
		return EXIT_FAILURE;
	}
	catch(exception e)
	{
		cout << "Exception: " << e.what() << endl;
		cout << "press \"Enter\" to continue" << endl;
		cin.get(); // keep window open
		return EXIT_FAILURE;
	}
	cout << "press \"Enter\" to continue" << endl;
	cin.get(); // keep window open
	return EXIT_SUCCESS;
}

