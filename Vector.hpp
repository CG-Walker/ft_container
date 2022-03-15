#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <stdexcept>
	

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
			typedef ft::iterator<T>								iterator;			// À implémenter
			//typedef typename const_iterator					const_iterator;		// À implémenter
			//typedef typename reverse_iterator					reverse_iterator;	// À implémenter
			//typedef typename const_reverse_iterator			const_iterator;		// À implémenter

			// Constructors, Destructor & Operator
			vector() : _ptr(0), _size(0), _capacity(0) {};
			explicit vector( const Allocator & alloc );
			explicit vector( size_type count, const T & value = T(), const Allocator & alloc = Allocator());
			vector( const vector & other );
			
			~vector() {};

			vector & operator=( const vector & other )
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
				if (!(pos < this->_size))
					throw (std::out_of_range("vector::at: "));
				return (*this[pos]);
			}

			const_reference at( size_type pos ) const
			{
				if (!(pos < this->_size))
					throw (std::out_of_range("vector::at: "));
				return (*this[pos]);
			}

			reference operator[]( size_type pos ) {	return *(this->_ptr + pos);	};

			// Iterators
			iterator begin() { return iterator(this->_ptr); };

			//const_iterator begin() const { return (this->_ptr) };

			iterator end() { return iterator(this->_ptr + this->_size); };

			//const_iterator end() const { return (this->_ptr + this->_size); };

			// Capacity
			bool empty() const { return !(this->_size); };

			size_type size() const { return (this->_size); };

			size_type max_size() const; // À implémenter

			void reserve( size_type new_cap )
			{
				if (new_cap <= this->_capacity || new_cap == 0)
					return ;
				allocator_type alloc;
				pointer new_ptr;
				new_ptr = alloc.allocate(new_cap);
				for (size_type i = 0; i < this->_size; i++)
				{
					alloc.construct(& new_ptr[i], this->_ptr[i]);
					alloc.destroy(& this->_ptr[i]);
				}
				alloc.deallocate(this->_ptr, this->_capacity);
				this->_ptr = new_ptr;
				this->_capacity = new_cap;
			}

			size_type capacity() const { return (this->_capacity); };

			// Modifiers
			void clear()
			{
				allocator_type alloc;
				for (size_type i = 0; i < this->_size; i++)
				{
					alloc.destroy(this->_ptr[i]);
				}
				this->_size = 0;
			}

			iterator insert( iterator pos, const value_type & value )
			{
			
			}

			void insert( iterator pos, size_type count, const value_type & value );

			template <class InputIt>
			void insert( iterator pos, InputIt first, InputIt last );

		private:
			pointer			_ptr;
			size_type		_size;
			size_type		_capacity;
	}; // class Vector

	// Non-member functions

} // namespace ft

 #endif