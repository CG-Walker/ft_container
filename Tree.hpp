#ifndef TREE_HPP
# define TREE_HPP

# include <memory>

# include "Iterator.hpp"
#include "tree_iterator.hpp"
# include "Utils.hpp"

namespace ft
{

	template <class Key, class T, class Compare, class Allocator = std::allocator<T> >
	class tree
	{
		private:
			// Member types
			typedef Key															key_type;
			typedef T															value_type;
			typedef node<T> *													link_type;
			typedef const node<T> *												const_link_type;
			typedef typename Allocator::size_type 								size_type;
			//typedef typename Allocator::template rebind<node<T> >::other		node_allocator_type;

			typedef typename Allocator::template rebind<node<T> >::other		node_allocator_type;

			typedef typename node_allocator_type::difference_type 				difference_type;

		public:
			// Constructors & Destructor
            typedef ft::tree_iterator_<T>										iterator;
		    typedef ft::tree_iterator_<const T>									const_iterator;
			tree(const Compare & compare, const Allocator & allocator)  : _compare(compare), _size(0), _alloc(node_allocator_type(allocator)) { initialize(); };

			tree(const tree & tree) : _compare(tree._compare), _alloc(tree._alloc), _size(0){};
			~tree()
			{
				destroy(this->_end->left);
				delete_node(this->_nil);
				delete_node(this->_end);
			}

			tree & operator=( const tree & other )
			{
				if (this != other)
				{
					this->clear();
					this->_compare = other._compare;
					for (iterator iter = other.begin(); iter != other.end(); ++iter)
						this->insert(*iter);
				}
				return (*this);
			}
	
			// Iterators
			iterator begin() { return (iterator(this->_begin, this->_nil)); }
			const_iterator begin() const { return const_iterator(this->_begin, this->_nil); }
			iterator end() { return iterator(this->_end, this->_nil); }
			const_iterator end() const { return const_iterator(this->_end, this->_nil); };

			// Modifiers
       		pair<iterator, bool> insert( const value_type & value )
			{
				link_type insert_place = search_insert_place(value);
				return (insert_node(value, insert_place));
			};

/* 		    iterator insert(iterator pos, const value_type & value)
			{
				if (pos == this->end()) // Si on veut ajouter à la fin
				{
					iterator max = end();
					if (this->size() > 0 && this->_compare(*(--max), value))
						return
					else
						return
				}
				if (this->_compare(value, *pos)) // Si la value est plus petite que celle de la pos
				{
					if (pos == this->begin())
						return (insert_node(value, this->_begin).first)
					iterator prev = pos - 1;
					if (this->_compare(*prev, value))
					{
						if (prev.base()->right == this->_nil)
							return (insert_node(value, prev.base()).first);
						else
							return (insert_node(value, pos.base()).first);
					}
				}
			} */

		iterator insert(iterator position, const value_type &value)
        {
            if (position == end())
            {
                iterator max = end();
                if (this->_size > 0 && compare_(*(--max), value))
                    return insert_node(value, max.base()).first;
                else
                    return insert(value).first;
            }
            if (compare_(value, *position)) // value < pos
            {
                if (position == begin())
                    return insert_node(value, this->_begin).first;
                iterator prev = position;
                --prev;
                if (compare_(*prev, value))
                {
                    if (prev.base()->right == this->_nil)
                        return insert_node(value, prev.base()).first;
                    else
                        return insert_node(value, position.base()).first;
                }
                return insert(value).first;
            }
            if (compare_(*position, value)) // pos < value
            {
                iterator max = end();
                --max;
                if (position == max)
                    return insert_node(value, max.base()).first;
                iterator next = position;
                ++next;
                if (compare_(value, *next))
                {
                    if (position.base()->right == this->_nil)
                        return insert_node(value, position.base()).first;
                    else
                        return insert_node(value, next.base()).first;
                }
                return insert(value).first;
            }
            return position;
        }

			// Capacity
			size_type size() const { return (this->_size); };

		private:
			link_type			_nil;
			link_type			_begin;
			link_type			_end;
			Compare				_compare;
			size_type			_size;
			node_allocator_type	_alloc;
		
			void initialize()
			{
				node<T> ptr_empty;
				this->_nil = this->_alloc.allocate(1);
				this->_alloc.construct(this->_nil, ptr_empty);
				this->_nil->left = this->_nil;
				this->_nil->right = this->_nil;

				this->_end = this->_alloc.allocate(1);
				this->_alloc.construct(this->_end, ptr_empty);
				this->_end->left = this->_nil;
				this->_begin = this->_end;
			}

			void delete_node( link_type node )
        	{
         	   this->_alloc.destroy(node);
        	   this->_alloc.deallocate(node, 1);
        	}
			iterator find( const key_type & key )
			{
				link_type node = find_node(key);
            	return (iterator(node, this->_nil));
			}

			link_type find_node( const key_type & key ) const
			{
				link_type node = this->_end;
				link_type tmp = this->_end->left;
				while (tmp != this->_nil)
				{
					if (!this->_compare(tmp->value, key))
					{	
						node = tmp;
						tmp = node->left;
					}
					else
						tmp = node->right;
				}	
				if (node != this->_end && !this->_compare(key, node->value))
					return (node);
				return (this->_end);
			}
			void clear()
			{
				destroy(this->_end->left);
				this->_begin = this->_end;
				this->_end->left = this->_nil;
				this->_size = 0;
			}

            void destroy(link_type node)
            {
                if (node != _nil)
                {
                    destroy(node->left);
                    destroy(node->right);
                    delete_node(node);
                }
            }

			ft::pair<iterator, bool> insert_node( const value_type & value, link_type insert_place )
			{
				link_type new_node = create_node(value);
				new_node->parent = insert_place;
				if (insert_place == this->_nil) // Si l'arbre est vide
				{
					new_node->parent = this->_end;
					this->_end->left = new_node;
				}
				else if (this->_compare(new_node->value, insert_place->value)) // Si le value est plus petite que celle de la place
					insert_place->left = new_node;
				else if (this->_compare(insert_place->value, new_node->value)) // Si le value est plus grande que celle de la place
					insert_place->right = new_node;
				else // Si la value existe déjà
				{
					this->_alloc.destroy(new_node);
					this->_alloc.deallocate(new_node, 1);
					return (ft::make_pair(iterator(insert_place, this->_nill), false));
				}
				this->_size++;
				return (ft::make_pair(iterator(new_node, this->_nill), true));
			}

			link_type create_node( const value_type & value )
			{
				link_type new_node = _alloc.allocate(1);
				_alloc.construct(new_node, this->_nil, value);
				return (new_node);
			}

			link_type search_insert_place( const value_type & value )
			{
				link_type prev_node = this->_nil;
				link_type root = this->_end->left;
				while (root != this->_nil)
				{
					prev_node = root;
					if (compare_(value, root->value))
						root = root->left;
					else if (compare_(root->value, value))
						root = root->right;
					else
						return (root);
				}
				return (prev_node);
        	}
	};
}

#endif