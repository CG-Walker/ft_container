#ifndef FT_MAP_HPP
# define FT_MAP_HPP

#include <functional>
//#include "Iterator.hpp"
#include "ReverseIterator.hpp"
#include "Utils.hpp"
#include "Tree.hpp"
#include "tree_iterator.hpp"

namespace ft
{
	template <class Key, class Value, class Compare> // Pas encore compris
	class map_value_compare : private Compare
	{
		public:
			map_value_compare() : Compare() {}
			map_value_compare(Compare c) : Compare(c) {}

			bool operator()(const Value &lhs, const Value &rhs) const
			{
				return static_cast<const Compare &>(*this)(lhs.first, rhs.first);
			}
			bool operator()(const Value &lhs, const Key &rhs) const
			{
				return static_cast<const Compare &>(*this)(lhs.first, rhs);
			}
			bool operator()(const Key &lhs, const Value &rhs) const
			{
				return static_cast<const Compare &>(*this)(lhs, rhs.first);
			}
	};

	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:
			// Member types
			typedef Key													key_type;
			typedef T													mapped_type;
			typedef typename ft::pair<const Key, T>						value_type;
			typedef typename Allocator::size_type						size_type;
			typedef typename Allocator::difference_type					difference_type;
			typedef Compare												key_compare;
			typedef Allocator											allocator_type;
			typedef value_type &										reference;
			typedef const value_type &									const_reference;
			typedef typename Allocator::pointer							pointer;
			typedef typename Allocator::const_pointer					const_pointer;
			typedef ft::reverse_iterator<T>								reverse_iterator;
			typedef ft::reverse_iterator<const T>						const_reverse_iterator;
		
		private:
			typedef map_value_compare<key_type, value_type, key_compare>				tree_compare;
			typedef ft::tree<key_type, value_type, tree_compare, allocator_type>		tree_type;

		public:
			typedef typename tree_type::iterator								iterator; // PAS BON
			typedef typename tree_type::const_iterator							const_iterator; // PAS BON

		public:

			class value_compare : std::binary_function<value_type, value_type, bool>
			{
			public:
				Compare comp;
				value_compare(Compare c) : comp(c) {}

				typedef bool 		result_type;
				typedef value_type	first_argument_type;
				typedef value_type	second_argument_type;

				bool operator()(const value_type &lhs, const value_type &rhs) const { return (comp(lhs.first, rhs.first)); }
			};
						
			// Constructors & Destructor
			//map() {};
			explicit map( const key_compare & comp = key_compare(), const allocator_type & alloc = allocator_type() ) : _key_comp(comp), _value_comp(value_compare(comp)), _tree(tree_compare(comp), alloc) {};
			
			/* template <class InputIt>
			map( InputIt first, InputIt last, const Compare & comp = Compare(), const Allocator & alloc = Allocator() ) {}; */
			map( const map & other ) : _key_comp(other._key_comp), _value_comp(other._value_comp), _tree(other._tree)
			{
				insert(other.begin(), other.end());
			}
			~map() {};

			// Iterators
			iterator begin() { return (this->_tree.begin()); };
			const_iterator begin() const { return (this->_tree.begin()); };
			iterator end() { return (this->_tree.end()); };
			const_iterator end() const { return (this->_tree.end()); };
			reverse_iterator rbegin() { return (reverse_iterator(this->begin())); };
			const_reverse_iterator rbegin() const { return (const_reverse_iterator(this->begin())); };
			reverse_iterator rend() { return (reverse_iterator(this->end())); };
			const_reverse_iterator rend() const { return (const_reverse_iterator(this->end())); };

			// Capacity
			bool empty() const { return (this->begin() == this->end()); };
			size_type size() const { return (this->_tree.size()); };
		
			// Modifiers
			void clear() { this->_tree.clear(); };

			ft::pair<iterator, bool> insert( const value_type & value ) 
			{
				return (this->_tree.insert(value));
			}
			//iterator insert( iterator hint, const value_type & value );
			//template< class InputIt >
			//void insert( InputIt first, InputIt last );

			// Element access
			size_type count( const Key & key ) const { return (this->_tree.find(key) == this->end() ? 0 : 1) ;};
			iterator find(const key_type & key) { return (this->_tree.find(key)); };
			const_iterator find(const key_type & key) const { return (this->_tree.find(key)); };
			//ft::pair<iterator,iterator> equal_range( const Key & key ) { return (this->_tree.equal_range(key)); };
			//ft::pair<const_iterator,const_iterator> equal_range( const Key & key ) const { return (this->_tree.equal_range(key)); };
			iterator lower_bound( const Key & key ) { return (this->_tree.lower_bound(key)); };
			const_iterator lower_bound( const Key & key ) const { return (this->_tree.lower_bound(key)); };
			iterator upper_bound( const Key & key ) { return (this->_tree.upper_bound(key)); };
			const_iterator upper_bound( const Key & key ) const { return (this->_tree.upper_bound(key)); };

			// Observers
			key_compare key_comp() const { return (this->_key_comp); };
			value_compare value_comp() const { return (this->_value_comp); };

			// DEBUG
			void print_tree() { this->_tree.print_tree(); };

		private:
			key_compare		_key_comp;
			value_compare	_value_comp;
			tree_type		_tree;
	};

	// Non-member functions
	 template < class Key, class T, class Compare, class Alloc >
	bool operator==( const std::map<Key,T,Compare,Alloc> & lhs, const std::map<Key,T,Compare,Alloc> & rhs )
    {
		if (lhs.size() != rhs.size())
			return false;
		return equal(lhs.begin(), lhs.end(), rhs.begin());
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const std::map<Key,T,Compare,Alloc> & lhs, const std::map<Key,T,Compare,Alloc> & rhs )
    {
		return !(lhs == rhs);
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const std::map<Key,T,Compare,Alloc> & lhs, const std::map<Key,T,Compare,Alloc> & rhs )
    {
		return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), lhs.value_comp());
	}
    template< class Key, class T, class Compare, class Alloc >
	bool operator>( const std::map<Key,T,Compare,Alloc> & lhs, const std::map<Key,T,Compare,Alloc> & rhs )
    {
		return rhs < lhs;
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const std::map<Key,T,Compare,Alloc> & lhs, const std::map<Key,T,Compare,Alloc> & rhs )
	{
		return !(lhs > rhs);
	}
	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const std::map<Key,T,Compare,Alloc> & lhs, const std::map<Key,T,Compare,Alloc> & rhs )
    {
		return rhs < lhs;
	}
} // namespace ft

#endif