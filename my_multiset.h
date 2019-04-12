#pragma once
#include "avl_tree.h"
/*
template <typename Key>
class my_muliset
{
	avl_tree<Key> values;
	class iterator;

public:
	iterator insert(Key value) { return new iterator(*values.insert(value)); }
	size_t erase(const Key& key) { return values.erase(key); }
	iterator find(const Key& key) const { return new iterator(*values.find(key)); }

	iterator lower_bound(const Key& key) { return new iterator(*values.lower_bound(key)); }
	iterator upper_bound(const Key & key) { return new iterator(*values.upper_bound(key)); }

	size_t size() const { return values.size(); }
	bool empty() const { return values.empty(); }

	/*
	iterator begin() { return values; }
	iterator end() { return null_elem; }
	
private:
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
};
*/