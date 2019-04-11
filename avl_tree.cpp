#pragma once
#include "avl_tree.h"

template<typename Key>
void avl_tree<Key>::insert(Key value)
{
}

template<typename Key>
size_t avl_tree<Key>::erase(const Key& key)
{
	//remove(root, key);
	auto node = root;
	while (node.value != key)
	{
		node = node->value > key?		
			node = node->right :
			node = node->left;
		if (!node)
			return 0;
	}
	if (!(node->left) || !(node->right)) // Если 1 или 0 сыновей
	{
		auto temp = node->left ?
			node->left :
			node->right;
		if (!temp) 
		{
			temp = node;
			node = node->parent;			
		}
		else
		{
			node->value = temp->value;			
		}
		delete temp;
	}
	else
	{
		auto temp = leftest_from(node->right);
		node->value = temp->value;
		node = temp->parent;
		if (temp->right)								
			*temp.become(temp->right);		
		delete temp;
	}
	//TODO Нужно уменшить size_c
	while (node)
	{
		node->height = max(height(node->left),
						   height(node->right)) + 1;
		switch (balance(node))
		{
		case 1, -1: return 1; break;
		case 0: break;
		default: balancing(node); 
			if (balance(node) == 0) return 1; //?? Не уверен
			break;
		}
		node = node->parent;
	}	
}

template<typename Key>
void avl_tree<Key>::big_rotate_left(avl_tree_node<Key>* node)
{
	rotate_left(node->left);
	rotate_right(node);
}

template<typename Key>
void avl_tree<Key>::big_rotate_right(avl_tree_node<Key>* node)
{
	rotate_right(node->right);
	rotate_left(node);
}

template<typename Key>
void avl_tree<Key>::rotate_left(avl_tree_node<Key>* node)
{
	auto right = node->right;
	node->right = right->left;
	right->left = node;

	node->height = max(height(node->left),
					   height(node->right)) + 1;
	right->height = max(height(right->left),
					    height(right->right)) + 1;
}

template<typename Key>
void avl_tree<Key>::rotate_right(avl_tree_node<Key>* node)
{
	auto left = node->left;
	node->left = left->right;
	left->right = node;

	node->height = max(height(node->left),
					   height(node->right)) + 1;
	left->height = max(height(left->left),
					   height(left->right)) + 1;
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

template<typename Key>
void avl_tree<Key>::leftest_from(avl_tree_node<Key>* node)
{
	auto temp = node;
	while (temp->left)
		temp = temp->left;
	return temp;
}
