#pragma once

enum side_type {LEFT, RIGHT};

template <typename T>
struct avl_tree_node
{
	T value;

	avl_tree_node<T>* parrent;
	avl_tree_node<T>* left;
	avl_tree_node<T>* right;

	int height;	
	side_type side;

	avl_tree_node(T value_, avl_tree_node<T>* parrent_, avl_tree_node<T>* left_, avl_tree_node<T>* right_, side_type side_) :
		value(value_), parrent(parrent_), left(left_), right(right_),
		height(0), side(side_) {}
};
