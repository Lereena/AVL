#include "avl_tree.h"
//#include "avl_tree.cpp"
#include <iostream>

int main()
{	
    avl_tree<int> tree;		
	tree.size();	
	tree.empty();
	tree.insert(5);
	std::cout << tree.check() << std::endl;
	tree.insert(6);
	std::cout << tree.check() << std::endl;
	tree.insert(7);
	std::cout << tree.check() << std::endl;
	tree.insert(8);
	std::cout << tree.check() << std::endl;
	tree.insert(9);
	std::cout << tree.check() << std::endl;
	tree.insert(10);
	std::cout << tree.check() << std::endl;
	tree.insert(11);
	std::cout << tree.check() << std::endl;
	tree.insert(12);
	std::cout << tree.check() << std::endl;
	//tree.erase(6);
	//tree.erase(6);
	//tree.insert(7);
	//tree.insert(8);
	//tree.insert(9);

	print_tree(tree);
}