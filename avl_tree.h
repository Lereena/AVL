#pragma once

#include <cstdio>
#include "avl_tree_node.h"
#include <cmath>
using namespace std;

template <typename Key>
class avl_tree
{
	avl_tree_node<Key>* root;
	avl_tree_node<Key>* null_elem;

	size_t size_c;

	class iterator;

public:

    avl_tree() : root(nullptr), size_c(0) {}

    iterator insert(Key value) { return iterator(insert_(value, root)); }
	size_t erase(const Key& key);

	iterator find(const Key& key) { return iterator(find_(key, root)); }

	iterator lower_bound(const Key& key) { return lower_bound_(key, root); }
	iterator upper_bound(const Key& key) { return upper_bound_(key, root); }

	size_t size() const { return size_c; }
	bool empty() const { return size_c == 0; };
	
private:

    avl_tree_node<Key>* insert_(Key& value, avl_tree_node<Key>* parent);

    avl_tree_node<Key>* big_rotate_left(avl_tree_node<Key>* node);
    avl_tree_node<Key>* big_rotate_right(avl_tree_node<Key>* node);
    avl_tree_node<Key>* rotate_left(avl_tree_node<Key>* node);
    avl_tree_node<Key>* rotate_right(avl_tree_node<Key>* node);
    void leftest_from(avl_tree_node<Key>* node);

	void restore_height(avl_tree_node<Key>* node)
    {
	    auto left = node->left->height;
	    auto right = node->right->height;
	    node->height = (left > right ? left : right) + 1;
    }

	avl_tree_node<Key>* balancing(avl_tree_node<Key>* node)
    {
        restore_height(node);
        if (balance(node) == 2)
        {
            if (balance(node->right) < 0)
                node->right = rotate_right(node->right);
            return rotate_left(node);
        }
        if (balance(node) == -2)
        {
            if (balance(node->left) > 0)
                node->left = rotate_left(node->left);
            return rotate_right(node);
        }
        return node;
    }

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


    avl_tree_node<Key>* find_(Key& key, avl_tree_node<Key>* parent)
    {
        if (!parent || key == parent->value)
            return parent;
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