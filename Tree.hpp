#ifndef TREE_HPP
# define TREE_HPP

#include "iterator.hpp"
#include "utility.hpp"

namespace ft
{
	template <class T>
	class node
	{
		public :
			node	*parent;
			node	*left;
			node	*right;
			T		value;
	
		node() : parent(NULL), left(NULL), right(NULL) {};
		node(node *nil, const T *value) : parent(nil), left(nil), right(nil), value(value) {};
	};
	template <class Key, class T, class Compare, class Allocator = std::allocator<T> >
    class tree
	{
		private:
			typedef Key key_type;
			typedef T value_type;
			typedef node<T> *link_type;
			typedef const node<T> *const_link_type;
			typedef typename Allocator::size_type size_type;
			typedef typename Allocator::template rebind<rb_node_<T> >::other node_allocator_type;
       		typedef typename node_allocator_type::difference_type difference_type;

			link_type _nil;
     		link_type _begin;
        	link_type _end;
			Compare             _compare;
			size_type           _size;
            node_allocator_type _alloc;            

		public:
			tree(const Compare &compare, const Allocator &allocator) : _compare(compare),  {};
	}

}

#endif


    };