#pragma once

template <typename T>
class tree_node
{
	T value;
	tree_node<T>* parrent;
	tree_node<T>* left;
	tree_node<T>* right;

	tree_node(T value_, tree_node<T>* parrent_, tree_node<T>* left_, tree_node<T>* right_) :
		value(value_), parrent(parrent_), left(left_), right(right_) {}
};
