#ifndef TREE_ITERATOR_HPP
# define TREE_ITERATOR_HPP

# include "Utils.hpp"
# include "Iterator.hpp"
# include "Tree.hpp"
# include "IteratorTrait.hpp"

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
			~tree_iterator(void) {};
			explicit tree_iterator(link_type ptr, link_type nil) : _current(ptr), _nil(nil) {};

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
			
			// prefix increment
			tree_iterator &operator++(int)
			{
				this->next();
				return(*this);
			}
			tree_iterator &operator--(int)
			{
				this->prev();
				return(*this);
			}

			// Postfix increment
			/*
			tree_iterator operator++(int)
			{
				tree_iterator tmp(*this);
				++(*this);
				return tmp;
			}
			tree_iterator operator--(int)
			{
				tree_iterator tmp(*this);
				--(*this);
				return tmp;
			}
			*/

		private:
			link_type _current;
			link_type _nil;

			void prev()
			{
				if (this->_current->left) 
				{
					this->_current = this->_current->left;
					while (this->_current->right)
						this->_current = this->_current->right;
				} 
				else
					this->_current = this->_current->parent;
			}
			void next() 
			{
				if (this->_current->right) 
				{
					this->_current = this->_current->right;
					while (this->_current->left)
						this->_current = this->_current->left;
				}
				else
				{
					link_type tmp = this->_current;
					this->_current = this->_current->parent;
					while (this->_current->left != tmp)
					{
						tmp = this->_current;
						this->_current = this->_current->parent;
					}
				}
		}
	};
}
#endif


