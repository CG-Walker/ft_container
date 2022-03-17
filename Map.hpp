#ifndef FT_MAP_HPP
# define FT_MAP_HPP

#include <functional>
#include "Iterator.hpp"
#include "ReverseIterator.hpp"
#include "Utils.hpp"

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T>>>
	class map
	{
		public:
			// Member types
			typedef Key											key_type;
			typedef T											mapped_type;
			typedef typename std::pair<const Key, T>			value_type;
			typedef typename Allocator::size_type				size_type;
			typedef typename Allocator::difference_type			difference_type;
			typedef Compare										key_compare;
			typedef Allocator									allocator_type;
			typedef value_type &								reference;
			typedef const value_type &							const_reference;
			typedef typename Allocator::pointer					pointer;
			typedef typename Allocator::const_pointer			const_pointer;
			typedef ft::iterator<T>								iterator;
			typedef ft::iterator<const T>						const_iterator;
			typedef ft::reverse_iterator<T>						reverse_iterator;
			typedef ft::reverse_iterator<const T>				const_reverse_iterator;

			class value_compare : std::binary_function<value_type, value_type, bool>
			{
				public:
					// Member types
					typedef bool 		result_type;
					typedef value_type 	first_argument_type;
					typedef value_type 	second_argument_type;

					bool operator()( const value_type & lhs, const value_type & rhs ) const { return (comp(lhs.first, rhs.first)); };
				protected:
					Compare comp;
					value_compare( Compare c ) : comp(c) {};
			}
			map() {};
			explicit map( const Compare& comp, const Allocator& alloc = Allocator() ) {};
			template< class InputIt >
			map( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() ) {};
			~map(){};
		private:

	};
} // namespace ft

#endif