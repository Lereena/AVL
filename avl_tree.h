#pragma once
#include "avl_tree_node.h"

template <typename Key>
class avl_tree
{
	avl_tree_node<Key>* root;
	avl_tree_node<Key>* null_elem;

	size_t size_c;

	class iterator;
public:
	void insert(Key value);
	size_t erase(const Key& key);
	iterator find(const Key& key); 

	iterator lower_bound(const Key& key);
	iterator upper_bound(const Key& key);

	size_t size() const { return size_c; }
	bool empty() const { return size_c == 0; };
	
private:
	void big_left_turn(avl_tree_node<Key>* node);
	void big_right_turn(avl_tree_node<Key>* node);
	void lesser_left_turn(avl_tree_node<Key>* node);
	void lesser_right_turn(avl_tree_node<Key>* node);
	void balancing(avl_tree_node<Key>* node);

	size_t height(avl_tree_node<Key>* node);
	int balance(avl_tree_node<Key>* node);

	class iterator
	{

	};
};
