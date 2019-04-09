#pragma once
#include "avl_tree.h"

template<typename Key>
void avl_tree<Key>::insert(Key value)
{
}

template<typename Key>
size_t avl_tree<Key>::erase(const Key& key)
{
	remove(root, key);
	
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
avl_tree_node<Key>* avl_tree<Key>::remove(avl_tree_node<Key>* root, const Key& key)
{
	if (root == nullptr)
		return root;
	if (key < root->key)
		root->left = deleteNode(root->left, key);
	else if (key > root->key)
		root->right = deleteNode(root->right, key);
	else
	{
		//Если есть 1 или 0 сыновей
		if (!(root->left) || !(root->right))
		{
			Node* temp = root->left ?
				root->left :
				root->right;

			if (!temp)
			{
				temp = root;
				root = nullptr;
			}
			else
				root->value = temp->value;
			delete temp;
		}
		//Если 2 сына
		else
		{
			auto temp = leftest_from(root->right);
			root->value = temp->value;

			root->right = deleteNode(root->right,
				temp->value);
		}
	}
	if (root == nullptr)
		return root;
	root.height = max(height(root.left), height(root.right)) + 1;
}

template<typename Key>
void avl_tree<Key>::leftest_from(avl_tree_node<Key>* node)
{
	auto temp = node;
	while (temp->left)
		temp = temp->left;
	return temp;
}
