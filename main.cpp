#include "avl_tree.h"
//#include "avl_tree.cpp"
#include <iostream>

int main()
{	
    avl_tree<int> tree;		
	tree.size();	
	tree.empty();
	tree.insert(5);
	tree.insert(6);
	tree.insert(7);
	tree.insert(8);
	tree.insert(9);

	print_tree(tree);
}