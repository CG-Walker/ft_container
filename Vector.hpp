#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>

namespace ft
{
	template <class T, class Allocator = std::allocator<T>>
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
			//typedef typename iterator							iterator;			// À implémenter
			//typedef typename const_iterator					const_iterator;		// À implémenter
			//typedef typename reverse_iterator					reverse_iterator;	// À implémenter
			//typedef typename const_reverse_iterator			const_iterator;		// À implémenter

			// Constructors, Destructor & Operator
			vector();
			explicit vector( const Allocator & alloc );
			explicit vector( size_type count, const T & value = T(), const Allocator & alloc = Allocator());
			vector( const vector & other );
			
			~vector();

			// Element access

			// Iterators

			// Capacity
			void reserve( size_type new_cap )
			{
				if (new_cap <= this->capacity() || new_cap == 0)
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
			// Modifiers

		private:
			pointer			_ptr;
			size_type		_size;
			size_type		_capacity;
	}; // class Vector

	// Non-member functions

} // namespace ft

 #endif