#pragma once

#include <cstdio>
#include "avl_tree_node.h"
#include <cmath>
using namespace std;

template <typename Key>
class avl_tree
{
	avl_tree_node<Key>* root;
	//avl_tree_node<Key>* null_elem;

	size_t size_c;	

public:

    avl_tree() : root(nullptr), size_c(0) {}

	avl_tree_node<Key>* insert(Key value);
	size_t erase(const Key& key);

	avl_tree_node<Key>* find(const Key& key);

	avl_tree_node<Key>* lower_bound(const Key& key);
	avl_tree_node<Key>* upper_bound(const Key& key);

	size_t size() const { return size_c; }
	bool empty() const { return size_c == 0; };
	
private:    
    avl_tree_node<Key>* big_rotate_left(avl_tree_node<Key>* node);
    avl_tree_node<Key>* big_rotate_right(avl_tree_node<Key>* node);
    avl_tree_node<Key>* rotate_left(avl_tree_node<Key>* node);
    avl_tree_node<Key>* rotate_right(avl_tree_node<Key>* node);

	avl_tree_node<Key>* insert_(Key value, avl_tree_node<Key>* parent);
	avl_tree_node<Key>* find_(const Key& key, avl_tree_node<Key>* parent);

    void leftest_from(avl_tree_node<Key>* node);

	void restore_height(avl_tree_node<Key>* node)
    {
	    auto left = node->left->height;
	    auto right = node->right->height;
	    node->height = (left > right ? left : right) + 1;
    }

	avl_tree_node<Key>* balancing(avl_tree_node<Key>* node);

	size_t height(avl_tree_node<Key>* node);
	int balance(avl_tree_node<Key>* node);	  
};