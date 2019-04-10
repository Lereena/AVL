#pragma once

#include <cstdio>
#include "avl_tree_node.h"

template <typename Key>
class avl_tree
{
	avl_tree_node<Key>* root;
	avl_tree_node<Key>* null_elem;

	size_t size_c;

	class iterator;

public:

    avl_tree() : root(nullptr), size_c(0) {}

	void insert(Key value);
	size_t erase(const Key& key);

	iterator find(const Key& key) { return find_(key, root); }

	iterator lower_bound(const Key& key) { return lower_bound_(key, root); }
	iterator upper_bound(const Key& key) { return upper_bound_(key, root); }

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

    iterator find_(Key& key, avl_tree_node<Key>* parent)
    {
        if (!parent || key == parent->value)
            return iterator(parent);
        if (key < parent->value)
            return find_(key, parent->left);
        return find_(key, parent->right);
    }

    iterator lower_bound_(Key& key, avl_tree_node<Key>* parent)
    {
        auto current = parent;
        avl_tree_node<Key>* next = nullptr;
        while(current)
        {
            if (current->value >= key)
            {
                next = current;
                current = current->left;
            }
            else
                current = current->right;
        }
        return iterator(next);
    }

    iterator upper_bound_(Key& key, avl_tree_node<Key>* parent)
    {
        auto current = parent;
        avl_tree_node<Key>* next = nullptr;
        while (current)
        {
            if (current->value <= key)
            {
                next = current;
                current = current->right;
            }
            else
                current = current->left;
        }
        return iterator(next);
    }
};