#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <stdexcept>

# include <iostream>
	

# include "Iterator.hpp"

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
			//typedef typename const_iterator					const_iterator;		// À implémenter
			//typedef typename reverse_iterator					reverse_iterator;	// À implémenter
			//typedef typename const_reverse_iterator			const_iterator;		// À implémenter

			// Constructors, Destructor & Operator
			explicit vector( const Allocator & alloc = allocator_type()) : _alloc(alloc), _first(NULL), _last(NULL), _capacity(0) {};
			explicit vector( size_type count, const T & value = T(), const Allocator & alloc = Allocator());
			vector( const vector & other );
			
			~vector() {}; // À terminer

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

			iterator end() { return iterator(this->_last); };

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
				{
					this->_alloc.destroy(now);
				}
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

	// Non-member functions

} // namespace ft

 #endif