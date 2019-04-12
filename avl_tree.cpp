#include "avl_tree.h"

template<typename Key>
avl_tree_node<Key>* avl_tree<Key>::insert(Key value)
{
	return insert_(value, root);	
}

template<typename Key>
size_t avl_tree<Key>::erase(const Key& key)
{
    auto node = root;
    while (node.value != key)
    {
        node = node->value > key?
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
            *temp.become(temp->right);
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

template<typename Key>
avl_tree_node<Key>* avl_tree<Key>::find(const Key& key)
{
	return find_(key, root);	
}

template<typename Key>
avl_tree_node<Key>* avl_tree<Key>::lower_bound(const Key& key)
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

template<typename Key>
avl_tree_node<Key>* avl_tree<Key>::upper_bound(const Key& key)
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

template<typename Key>
avl_tree_node<Key>* avl_tree<Key>::big_rotate_left(avl_tree_node<Key>* node)
{
    rotate_left(node->left);
    rotate_right(node);
}

template<typename Key>
avl_tree_node<Key>* avl_tree<Key>::big_rotate_right(avl_tree_node<Key>* node)
{
    rotate_right(node->right);
    rotate_left(node);
}

template<typename Key>
avl_tree_node<Key>* avl_tree<Key>::rotate_left(avl_tree_node<Key>* node)
{
    auto right = node->right;
    node->right = right->left;
    right->left = node;

	restore_height(node);
	restore_height(right);

	return right;
}

template<typename Key>
avl_tree_node<Key>* avl_tree<Key>::rotate_right(avl_tree_node<Key>* node)
{
    auto left = node->left;
    node->left = left->right;
    left->right = node;

	restore_height(node);
	restore_height(left);

	return left;
}

template<typename Key>
avl_tree_node<Key>* avl_tree<Key>::insert_(Key value, avl_tree_node<Key>* parent)
{
	if (!parent)
	{
		parent = new avl_tree_node<Key>(value, nullptr, nullptr, nullptr);
		return parent;
	}
	if (auto found = find_(value, parent))
	{
		//found->count++;
		return found;
	}
	if (value < parent->value)
		parent->left = insert_(value, parent->left);
	else
		parent->right = insert_(value, parent->right);

	return balancing(parent);
}

template<typename Key>
avl_tree_node<Key>* avl_tree<Key>::find_(const Key& key, avl_tree_node<Key>* parent)
{
	if (!parent || key == parent->value)
		return parent;
	if (key < parent->value)
		return find_(key, parent->left);
	return find_(key, parent->right);
}

template<typename Key>
avl_tree_node<Key>* avl_tree<Key>::balancing(avl_tree_node<Key>* node)
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

template<typename Key>
size_t avl_tree<Key>::height(avl_tree_node<Key>* node)
{
    if (node == nullptr)
        return 0;
    return node->height;
}

template<typename Key>
int avl_tree<Key>::balance(avl_tree_node<Key>* node)
{
    return height(node->left) - height(node->right);
}

template<typename Key>
void avl_tree<Key>::leftest_from(avl_tree_node<Key>* node)
{
    auto temp = node;
    while (temp->left)
        temp = temp->left;
    return temp;
}