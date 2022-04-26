
#ifndef REVERSEITERATOR_HPP
#define REVERSEITERATOR_HPP

#include "Iterator.hpp"

namespace ft
{
template <typename Iter>
	class reverse_iterator 
	{
	private:
		Iter _base;

	public:
		typedef Iter iterator_type;
		typedef typename iterator_traits<Iter>::difference_type difference_type;
		typedef typename iterator_traits<Iter>::value_type value_type;
		typedef typename iterator_traits<Iter>::pointer pointer;
		typedef typename iterator_traits<Iter>::reference reference;
		typedef typename iterator_traits<Iter>::iterator_category iterator_category;
		
        reverse_iterator() : _base(){};
		reverse_iterator(Iter base) : _base(base){};
		reverse_iterator(const reverse_iterator<Iter> &other) : _base(other._base){};
		~reverse_iterator() {};

		Iter base() const{ return _base; };

		reverse_iterator<Iter> &operator=(const reverse_iterator<Iter> &other)
		{
			_base = other._base;
			return *this;
		}

		reverse_iterator<Iter> &operator++()
		{
			--_base;
			return *this;
		}

		reverse_iterator<Iter> operator++(int)
		{
			reverse_iterator<Iter> ite(_base--);
			return ite;
		}

		reference operator*() const
		{
			Iter ite(_base);
			--ite;
			return *ite;
		}

		pointer operator->() const
		{
			Iter ite(_base);
			--ite;
			return ite.operator->();
		}

		reverse_iterator<Iter> &operator--()
		{
			++_base;
			return *this;
		}

		reverse_iterator<Iter> operator--(int)
		{
			reverse_iterator<Iter> ite(_base++);
			return ite;
		}

		reverse_iterator<Iter> &operator+=(difference_type offset)
		{
			_base -= offset;
			return *this;
		}

		reverse_iterator<Iter> &operator-=(difference_type offset)
		{
			_base += offset;
			return *this;
		}

        reverse_iterator<Iter> &operator+(difference_type offset)
		{
			_base = _base - offset;
			return *this;
		}

		reverse_iterator<Iter> &operator-(difference_type offset)
		{
			_base = _base + offset;
			return *this;
		}
    };

    template <class Iterator, class Iterator2>
    bool operator==(const reverse_iterator<Iterator> &lhs,
                    const reverse_iterator<Iterator2> &rhs)
    {
        return lhs.base() == rhs.base();
    }
     template <class Iterator, class Iterator2>
    bool operator!=(const reverse_iterator<Iterator> &lhs,
                    const reverse_iterator<Iterator2> &rhs)
    {
        return lhs.base() != rhs.base();
    }
     template <class Iterator, class Iterator2>
    bool operator<(const reverse_iterator<Iterator> &lhs,
                   const reverse_iterator<Iterator2> &rhs)
    {
        return lhs.base() > rhs.base();
    }
     template <class Iterator, class Iterator2>
    bool operator<=(const reverse_iterator<Iterator> &lhs,
                    const reverse_iterator<Iterator2> &rhs)
    {
        return lhs.base() >= rhs.base();
    }
     template <class Iterator, class Iterator2>
    bool operator>(const reverse_iterator<Iterator> &lhs,
                   const reverse_iterator<Iterator2> &rhs)
    {
        return lhs.base() < rhs.base();
    }
     template <class Iterator, class Iterator2>
    bool operator>=(const reverse_iterator<Iterator> &lhs,
                    const reverse_iterator<Iterator2> &rhs)
    {
        return lhs.base() <= rhs.base();
    }

    template <class Iterator>
    reverse_iterator<Iterator> operator+(
        typename reverse_iterator<Iterator>::difference_type n,
        const reverse_iterator<Iterator> &rev_it)
    {
        return reverse_iterator<Iterator>(rev_it.base() - n);
    }
    template <class Iterator>
    typename reverse_iterator<Iterator>::difference_type
    operator-(const reverse_iterator<Iterator> &lhs,
              const reverse_iterator<Iterator> &rhs)
    {
        return rhs.base() - lhs.base();
    }
}

#endif