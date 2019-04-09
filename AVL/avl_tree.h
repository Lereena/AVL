#pragma once
#include "tree_node.h"

template <typename Key>
class avl_tree
{
	tree_node<Key>* root;
	tree_node<Key>* null_elem;

	size_t size_c;

	class iterator;
public:
	void insert(Key value);
	size_t erase(const Key& key);
	iterator find(const Key& key); 

	iterator lower_bound(const Key& key);
	iterator upper_bound(const Key& key);

	size_t size() const { return size_c; }
	bool empty() const { return size == 0; };
	
private:	
	class iterator
	{

	};
};
