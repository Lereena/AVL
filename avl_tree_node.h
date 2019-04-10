#pragma once

enum side_type {LEFT, RIGHT};

template <typename T>
class avl_tree_node
{
	T value;

	avl_tree_node<T>* parent;
	avl_tree_node<T>* left;
	avl_tree_node<T>* right;

	int height;	
	side_type side;

	avl_tree_node(T value_, avl_tree_node<T>* parent_, avl_tree_node<T>* left_, avl_tree_node<T>* right_, side_type side_) :
		value(value_), parent(parent_), left(left_), right(right_),
		height(0), side(side_) {}

public:

    bool is_left(avl_tree_node<T> *node)
    {
        return node == node->parent->left;
    }
};
