#include <vector>

namespace ft
{

template <class T, class Container = std::vector<T>>
class stack
{
public:
	// Member types
	typedef Container								container_type;
	typedef typename Container::value_type			value_type;
	typedef typename Container::size_type			size_type;
	typedef typename Container::reference			reference;
	typedef typename Container::constr_reference	const_reference;

	// Constructors, Destructor & Operator
	explicit stack( const Container & cont = Container() );
	stack( const stack & other );

	~stack();

	stack & operator=( const stack & other );
	{
		c = other.c;
		return(*this);
	}

	// Element access
	reference top()
	{ 
		 return (this->c.back());
	}
	const_reference top() const
	{ 
		 return (this->c.back());
	}

	// Capacity
	bool empty() const
	{
		if (size() == 0)
			return (true);
		else
			return (false);
	};

	size_type size() const
	{
		return (c.size());
	}

	// Modifiers
	void push( const value_type & value )
	{
		c.push_back(value)
	}

	void pop()
	{
		c.pop_back();
	}

private:
	Container c;
}; // Class Vector

// Non-member functions :
template< class T, class Container >
bool operator==( const ft::stack<T,Container> & lhs, const ft::stack<T,Container> & rhs )
{
	if (lhs == rhs) // .c ou pas ?
		return (true);
	else
		return (false);
}

template< class T, class Container >
bool operator!=( const ft::stack<T,Container> & lhs, const ft::stack<T,Container> & rhs )
{
	if (lhs != rhs)
		return (true);
	else
		return (false);
}

template< class T, class Container >
bool operator<( const ft::stack<T,Container> & lhs, const ft::stack<T,Container> & rhs )
{
  	if (lhs < rhs)
		return (true);
	else
		return (false);
}

template< class T, class Container >
bool operator<=( const ft::stack<T,Container> & lhs, const ft::stack<T,Container> & rhs )
{
  	if (lhs <= rhs)
		return (true);
	else
		return (false);
}

template< class T, class Container >
bool operator>( const ft::stack<T,Container> & lhs, const ft::stack<T,Container> & rhs )
{
  	if (lhs > rhs)
		return (true);
	else
		return (false);
}

template< class T, class Container >
bool operator>=( const ft::stack<T,Container> & lhs, const ft::stack<T,Container> & rhs )
{
  	if (lhs >= rhs)
		return (true);
	else
		return (false);
}

} // Namespace FT