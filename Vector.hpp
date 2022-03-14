#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>

namespace ft
{

template <typename T, class Allocator = std::allocator<T>>
class Vector
{
	typedef T											value_type;
	typedef Allocator									allocator_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
	typedef typename allocator_type::size_type			size_type;
public:
	// Constructors & Destructors
	explicit Vector(const allocator_type & alloc = allocator_type()) : _alloc(alloc), _ptr(0), _size(0), _capacity(0) {};
	Vector(Vector & src) : _alloc(allocator_type()), _ptr(0), _size(0), _capacity(0) { *this = src; };
	virtual ~Vector() {
		// clear();
		if (_capacity > 0)
		{
			_alloc.deallocate(_ptr, _capacity);
			_capacity = 0;
		}
	};

	// Iterators

	// Capacity

	// Element access

	// Modifiers

	// Allocator
	void clear() {};
private:
	allocator_type	_alloc;
	pointer 		_ptr;
	size_t			_size;
	size_t			_capacity;
}; // class Vector

 #endif

} // namespace ft
