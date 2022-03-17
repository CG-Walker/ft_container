#ifndef TREE_HPP
# define TREE_HPP

#include "iterator.hpp"
#include "utility.hpp"

namespace ft
{
	template <class T>
	class node
	{
		public :
			node	*parent;
			node	*left;
			node	*right;
			T		value;
		
		node() : parent(NULL), left(NULL), right(NULL) {};
		node(node *other, const T *value) : parent(other), left(other), right(other), value(value) {};
	};

	template <class T>
	class node_utils
	{
		public:
			node<T> *tree_min(node <T> *node, node <T> *other) const
			{
				while (node->left != other)
					node = node->left;
				return node;
			}

			node<T> *tree_max(node <T> *node, node <T> *other) const
			{
				while (node->right != other)
					node = node->right;
				return node;	
			}
			bool is_left_child(rb_node_<T> *node) const
       		{
            	return node == node->parent->left;
       		}

			bool is_right_child(rb_node_<T> *node) const
			{
				return node == node->parent->right;
			}
			node<T> *search_next_node(node <T> node, node <T> other) const
			{
				if (node->right != other)
				{
					return(tree_min(node->left, other));
				}
				 while (!is_left_child(node))
            	{
               		node = node->parent;
            	}
            	return node->parent;
			}
			node<T> *search_prev_node(node <T> node, node <T> other) const
			{
				if (node->right != other)
				{
					return(tree_max(node->left, other));
				}
				 while (!is_right_child(node))
            	{
               		node = node->parent;
            	}
            	return node->parent;
			}
	}

	template <class T>
	class tree_iterator : public ft::iterator_trait(T *)
	{
		public:
			typedef typename iterator_traits<T>::iterator_category iterator_category;
       		typedef typename iterator_traits<T>::value_type value_type;
        	typedef typename iterator_traits<T>::difference_type difference_type;
        	typedef typename iterator_traits<T>::pointer pointer;
        	typedef typename iterator_traits<T>::reference reference;
			typedef node<value_type> *link_type;

		private:
        	link_type _current_node;
       		link_type _other;
        	node_utils<value_type> _utils;
	}
}

#endif