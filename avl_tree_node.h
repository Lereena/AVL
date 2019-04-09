#pragma once

enum side_type {LEFT, ROOT, RIGHT};

template <typename T>
struct avl_tree_node
{
	T value;

	avl_tree_node<T>* parrent;
	avl_tree_node<T>* left;
	avl_tree_node<T>* right;

	int height;	
	side_type side;

	avl_tree_node(T value_, avl_tree_node<T>* parrent_ = nullptr, side_type side_ = ROOT,
		avl_tree_node<T>* left_ = nullptr, avl_tree_node<T>* right_ = nullptr) :
		value(value_), parrent(parrent_), left(left_), right(right_),
		height(0), side(side_) {}

	~avl_tree_node()
	{
		switch (side)
		{
		case LEFT: parrent->left = nullptr; break;
		case RIGHT: parrent->right = nullptr; break;
		default: break;
		}
		parrent = nullptr;
		left = nullptr;
		right = nullptr;
	}
};
