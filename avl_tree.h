#pragma once

#include <cstdio>
#include "avl_tree_node.h"
#include <cmath>
using namespace std;

template <typename Key>
class avl_tree
{
	avl_tree_node<Key>* root;
	//avl_tree_node<Key>* null_elem;

	size_t size_c;	

public:
    avl_tree() : root(nullptr), size_c(0) {}

	bool check() { return check_(root); }
	bool check_(avl_tree_node<Key>* node)
	{
		if (!node)
			return true;
		if (node->right && node->right->parent != node ||
			node->left && node->left->parent != node)
			return false;
		return check_(node->right) && check_(node->left);
	}

	avl_tree_node<Key>* insert(Key key) 
	{ 
		if (!root)
		{
			root = new avl_tree_node<Key>(key, nullptr, nullptr, nullptr);
			return root;
		}
		avl_tree_node<Key>* cur;
		bst_insert(key, root, nullptr, cur);
		cur = cur->parent;
		while (cur)
		{
			restore_height(cur);
			switch (balance(cur))
			{
			case 1: break;
			case -1: break;
			case 0: return cur;
			default: balancing(cur);
				if (balance(cur) == 0) return 0; //??
				break;
			}
			cur = cur->parent;
		}
		return cur;
	}

	size_t erase(const Key& key)
    {
        auto node = root;
        while (node->value != key)
        {
            node =  key > node->value?
                    node = node->right :
                    node = node->left;
        }
        if (!(node->left) || !(node->right)) //
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
                temp->become(temp->right);
            delete temp;
        }
        while (node)
        {
            restore_height(node);
            switch (balance(node))
            {
                case 1: return 0;
                case -1: return 0;
                case 0: break;
                default: balancing(node);
                    if (balance(node) == 0) return 0; //??
                    break;
            }
            node = node->parent;
        }
    }

	avl_tree_node<Key>* find(const Key& key) { return find_(key, root);	}

	avl_tree_node<Key>* lower_bound(const Key& key)
    {
        auto current = root;
        avl_tree_node<Key>* next = nullptr;
        while (current)
        {
            if (current->value >= key)
            {
                next = current;
                current = current->left;
            }
            else
                current = current->right;
        }
        return next;
    }

	avl_tree_node<Key>* upper_bound(const Key& key)
    {
        auto current = root;
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
        return next;
    }

	size_t size() const { return size_c; }
	bool empty() const { return size_c == 0; };
	
private:
	avl_tree_node<Key>* bst_insert(Key key, avl_tree_node<Key>* node, avl_tree_node<Key>* parent, avl_tree_node<Key>*& new_node)
	{
		if (!node)
		{
			new_node = new avl_tree_node<Key>(key, parent, nullptr, nullptr);
			return new_node;
		}
			
		if (key > node->value)
			node->right = bst_insert(key, node->right, node, new_node);
		if (key < node->value)
			node->left = bst_insert(key, node->left, node, new_node);		
		return node;
	}

    avl_tree_node<Key>* big_rotate_left(avl_tree_node<Key>* node)
    {
        rotate_left(node->left);
        rotate_right(node);
        return node;
    }

    avl_tree_node<Key>* big_rotate_right(avl_tree_node<Key>* node)
    {
        rotate_right(node->right);
        rotate_left(node);
        return node;
    }

    avl_tree_node<Key>* rotate_left(avl_tree_node<Key>* node)
    {
        auto right = node->right;
        node->right = right->left;
		if (!node->parent)		
			root = right;
		else
		{
			if (node->is_left())
				node->parent->left = right;
			else
				node->parent->right = right;
		}
		right->parent = node->parent;
        right->left = node;
		node->parent = right;

        restore_height(node);
        restore_height(right);

        return right;
    }

    avl_tree_node<Key>* rotate_right(avl_tree_node<Key>* node)
    {
        auto left = node->left;
        node->left = left->right;
		if (!node->parent)
			root = left;
		else
		{
			if (node->is_left())
				node->parent->left = left;
			else
				node->parent->right = left;
		}
		left->parent = node->parent;
        left->right = node;
		node->parent = left;

        restore_height(node);
        restore_height(left);

        return left;
    }
	
	avl_tree_node<Key>* find_(const Key& key, avl_tree_node<Key>* parent)
    {
        if (!parent || key == parent->value)
            return parent;
        if (key < parent->value)
            return find_(key, parent->left);
        return find_(key, parent->right);
    }

    avl_tree_node<Key>* leftest_from(avl_tree_node<Key>* node) const
    {
        auto temp = node;
        while (temp->left)
            temp = temp->left;
        return temp;
    }

	void restore_height(avl_tree_node<Key>* node)
    {		
		auto left = node->left ? node->left->height : 0;
		auto right = node->right ? node->right->height : 0;
	    node->height = (left > right ? left : right) + 1;
    }

	avl_tree_node<Key>* balancing(avl_tree_node<Key>* node)
    {
        restore_height(node);
        if (balance(node) == 2)
        {
            if (balance(node->right) < 0)
                node->right = rotate_left(node->right);
            return rotate_right(node);
        }
        if (balance(node) == -2)
        {
            if (balance(node->left) > 0)
                node->left = rotate_right(node->left);
            return rotate_left(node);
        }
        return node;
    }

	size_t height(avl_tree_node<Key>* node) const
    {
        if (node == nullptr)
            return 0;
        return node->height;
    }

	int balance(avl_tree_node<Key>* node) const
    {
		if (!node)
			return 0;
        return height(node->left) - height(node->right);
    }

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
	if (node == nullptr || node == NULL)
		return;
	print_node(node->right, space + tab);
	for (int i = 0; i < space; i++)
		std::cout << " ";
	std::cout << node->value << std::endl;
	print_node(node->left, space + tab);
}