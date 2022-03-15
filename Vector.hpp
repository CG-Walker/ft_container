#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <stdexcept>
# include <limits>

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
			vector( const vector & other ) : _alloc(other._alloc), _first(NULL), _last(NULL), _capacity(0) // Double free, normal ?
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

			vector & operator=( const vector & other )
			{
				assign(other._first, other._last);
				return (*this);
			}

			allocator_type get_allocator() const { return (this->_alloc); };

			void assign( size_type count, const T & value )
			{
				if (count > this->_capacity)
				{
					this->clear();
					this->reserve(count);
		            std::uninitialized_fill_n(this->_first, count, value);
				}
				else
				{
					this->clear();
					std::fill_n(this->_first, count, value);
				}
				this->_last = this->_first + count;
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

			reference front() { return *(this->begin()); };

			const_reference front() const { return *(this->begin()); };

			reference back() { return *(this->end() - 1); };

			const_reference back() const { return *(this->end() - 1); };

			T * data() { return (this->_first); };

			const T * data() const { return (this->_first); };

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

			size_type max_size() const
			{
				return (std::min(static_cast<size_type>(std::numeric_limits<difference_type>::max()), this->_alloc.max_size()));
			}

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
				pointer now = this->_last;
				while (now != this->_first)
				{
					this->_alloc.destroy(--now);
				}
				this->_last = this->_first;
			}

			iterator insert( iterator pos, const value_type & value ); // TODO

			void insert( iterator pos, size_type count, const value_type & value ) // TODO
			{
				size_type new_size = this->size() + count;
				size_type offset = pos - begin();
				
				if (new_size > this->_capacity)
				{
					new_size = calc_new_capacity(new_size);
					size_type old_capacity = this->_capacity;
					size_type old_size = this->size();
					pointer new_first = this->_alloc.allocate(new_size);

					std::uninitialized_copy(this->begin(), pos, new_first);
					std::uninitialized_fill_n(new_first + offset, count, value);
					std::uninitialized_copy(pos, this->end(), new_first + offset + count);

					clear();
					this->_alloc.deallocate(this->_first, old_capacity);
					this->_first = new_first;
					this->_last = this->_first + old_size + count;
					this->_capacity = this->_first + new_size;
				}
				else
				{
					// Tout décaler
				}
			}

			template <class InputIt>
			void insert( iterator pos, InputIt first, InputIt last ); // TODO

			iterator erase( iterator pos ) { return this->erase(pos, pos + 1); };

			iterator erase( iterator first, iterator last )
			{
				difference_type offset = std::distance(this->_first, this->_last);
				for (iterator it = first; it + offset != this->end(); ++it)
					*it = *(it + offset);
				pointer now = this->_last;
				while (now != (this->_last - offset))
					this->_alloc.destroy(--now);
				this->_last = (this->_last - offset);
				return (this->_first);
			}

			void push_back( const value_type & value )
			{
				size_type new_size = this->size() + 1;
				if (new_size > this->_capacity)
					this->reserve(calc_new_capacity(new_size));
				this->_alloc.construct(this->_last, value);
				this->_last++;
			}

			void pop_back()
			{
				this->_alloc.destroy((this->_last - 1));
				this->_last--;
			}

			void resize( size_type count, T value = T() )
			{
				if (count < size())
				{
					this->erase(this->begin() + count, this->end());
				}
				else if (count > this->size())
				{
					insert(this->end(), count - this->size(), value);
				}
			}

			void swap( vector& other )
			{

				pointer buffer_first = other._first;
				pointer buffer_last = other._last;
				size_type buffer_capacity = other._capacity;

				other._first = this->_first;
				other._last = this->_last;
				other._capacity = this->_capacity;

				this->_first = buffer_first;
				this->_last = buffer_last;
				this->_capacity = buffer_capacity;
			}

		private:
			allocator_type	_alloc;
			pointer			_first;
			pointer			_last;
			size_type		_capacity;

		// Private member functions

		size_type calc_new_capacity(size_type new_cap)
        {
			size_type max_cap = max_size();
			if (new_cap > max_cap)
				throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
			size_type cap = this->_capacity;
			if (cap >= max_cap / 2)
				return max_cap;
			return std::max(cap * 2, new_cap);
       	}
	}; // class Vector

	// Non-member functions
	template <class T, class Alloc>
	bool operator==(const vector<T> & lhs, const vector<T> & rhs)
	{
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
    bool operator!=(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
    {
        return !(lhs == rhs);
    }

	template <class T, class Alloc>
    bool operator<(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
    {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }

	template <class T, class Alloc>
    bool operator<=(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
    {
        return !(rhs < lhs);
    }

    template <class T, class Alloc>
    bool operator>(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
    {
        return (rhs < lhs);
    }

    template <class T, class Alloc>
    bool operator>=(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
    {
        return !(lhs < rhs);
    }
} // namespace ft

 #endif