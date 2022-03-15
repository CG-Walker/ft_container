#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <cstddef>

namespace ft
{
	template <typename T>
	class iterator
	{
		public:
			//typedef std::random_access_iterator_tag iterator_category;
			//typedef T								value_type;
			typedef T *								pointer;
			typedef T const *						const_pointer;
			typedef T &								reference;
			typedef T const &						const_reference;
			typedef std::ptrdiff_t					difference_type;
			typedef iterator<T> 					_iterator;

			// Constructors and Destructor
			iterator(void) : _ptr(NULL) {}
			iterator(pointer elem) : _ptr(elem) {}
			iterator(const _iterator & other)  : _ptr(other._ptr){}
			~iterator(void) {};

			_iterator & operator=(_iterator const & other)
			{
				_ptr = other._ptr;
				return (*this);
			}

			_iterator & operator+(_iterator const & other)
			{
				_iterator new_it;
				new_it._ptr = this->_ptr + other._ptr;
				return (new_it);
			}

			_iterator & operator-(_iterator const & other)
			{
				_iterator new_it;
				new_it._ptr = this->_ptr - other._ptr;
				return (new_it);
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
			
			// Prefix increment
			_iterator & operator++()
			{
				++this->_ptr;
				return(*this);
			}

			_iterator & operator--()
			{
				--this->_ptr;
				return(*this);
			}

			// Postfix increment
			_iterator operator++(int)
			{
				iterator ite = *this;
				++this->_ptr;
				return(*ite);
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