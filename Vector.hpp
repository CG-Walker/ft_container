#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <stdexcept>

# include <iostream>
	
# include "Iterator.hpp"
# include "ReverseIterator.hpp"
# include "Utils.hpp"

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
			// Member types
			typedef T											value_type;
			typedef Allocator									allocator_type;
			typedef typename allocator_type::size_type			size_type;
			typedef typename allocator_type::difference_type	difference_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef ft::iterator<T>								iterator;
			typedef ft::iterator<const T>						const_iterator;
			typedef ft::reverse_iterator<T>						reverse_iterator;
			typedef ft::reverse_iterator<const T>				const_reverse_iterator;

			// Constructors & Destructor
			explicit vector( const Allocator & alloc = allocator_type()) : _alloc(alloc), _first(NULL), _last(NULL), _capacity(0) {};
			explicit vector( size_type count, const T & value = T(), const Allocator & alloc = Allocator()) : _alloc(alloc), _first(NULL), _last(NULL), _capacity(0)
			{
				if (count > 0)
				{
					this->_first = this->_alloc.allocate(count);
					this->_last = _first + count;
					this->_capacity = count;
					std::uninitialized_fill_n(this->_first, count, value);
				}
			}
			template<class InputIt>
			//vector( InputIt first, InputIt last, const Allocator & alloc = Allocator() );
			vector( const vector & other ) : _alloc(other._alloc), _first(NULL), _last(NULL), _capacity(0) // Double free
			{
				size_type size = other.size();
				if (size > 0)
				{
					this->_first = this->_alloc.allocate(size);
					this->_last = _first + size;
					this->_capacity = other._capacity;
					std::uninitialized_copy(other._first, other._last, this->_first);
				}
			}
			
			~vector()
			{
				this->clear();
				this->_alloc.deallocate(this->_first, this->_capacity);
			}

			vector & operator=( const vector & other ) // À terminer
			{
				if (other == *this)
					return (*this);
				this->clear();
				this->insert(this->end(), other.begin(), other.end());
				return (*this);
			}

			// Element access
			reference at( size_type pos ) 
			{
				if (!(pos < this->size()))
					throw (std::out_of_range("vector::at: "));
				return (*this[pos]);
			}

			const_reference at( size_type pos ) const
			{
				if (!(pos < this->size()))
					throw (std::out_of_range("vector::at: "));
				return (*this[pos]);
			}

			reference operator[]( size_type pos ) {	return *(this->_first + pos);	};

			// Iterators
			iterator begin() { return iterator(this->_first); };

			const_iterator begin() const { return const_iterator(this->_first); };

			reverse_iterator rbegin() { return reverse_iterator(this->_last); };

			const_reverse_iterator rbegin() const { return const_reverse_iterator(this->_last); };

			iterator end() { return iterator(this->_last); };

			reverse_iterator rend() { return reverse_iterator(this->_first); };

			const_reverse_iterator rend() const { return const_reverse_iterator(this->_first); };

			const_iterator end() const { return const_iterator(this->_last); };

			// Capacity
			bool empty() const { return (this->_first == _last); };

			size_type size() const { return (this->_last - this->_first); };

			size_type max_size() const; // À implémenter

			void reserve( size_type new_cap )
			{
				if (new_cap > this->_capacity)
				{
					pointer new_first;
					new_first = this->_alloc.allocate(new_cap);
					size_type old_size = this->size();
					std::uninitialized_copy(this->_first, this->_last, new_first);
					this->clear();
					this->_alloc.deallocate(this->_first, this->_capacity);
					this->_first = new_first;
					this->_last = this->_first + old_size;
					this->_capacity = new_cap;
				}
			}

			size_type capacity() const { return (this->_capacity); };

			// Modifiers
			void clear()
			{
				for (pointer now = this->_first; now != this->_last; now++)
					this->_alloc.destroy(now);
			}

			void push_back( const value_type & value )
			{
				size_type new_size = this->size() + 1;
				if (new_size > this->_capacity)
					this->reserve(calc_new_capacity(new_size));
				this->_alloc.construct(this->_last, value);
				this->_last++;
			}

			iterator insert( iterator pos, const value_type & value );

			void insert( iterator pos, size_type count, const value_type & value )
			{
				size_type new_size = this->size() + count;
				size_type offset = pos - begin();
				
				if (new_size > this->_capacity)
				{
					std::cout << "TODO\n";
				}
				else
				{
					for (size_type i = 0; i < count; i++)
					{
						if (offset + i >= this->size())
						{
							this->_alloc.construct(&this->_first[offset + i], value);
						}
						else
						{
							this->_first[offset + 1] = value;
						}
					}
					
				}
			}

			//template <class InputIt>
			//void insert( iterator pos, InputIt first, InputIt last );

 			size_type calc_new_capacity(size_type new_cap)
        	{
				size_type max_cap = 500;//max_size();
				if (new_cap > max_cap)
					throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
				size_type cap = this->_capacity;
				if (cap >= max_cap / 2)
					return max_cap;
				return std::max(cap * 2, new_cap);
       		}

		private:
			allocator_type	_alloc;
			pointer			_first;
			pointer			_last;
			size_type		_capacity;
	}; // class Vector

	 template <class T, class Alloc>
	bool operator==(const vector<T> &lhs, const vector<T> &rhs)
	{
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}
	template <class T, class Alloc>
    bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        return !(lhs == rhs);
    }
	template <class T, class Alloc>
    bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }
	 template <class T, class Alloc>
    bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        return !(rhs < lhs);
    }
    template <class T, class Alloc>
    bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        return rhs < lhs;
    }
    template <class T, class Alloc>
    bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
    {
        return !(lhs < rhs);
    }
} // namespace ft

 #endif