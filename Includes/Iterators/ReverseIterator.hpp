
#ifndef REVERSEITERATOR_HPP
# define REVERSEITERATOR_HPP

namespace ft
{
template <typename Iter>
	class reverse_iterator
	{
	protected:
		Iter _base;

	public:
		typedef typename iterator_traits<Iter>::difference_type		difference_type;
		typedef typename iterator_traits<Iter>::value_type			value_type;
		typedef typename iterator_traits<Iter>::pointer				pointer;
		typedef typename iterator_traits<Iter>::reference			reference;
		typedef typename iterator_traits<Iter>::iterator_category	iterator_category;
		
        reverse_iterator() : _base() {};
		explicit reverse_iterator(Iter base) : _base(base) {};
       template<class U>
		reverse_iterator(const reverse_iterator<U> &other)
		{
			_base = other.base();
		}
		~reverse_iterator() {};
		Iter base() const { return (this->_base); };
        template<class U>
		reverse_iterator &operator=(reverse_iterator<U> const &other)
		{
			_base = other.base();
			return (*this);
		}

		reverse_iterator<Iter> & operator++()
		{
			--this->_base;
			return (*this);
		}

		reverse_iterator<Iter> operator++(int)
		{
			reverse_iterator<Iter> ite(this->_base--);
			return (ite);
		}

		reference operator*() const
		{
			Iter	tmp = _base;
			return *(--tmp);
		}

		pointer operator->() const
		{
			return (&(operator*()));
		}
        
        reference operator[](difference_type n) const
		{
			return (base()[-n-1]);
		}

		reverse_iterator<Iter> & operator--()
		{
			++this->_base;
			return (*this);
		}

		reverse_iterator<Iter> operator--(int)
		{
			reverse_iterator<Iter> ite(this->_base++);
			return (ite);
		}

		reverse_iterator<Iter> & operator+=(difference_type offset)
		{
			this->_base -= offset;
			return (*this);
		}

		reverse_iterator<Iter> & operator-=(difference_type offset)
		{
			this->_base += offset;
			return (*this);
		}

        reverse_iterator<Iter> & operator+(difference_type offset)
		{
			this->_base = _base - offset;
			return (*this);
		}

		reverse_iterator<Iter> & operator-(difference_type offset)
		{
			this->_base = _base + offset;
			return (*this);
		}
    };

   	template< class Iterator1, class Iterator2 >
	bool operator==( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
	{
		return(lhs.base() == rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator!=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
	{
		return(lhs.base() != rhs.base());
	}
	template< class Iterator1, class Iterator2 >
	bool operator<( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
	{
		return(lhs.base() < rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator<=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
	{
		return(lhs.base() <= rhs.base());
	}

  	template< class Iterator1, class Iterator2 >
	bool operator>( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
	{
		return(lhs.base() > rhs.base());
	}

  	template< class Iterator1, class Iterator2 >
	bool operator>=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs )
	{
		return(lhs.base() >= rhs.base());
	}

    template <class Iterator>
    reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> & rev_it)
    {
        return reverse_iterator<Iterator>(rev_it.base() - n);
    }

    template <class Iterator>
    typename reverse_iterator<Iterator>::difference_type
    operator-(const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs)
    {
        return (rhs.base() - lhs.base());
    }
}

#endif