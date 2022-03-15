#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <cstddef>

namespace ft
{
	template <typename T>
	class iterator
	{
		public:
			typedef std::random_access_iterator_tag iterator_category;
			typedef T								value_type;
			typedef T *								pointer;
			typedef T &								reference;
			typedef std::ptrdiff_t					difference_type;

			// constructor and destructor
			iterator(void) : _ptr(NULL) {};
			iterator(pointer elem) : _ptr(elem);
			iterator(const iterator & other) {};
			~iterator(void) {};

			iterator &operator=(const iterator &other)
			{
				this->_ptr = other->_ptr;
				return (*this);
			}
			// prefix increment
			iterator &operator++()
			{
				++this->_ptr;
				return(*this);
			}
			iterator &operator--()
			{
				--this->_ptr;
				return(*this);
			}

			// postfix increment
			iterator operator++(int)
			{
				iterator ite = *this;
				++this->_ptr;
				return(*ite);
			}
			iterator operator--(int)
			{
				iterator ite = *this;
				--this->_ptr;
				return(*ite);
			}

			iterator &operator+=(const iterator &other)
			{
				this->_ptr += other->_ptr;
				return (*this);
			}
			iterator &operator-=(const iterator &other)
			{
				this->_ptr -= other->_ptr;
				return (*this);
			}
			// reference
			reference operator*()
			{
				return(*_ptr);
			}
			reference operator[](difference_type n) const
			{
				return *(*this + n);
			}
			// pointer
			pointer operator->()
			{
				return(_ptr);
			}

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
		private:
			pointer _ptr;
	};
	template <typename T>
	bool operator==(const iterator<T> &lhs, const iterator<T> &rhs)
	{
		return (lhs._e == rhs._e);
	}
	template <typename T>
	bool operator!=(const iterator<T> &lhs, const iterator<T> &rhs)
	{
		return (lhs._e != rhs._e);
	}
	template <typename T>
	bool operator>(const iterator<T> &lhs, const iterator<T> &rhs)
	{
		return (lhs._e > rhs._e);
	}
	template <typename T>
	bool operator<(const iterator<T> &lhs, const iterator<T> &rhs)
	{
		return (lhs._e < rhs._e);
	}
	template <typename T>
	bool operator>=(const iterator<T> &lhs, const iterator<T> &rhs)
	{
		return (lhs._e >= rhs._e);
	}
	template <typename T>
	bool operator<=(const iterator<T> &lhs, const iterator<T> &rhs)
	{
		return (lhs._e <= rhs._e);
	}
}

#endif