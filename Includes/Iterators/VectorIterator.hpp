#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>

# include "IteratorTrait.hpp"

namespace ft
{
	template <typename T>
	class iterator 
	{
		public:
			typedef std::random_access_iterator_tag						iterator_category;
			typedef T													value_type;
			typedef typename ft::iterator_traits<T*>::pointer			pointer;
            typedef typename ft::iterator_traits<const T*>::pointer    	const_pointer;
            typedef typename ft::iterator_traits<T*>::reference			reference;
			typedef typename ft::iterator_traits<const T*>::reference	const_reference;
			typedef typename ft::iterator_traits<T*>::difference_type	difference_type;

			// Constructors and Destructor
			iterator(void) : _ptr(NULL) {};
			iterator(pointer elem) : _ptr(elem) {};
			template <class U>
			iterator(const iterator<U> & other)	{ this->_ptr = other.base(); };
			~iterator(void) {};

            pointer base() const {return (_ptr);};

			iterator &operator=(iterator const & other)
			{
				_ptr = other._ptr;
				return (*this);
			}

            iterator & operator=(iterator & other)
			{
				_ptr = other._ptr;
				return (*this);
			}

			difference_type operator+(iterator const & other)
			{
				difference_type ret = this->_ptr + other._ptr;
				return (ret);
			}

			difference_type operator-(iterator const & other)
			{
				difference_type ret = this->_ptr - other._ptr;
				return (ret);
			}

			iterator operator-(size_t n)
			{
				iterator ret = this->_ptr - n;
				return (ret);
			}
			
            iterator operator+(size_t n)
			{
				iterator ret = this->_ptr + n;
				return (ret);
			}
			// Prefix increment
			iterator & operator++()
			{
				++(this)->_ptr;
				return(*this);
			}

			iterator & operator--()
			{
				--(this)->_ptr;
				return(*this);
			}

			// Postfix increment
			iterator operator++(int)
			{
				iterator ite = *this;
				++this->_ptr;
				return (ite);
			}
	
			iterator operator--(int)
			{
				iterator ite = *this;
				--this->_ptr;
				return (ite);
			}

			iterator & operator+=(const iterator & other)
			{
				this->_ptr += other->_ptr;
				return (*this);
			}

			iterator & operator-=(const iterator & other)
			{
				this->_ptr -= other->_ptr;
				return (*this);
			}

			iterator & operator+=(size_t n)
			{
				this->_ptr += n;
				return (*this);
			}

			iterator & operator-=(size_t n)
			{
				this->_ptr -= n;
				return (*this);
			}

			reference operator*() { return (*_ptr); };
			reference operator[](int n) const { return (*(this->_ptr + n));	};
			pointer operator->() { return (_ptr); };

		protected:
			pointer _ptr;
	};

	template <class Iterator1, class Iterator2>
    bool operator==(const iterator<Iterator1> &lhs, const iterator<Iterator2> &rhs)
    {
        return lhs.base() == rhs.base();
    }
    template <class Iterator1, class Iterator2>
    bool operator!=(const iterator<Iterator1> &lhs, const iterator<Iterator2> &rhs)
    {
        return lhs.base() != rhs.base();
    }

	template <class Iterator1, class Iterator2>
    bool operator>(const iterator<Iterator1> &lhs, const iterator<Iterator2> &rhs)
    {
        return lhs.base() > rhs.base();
    }
	
	template <class Iterator1, class Iterator2>
    bool operator<(const iterator<Iterator1> &lhs, const iterator<Iterator2> &rhs)
    {
        return lhs.base() < rhs.base();
    }

	template <class Iterator1, class Iterator2>
    bool operator>=(const iterator<Iterator1> &lhs, const iterator<Iterator2> &rhs)
    {
        return lhs.base() >= rhs.base();
    }
	template <class Iterator1, class Iterator2>
    bool operator<=(const iterator<Iterator1> &lhs, const iterator<Iterator2> &rhs)
    {
        return lhs.base() <= rhs.base();
    }
}

#endif