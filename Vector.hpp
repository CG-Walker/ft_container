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
			//typedef typename iterator							iterator;		// À implémenter
			//typedef typename const_iterator					const_iterator;	// À implémenter
			//typedef typename reverse_iterator					iterator;		// À implémenter
			//typedef typename const_reverse_iterator			const_iterator;	// À implémenter


			// Constructors, Destructor & Operator

			// Element access

			// Iterators

			// Capacity

			// Modifiers

		private:
			allocator_type	_alloc;
			pointer 		_ptr;
			size_t			_size;
			size_t			_capacity;
	}; // class Vector

	// Non-member functions

} // namespace ft

 #endif