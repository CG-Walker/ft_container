#ifndef TREE_ITERATOR_HPP
# define TREE_ITERATOR_HPP

# include "Utils.hpp"
# include "Iterator.hpp"
# include "Tree.hpp"
# include "IteratorTrait.hpp"
# include <iostream>

namespace ft
{
	template <class T>
	class node
	{
		public :
			node *	parent;
			node *	left;
			node *	right;
			T		value;

			node() : parent(NULL), left(NULL), right(NULL) {};
			node(node * nil, const T * value) : parent(nil), left(nil), right(nil), value(value) {};
			node(node * nil, const T & value) : parent(nil), left(nil), right(nil), value(value) {};
	};

	template <class T>
	class tree_iterator
	{
		public:
			typedef std::bidirectional_iterator_tag             iterator_category;
			typedef typename ft::iterator_traits<T>::value_type value_type;
			typedef typename ft::iterator_traits<T>::difference_type difference_type;
			typedef typename ft::iterator_traits<T>::pointer pointer;
			typedef typename ft::iterator_traits<T>::reference reference;
		private:
			typedef ft::node<value_type> * link_type;
		public:
			tree_iterator() : _current(NULL) {};
			explicit tree_iterator(link_type ptr, link_type nil) : _current(ptr), _nil(nil) {};
			~tree_iterator(void) {};

			link_type base() const {return _current;};
			link_type get_nil() const {return _nil;};
			template <class Iter>
			tree_iterator(const tree_iterator<Iter> &other) {*this = other;};

			template <class Iter>
			tree_iterator &operator=(const tree_iterator<Iter> &other)
			{
				_current = other.base();
				_nil = other.get_nil();
				return *this;
			}

			// dereference operator
			reference operator*() const {return _current->value;};
			pointer operator->() const {return &_current->value;};
			
			// Postfix increment
			tree_iterator & operator++()
			{
				this->next();
				return (*this);
			}
			tree_iterator & operator--()
			{
				this->prev();
				return (*this);
			}

			// Préfix increment
			
			tree_iterator operator++(int)
			{
				tree_iterator tmp(*this);
				++(*this);
				return (tmp);
			}
			tree_iterator operator--(int)
			{
				tree_iterator tmp(*this);
				--(*this);
				return (tmp);
			}
			

		private:
			link_type _current;
			link_type _nil;

			void prev()
			{
				if (this->_current->left) 
				{
					this->_current = this->_current->left;
					while (this->_current->right != this->_nil)
						this->_current = this->_current->right;
				} 
				else
					this->_current = this->_current->parent;
			}
			void next() 
			{
				if (this->_current->right != this->_nil) 
				{
					this->_current = this->_current->right;
					while (this->_current->left != this->_nil)
						this->_current = this->_current->left;
				}
				else
				{
					link_type tmp = this->_current;
					this->_current = this->_current->parent;
					while (this->_current->left != tmp) // 
					{
						tmp = this->_current; // 10
						this->_current = this->_current->parent; // end
					}
				}
		}
	};
	
/*
					5
			3				8
		2		4		7		13

		2 3 4 5 7 8 13
*/
	template <class Iterator1, class Iterator2>
	bool operator==(const ft::tree_iterator<Iterator1> &lhs, const ft::tree_iterator<Iterator2> &rhs)
	{
		return lhs.base() == rhs.base();
	}
	template <class Iterator1, class Iterator2>
	bool operator!=(const ft::tree_iterator<Iterator1> &lhs, const ft::tree_iterator<Iterator2> &rhs)
	{
		return lhs.base() != rhs.base();
	}
	template <class Iterator1, class Iterator2>
	bool operator>(const ft::tree_iterator<Iterator1> &lhs, const ft::tree_iterator<Iterator2> &rhs)
	{
		return lhs.base() > rhs.base();
	}
	template <class Iterator1, class Iterator2>
	bool operator>=(const ft::tree_iterator<Iterator1> &lhs, const ft::tree_iterator<Iterator2> &rhs)
	{
		return lhs.base() >= rhs.base();
	}
	template <class Iterator1, class Iterator2>
	bool operator<(const ft::tree_iterator<Iterator1> &lhs, const ft::tree_iterator<Iterator2> &rhs)
	{
		return lhs.base() < rhs.base();
	}
	template <class Iterator1, class Iterator2>
	bool operator<=(const ft::tree_iterator<Iterator1> &lhs, const ft::tree_iterator<Iterator2> &rhs)
	{
		return lhs.base() <= rhs.base();
	}
}
#endif
