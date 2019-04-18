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

public:
    avl_tree() : root(nullptr), size_c(0) {}

	bool check() { return check_(root); }
	bool check_(avl_tree_node<Key>* node)
	{
		if (!node)
			return true;
		if (node->right && node->right->parent != node ||
			node->left && node->left->parent != node)
		{
			throw "lol";
			return false;
		}
		return check_(node->right) && check_(node->left);
	}

	avl_tree_node<Key>* insert(Key key) 
	{
		if (!root)
		{
			root = new avl_tree_node<Key>(key, nullptr, nullptr, nullptr);
			return root;
		}
		avl_tree_node<Key>* new_node = nullptr;
		bst_insert(key, root, nullptr, new_node);		
		if (new_node)
			traverse_balancing(new_node->parent);
		return new_node;
	}

	size_t erase(const Key& key)
    {
		auto node = bst_erase(key);
		traverse_balancing(node);
		return 0;
    }

	avl_tree_node<Key>* find(const Key& key)
	{
		auto cur = root;
		while (cur && cur != null_elem)
		{
			if (cur->value == key)
				return cur;
			if (key > cur->value)
				cur = cur->right;
			else
				cur = cur->left;
		}
		return nullptr;
	}

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

	avl_tree_node<Key>* bst_erase(Key key) // returns parrent of deleted node
	{
		auto node = find(key);
		if (!node)
			return nullptr;
		if (!(node->left) || !(node->right))
		{
			auto temp = node->left ? // 1 or 0 childs
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
		else // 2 childs
		{
			auto temp = leftest_from(node->right);
			node->value = temp->value;
			node = temp->parent;
			if (temp->right)
				temp->become(temp->right);
			delete temp;
		}
		return node;
	}

	void null_elem_insert_reassign(avl_tree_node<Key>* node)
	{
		if (null_elem->left->left == node) // Added new minimum
			null_elem->left = node;
		if (null_elem->right->right == node) // Added new maximum
			null_elem->right = node;
	}

	void null_elem_erase_reassign(avl_tree_node<Key>* node)
	{

	}

    avl_tree_node<Key>* rotate_left(avl_tree_node<Key>* node)
    {
        auto r_node = node->right;
        node->right = r_node->left;
		if (r_node->left)
			r_node->left->parent = node;
		if (!node->parent)		
			root = r_node;
		else
		{
			if (node->is_left())
				node->parent->left = r_node;
			else
				node->parent->right = r_node;
		}
		r_node->parent = node->parent;
		r_node->left = node;
		node->parent = r_node;

        restore_height(node);
        restore_height(r_node);
		
        return r_node;
    }

    avl_tree_node<Key>* rotate_right(avl_tree_node<Key>* node)
    {
        auto l_node = node->left;
        node->left = l_node->right;
		if (l_node->right)
			l_node->right->parent = node;
		if (!node->parent)
			root = l_node;
		else
		{
			if (node->is_left())
				node->parent->left = l_node;
			else
				node->parent->right = l_node;
		}
		l_node->parent = node->parent;
		l_node->right = node;
		node->parent = l_node;

        restore_height(node);
        restore_height(l_node);

        return l_node;
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

	void traverse_balancing(avl_tree_node<Key>* node)
	{
		while (node)
		{			
			switch (get_balance(node))
			{
			case 1: break;
			case -1: break;
			case 0: return;
			default: balancing(node);
				if (get_balance(node) == 0) return;
				break;
			}
			node = node->parent;
		}
	}

	avl_tree_node<Key>* balancing(avl_tree_node<Key>* node)
    {
        restore_height(node);
        if (get_balance(node) == 2)
        {
            if (get_balance(node->left) < 0)
                node->left = rotate_left(node->left);			
            return rotate_right(node);
        }
        if (get_balance(node) == -2)
        {
            if (get_balance(node->right) > 0)
                node->right = rotate_right(node->right);			
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

	int get_balance(avl_tree_node<Key>* node) const
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