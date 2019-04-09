#pragma once
#include "avl_tree.h"

template<typename Key>
void avl_tree<Key>::insert(Key value)
{
}

template<typename Key>
size_t avl_tree<Key>::erase(const Key& key)
{
	return size_t();
}

template<typename Key>
void avl_tree<Key>::lesser_left_turn(avl_tree_node<Key>* node)
{
	auto right = node->right;
	node->right = right->left;
	right->left = node;

	node->height = max(height(right->left),
					   height(right->right)) + 1;
	right->height = max(height(node->left),
					    height(node->right)) + 1;
	right->balance++;
}

template<typename Key>
void avl_tree<Key>::lesser_right_turn(avl_tree_node<Key>* node)
{
	auto left = node->left;
	node->left = left->right;
	left->right = node;

	node->balance++;
	left->balance--;
}

template<typename Key>
size_t avl_tree<Key>::height(avl_tree_node<Key>* node)
{
	if (node == nullptr)
		return 0;
	return node->height;
}

template<typename Key>
int avl_tree<Key>::balance(avl_tree_node<Key>* node)
{
	return height(node->left) - height(node->right);
}
