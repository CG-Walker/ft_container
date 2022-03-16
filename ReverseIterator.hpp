
#ifndef REVERSEITERATOR_HPP
#define REVERSEITERATOR_HPP

#include "Iterator.hpp"

namespace ft
{
template <class T>
	class reverse_iterator 
	{
	public:
	
		//typedef std::random_access_iterator_tag iterator_category;
		//typedef T								value_type;
		typedef  typename ft::iterator_traits<T*>::pointer			pointer;
		typedef  typename ft::iterator_traits<const T*>::pointer    const_pointer;
		typedef  typename ft::iterator_traits<T*>::reference		reference;
		typedef  typename ft::iterator_traits<const T*>::reference	const_reference;
		typedef  typename ft::iterator_traits<T*>::difference_type	difference_type;
		typedef reverse_iterator<T> 					_reverse_iterator;
		
		reverse_iterator(): _base(0){};
		reverse_iterator(pointer base) : _base(base) {};
		reverse_iterator(const _reverse_iterator & other) : _base(other._base){};
		~reverse_iterator() {};
		
		pointer base() const {return (_base);}
		_reverse_iterator &operator=(const  _reverse_iterator & other)
		{
			this->_base = other._base;
			return(*this);
		}
		_reverse_iterator &operator++()
		{
			this->_base--;
			return(*this);
		}
		reverse_iterator operator++(int)
		{
			reverse_iterator tmp = *this;
			this->_base--;
			return (tmp);
		}
		reverse_iterator &operator+=(difference_type n)
		{
			this->_base -= n;
			return *this;
		}
		reverse_iterator operator-(difference_type n) const
		{
			return reverse_iterator(this->_base + n);
		}
		reverse_iterator &operator--()
		{
			this->_base++;
			return *this;
		}
		reverse_iterator operator--(int)
		{
			reverse_iterator tmp = *this;
			this->_base++;
			return tmp;
		}
		reverse_iterator &operator-=(difference_type n)
		{
			this->_base += n;
			return *this;
		}

		reference operator*() const
		{
			pointer tmp = this->_base;
			--tmp;
			return *tmp;
		}

		pointer operator->() const
		{
			return &(operator*());
		}

		reference operator[](difference_type n) const
		{
			return this->_base[-n - 1];
		}

		template <typename _T>
		friend bool operator==(const reverse_iterator<_T> &lhs, const reverse_iterator<_T> &rhs);
		template <typename _T>
		friend bool operator!=(const reverse_iterator<_T> &lhs, const reverse_iterator<_T> &rhs);
		template <typename _T>
		friend bool operator<(const reverse_iterator<_T> &lhs, const reverse_iterator<_T> &rhs);
		template <typename _T>
		friend bool operator<=(const reverse_iterator<_T> &lhs, const reverse_iterator<_T> &rhs);
		template <typename _T>
		friend bool operator>(const reverse_iterator<_T> &lhs, const reverse_iterator<_T> &rhs);
		template <typename _T>
		friend bool operator>=(const reverse_iterator<_T> &lhs, const reverse_iterator<_T> &rhs);
		template <typename _T>
		friend reverse_iterator<_T> operator+(typename reverse_iterator<_T>::difference_type n, const reverse_iterator<_T> &rev_it);
		template <typename _T>
		friend reverse_iterator<_T> operator-(typename reverse_iterator<_T>::difference_type n, const reverse_iterator<_T> &rev_it);

	private:
		pointer _base;
	};
	template <typename _T>
	bool operator==(const reverse_iterator<_T> &lhs,
					const reverse_iterator<_T> &rhs)
	{
		return lhs.base() == rhs.base();
	}
	template <typename _T>
	bool operator!=(const reverse_iterator<_T> &lhs,
					const reverse_iterator<_T> &rhs)
	{
		return lhs.base() != rhs.base();
	}
	template <typename _T>
	bool operator<(const reverse_iterator<_T> &lhs,
				   const reverse_iterator<_T> &rhs)
	{
		return lhs.base() > rhs.base();
	}
	template <typename _T>
	bool operator<=(const reverse_iterator<_T> &lhs,
					const reverse_iterator<_T> &rhs)
	{
		return lhs.base() >= rhs.base();
	}
	template <typename _T>
	bool operator>(const reverse_iterator<_T> &lhs,
				   const reverse_iterator<_T> &rhs)
	{
		return lhs.base() < rhs.base();
	}
	template <typename _T>
	bool operator>=(const reverse_iterator<_T> &lhs,
					const reverse_iterator<_T> &rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template <typename _T>
	reverse_iterator<_T> operator+(
		typename reverse_iterator<_T>::difference_type n,
		const reverse_iterator<_T> &rev_it)
	{
		return reverse_iterator<_T>(rev_it.base() - n);
	}
	template <typename _T>
	typename reverse_iterator<_T>::difference_type
	operator-(const reverse_iterator<_T> &lhs,
			  const reverse_iterator<_T> &rhs)
	{
		return rhs.base() - lhs.base();
	}

}

#endif