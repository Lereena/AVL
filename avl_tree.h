#pragma once

#include <cstdio>
#include "avl_tree_node.h"
#include <iostream>

template <typename Key>
class avl_tree
{
	avl_tree_node<Key>* root = nullptr;
	avl_tree_node<Key>* null_elem;

	size_t size_c;

	class iterator;

public:
	void insert(Key value);
	size_t erase(const Key& key);
	iterator find(const Key& key) const
	{
        if (!root || key == root->value)
            return root;
        if (key < root->data)
            return find_(key, root->left);
        else
            return find_(key, root->right);
	}

	iterator lower_bound(const Key& key);
	iterator upper_bound(const Key& key);

	size_t size() const { return size_c; }
	bool empty() const { return size_c == 0; }

	iterator begin() { return null_elem->left; }
	iterator end() { return null_elem; }

private:
	void big_rotate_left(avl_tree_node<Key>* node);
	void big_rotate_right(avl_tree_node<Key>* node);
	void rotate_left(avl_tree_node<Key>* node);
	void rotate_right(avl_tree_node<Key>* node);
	void balancing(avl_tree_node<Key>* node);

	size_t height(avl_tree_node<Key>* node);
	int balance(avl_tree_node<Key>* node);

	avl_tree_node<Key>* remove(avl_tree_node<Key>* root, const Key& key);

	void leftest_from(avl_tree_node<Key>* node);

	class iterator
	{
        avl_tree_node<Key>* node;

    public:
	    iterator(avl_tree_node<Key>* node_) :
	        node(node_) {}

        Key& operator*() { return node->value; }

        iterator& operator++()
        {
            iterator temp(node);
	        node = next();
	        return temp;
	    }

        iterator& operator++(int)
        {
            node = next();
            return this;
        }

        bool operator==(iterator& other)
        {
            return node == other.node;
	    }

        bool operator!=(iterator& other)
        {
            return node != other.node;
        }

    private:

	    avl_tree_node<Key>* next()
	    {
	        if (auto temp = node->right)
            {
                while (temp->left)
                    temp = temp->left;

                return temp;
            }

	        auto temp = node;
	        while (temp->is_left())
	            temp = temp->parent;

            return temp->parent;
	    }
	};
	template<typename T>
	friend void print_tree(const avl_tree<T>& tree);
};

template<typename T>
void print_tree(const avl_tree<T>& tree)
{
	auto root = tree.root;
	print_node(root);
}

template<typename T>
void print_node(const avl_tree_node<T>* node, int space = 0, int tab = 4)
{
	if (!node)
		return;
	print_node(node->right, space += tab);
	std::cout << node->value << std::endl;
	print_node(node->right, space += tab);
}
