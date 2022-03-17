#ifndef TREE_HPP
# define TREE_HPP

# include <memory>

# include "Iterator.hpp"
# include "Utils.hpp"

namespace ft
{
	template <class T>
	class node
	{
		public :
			node *	parent;
			node *	left;
			node *	right;
			T		value;
	
		node() : parent(NULL), left(NULL), right(NULL) {};
		node(node * nil, const T * value) : parent(nil), left(nil), right(nil), value(value) {};
	};

	template <class Key, class T, class Compare, class Allocator = std::allocator<T>>
	class tree
	{
		private:
			// Member types
			typedef Key															key_type;
			typedef T															value_type;
			typedef node<T> *													link_type;
			typedef const node<T> *												const_link_type;
			typedef typename Allocator::size_type 								size_type;
			typedef typename Allocator::template rebind<rb_node_<T> >::other 	node_allocator_type;
       		typedef typename node_allocator_type::difference_type 				difference_type;

		public:
			// Constructors & Destructor
			tree(const Compare & comp, const Allocator & alloc) : _compare(comp), _alloc(alloc), _size(0) { initialize(); };
			tree(const tree & other) : _compare(other._compare), _alloc(node_allocator_type(allocator)), _size(0) { initialize(); };
			~tree()
			{
				destroy(this->_end->left);
				delete_node(this->_nil);
				delete_node(this->_end);
			}
			//Member fonction
			iterator begin(){return iterator(this->_begin, this->_nil);}
			
			const_iterator begin() const{return const_iterator(this->_begin, this->_nil);}

			iterator end(){return iterator(this->_end, this->_nil);}
			const_iterator end() const{return const_iterator(this->_end, this->_nil);};

			size_type size() const{return this->_size;};

			tree &operator=(const tree &other)
			{
				if (this !=other)
				{
					clear();
					this->_compare = other._compare;
					for (iterator iter = other.begin(); iter != other.end(); ++iter)
                		insert(*iter);
				}
				return(*this);
			}
		private:
			link_type			_nil;
			link_type			_begin;
			link_type			_end;
			Compare				_compare;
			size_type			_size;
			node_allocator_type	_alloc;
		
			void initialize()
			{
				this->_nil = this->_alloc.allocate(1);
				this->_alloc.construct(this->_nil);
				this->_nil->left = this->_nil;
				this->_nil->right = this->_nil;

				this->_end = this->_alloc.allocate(1);
				this->_alloc.construct(this->_end);
				this->_end->left = this->_nil;
				this->_begin = this->_end;
			}

			void delete_node(link_type node)
        	{
         	   this->_alloc.destroy(node);
        	   this->_alloc.deallocate(node, 1);
        	}
			iterator find(const key_type &key)
			{
				link_type node = find_node(key);
            	return iterator(node, this->_nil);
			}
			link_type find_node(const key_type &key) const
			{
				link_type node = this->_end;
				link_type tmp = this->_end->left;
				while(tmp != this->_nil)
				{
					if(!_compare(tmp->value, key))
					{	
						node = tmp;
						tmp = node->left
					}
					else
						tmp = node->right;
				}	
				if (node != this->_end && !_compare(key, node->value))
					return node;
				return this->_end;
			}
			void clear(void);
			{
				destroy(this->_end->left)
				this->_begin = this->_end;
				this->_end->left = this->_nil;
				this->_size = 0;
			}
	};
}

#endif