#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <cstddef>
#include "IteratorTrait.hpp"
namespace ft
{
	template <typename T>
	class iterator 
	{
		public:
			//typedef std::random_access_iterator_tag iterator_category;
			//typedef T								value_type;
			typedef  typename ft::iterator_traits<T*>::pointer			pointer;
            typedef  typename ft::iterator_traits<const T*>::pointer    const_pointer;
            typedef  typename ft::iterator_traits<T*>::reference		reference;
			typedef  typename ft::iterator_traits<const T*>::reference	const_reference;
			typedef  typename ft::iterator_traits<T*>::difference_type	difference_type;
			typedef iterator<T> 					_iterator;

			// Constructors and Destructor
			iterator(void) : _ptr(NULL) {};
			iterator(pointer elem) : _ptr(elem) {};
			iterator(const _iterator & other)  : _ptr(other._ptr){};
			~iterator(void) {};

			_iterator & operator=(_iterator const & other)
			{
				_ptr = other._ptr;
				return (*this);
			}

			difference_type operator+(_iterator const & other)
			{
				difference_type ret = this->_ptr + other._ptr;
				return (ret);
			}

			difference_type operator-(_iterator const & other)
			{
				difference_type ret = this->_ptr - other._ptr;
				return (ret);
			}

			_iterator operator-(size_t n)
			{
				_iterator ret = this->_ptr - n;
				return (ret);
			}
			
			// Prefix increment
			_iterator & operator++()
			{
				++(this)->_ptr;
				return(*this);
			}

			_iterator & operator--()
			{
				--(this)->_ptr;
				return(*this);
			}

			// Postfix increment
			_iterator operator++(int)
			{
				iterator ite = *this;
				++this->_ptr;
				return ite;
			}
	
			_iterator operator--(int)
			{
				iterator ite = *this;
				--this->_ptr;
				return(*ite);
			}

			_iterator & operator+=(const _iterator & other)
			{
				this->_ptr += other->_ptr;
				return (*this);
			}

			_iterator & operator-=(const _iterator & other)
			{
				this->_ptr -= other->_ptr;
				return (*this);
			}

			reference operator*() { return(*_ptr); };
			reference operator[](difference_type n) const { return *(this + n);	};
			pointer operator->() { return(_ptr); };

		template <typename _T>
		friend bool operator==(const iterator<_T> &lhs, const iterator<_T> &rhs);
		template <typename _T>
		friend bool operator!=(const iterator<_T> &lhs, const iterator<_T> &rhs);
		template <typename _T>
		friend bool operator>(const iterator<_T> &lhs, const iterator<_T> &rhs);
		template <typename _T>
		friend bool operator<(const iterator<_T> &lhs, const iterator<_T> &rhs);
		template <typename _T>
		friend bool operator>=(const iterator<_T> &lhs, const iterator<_T> &rhs);
		template <typename _T>
		friend bool operator<=(const iterator<_T> &lhs, const iterator<_T> &rhs);

		protected:
			pointer _ptr;
	};
	template <typename T>
	bool operator==(const iterator<T> &lhs, const iterator<T> &rhs)
	{
		return (lhs._ptr == rhs._ptr);
	}
	template <typename T>
	bool operator!=(const iterator<T> &lhs, const iterator<T> &rhs)
	{
		return (lhs._ptr != rhs._ptr);
	}
	template <typename T>
	bool operator>(const iterator<T> &lhs, const iterator<T> &rhs)
	{
		return (lhs._ptr > rhs._ptr);
	}
	template <typename T>
	bool operator<(const iterator<T> &lhs, const iterator<T> &rhs)
	{
		return (lhs._ptr < rhs._ptr);
	}
	template <typename T>
	bool operator>=(const iterator<T> &lhs, const iterator<T> &rhs)
	{
		return (lhs._ptr >= rhs._ptr);
	}
	template <typename T>
	bool operator<=(const iterator<T> &lhs, const iterator<T> &rhs)
	{
		return (lhs._ptr <= rhs._ptr);
	}
}

#endif