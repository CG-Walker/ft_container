#ifndef STACK_HPP
#define STACK_HPP

#include <vector>

namespace ft
{
	template <class T, class Container = std::vector<T> >
	class stack
	{
		public:
			// Member types
			typedef Container								container_type;
			typedef typename Container::value_type			value_type;
			typedef typename Container::size_type			size_type;
			typedef typename Container::reference			reference;
			typedef typename Container::const_reference		const_reference;

			// Constructors, Destructor & Operator
			explicit stack( const Container & cont = Container() ) : c(cont) {};
			stack( const stack & other ) : c(other.c) {};

			~stack() {};

			stack & operator=( const stack & other )
			{
				this->c = other.c;
				return(*this);
			}

			// Element access
			reference top()	{ return (this->c.back()); };
			const_reference top() const { return (this->c.back()); }

			// Capacity
			bool empty() const { return (this->c.empty()); };

			size_type size() const { return (this->c.size()); };

			// Modifiers
			void push( const value_type & value ) {	this->c.push_back(value); };

			void pop() { this->c.pop_back(); }

			template <class Tn, class ContainerN>
				friend bool operator== (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs);

			template <class Tn, class ContainerN>
				friend bool operator!= (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs);
			
			template <class Tn, class ContainerN>
				friend bool operator< (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs);

			template <class Tn, class ContainerN>
				friend bool operator<= (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs);

			template <class Tn, class ContainerN>
				friend bool operator> (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs);

			template <class Tn, class ContainerN>
				friend bool operator>= (const ft::stack<Tn, ContainerN>& lhs, const ft::stack<Tn, ContainerN>& rhs);
		private:
			Container c;
	}; // Class Vector

	// Non-member functions
	template< class T, class Container >
	bool operator==( const ft::stack<T,Container> & lhs, const ft::stack<T,Container> & rhs )
	{
		return (lhs.c == rhs.c);
	}

	template< class T, class Container >
	bool operator!=( const ft::stack<T,Container> & lhs, const ft::stack<T,Container> & rhs )
	{
		return (lhs.c != rhs.c);
	}

	template< class T, class Container >
	bool operator<( const ft::stack<T,Container> & lhs, const ft::stack<T,Container> & rhs )
	{
		return (lhs.c < rhs.c);
	}

	template< class T, class Container >
	bool operator<=( const ft::stack<T,Container> & lhs, const ft::stack<T,Container> & rhs )
	{
		return (lhs.c <= rhs.c);
	}

	template< class T, class Container >
	bool operator>( const ft::stack<T,Container> & lhs, const ft::stack<T,Container> & rhs )
	{
		return (lhs.c > rhs.c);
	}

	template< class T, class Container >
	bool operator>=( const ft::stack<T,Container> & lhs, const ft::stack<T,Container> & rhs )
	{
		return (lhs.c >= rhs.c);
	}
} // Namespace ft

#endif