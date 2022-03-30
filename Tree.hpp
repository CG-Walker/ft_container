#ifndef TREE_HPP
# define TREE_HPP

# include <memory>

//# include "Iterator.hpp"
#include "tree_iterator.hpp"
# include "Utils.hpp"
#include <iostream>

namespace ft
{
	template <class Key, class T, class Compare, class Allocator = std::allocator<T> >
	class tree
	{
		public:
			// Member types
 			typedef ft::tree_iterator<T *>										iterator;
			typedef ft::tree_iterator<const T *>								const_iterator;

		private:
			// Member types
			typedef Key															key_type;
			// T = value_type de map = ft::pair<const Key, T> 
			typedef T															value_type;
			typedef ft::node<T> *												link_type;
			typedef const ft::node<T> *											const_link_type;
			typedef typename Allocator::size_type 								size_type;
			typedef typename Allocator::template rebind<node<T> >::other		node_allocator_type;
			typedef typename node_allocator_type::difference_type 				difference_type;

		public:
			// Constructors & Destructor
			tree(const Compare & compare, const Allocator & allocator)  : _current(NULL), _compare(compare), _size(0), _alloc(node_allocator_type(allocator)) { initialize(); };
			//tree(const tree & tree) : _compare(tree._compare), _alloc(tree._alloc), _size(0){};
			~tree()	{};

			tree & operator=( const tree & other ) {};
	
			// Iterators
			iterator begin() { return (iterator(this->_begin, this->_nil)); }
			const_iterator begin() const { return const_iterator(this->_begin, this->_nil); }
			iterator end() { return iterator(this->_end, this->_nil); }
			const_iterator end() const { return const_iterator(this->_end, this->_nil); }; // A corriger

			// Capacity
			size_type size() const { return (this->_size); };
			size_type max_size() const
			{
				return (std::min(static_cast<size_type>(std::numeric_limits<difference_type>::max()), alloc_.max_size()));
			}

			// Modifiers
			void clear()
			{
				this->delete_branch(this->_current);
				this->_size = 0;
				this->_begin = this->_end;
				this->_current = NULL;
			}

			ft::pair<iterator, bool> insert(const value_type & value)
			{
				link_type root = this->_current;
				link_type new_node = create_node(value);
				if (this->_current == NULL) // Signifie que l'arbe est vide
				{
					this->_current = new_node;
					this->_current->left->parent = this->_current;
					this->_current->right->parent = this->_current;
					this->_size += 1;
					this->_begin = new_node;
					return (ft::make_pair(iterator(new_node, this->_nil), true));
				}
				if (this->find(value.first) != this->end())	// Signifie que la clé existe déjà
					return (ft::make_pair(iterator(new_node, this->_nil), false));
				while (true)
				{
					if (this->_current == this->_nil)
					{
						new_node->parent = this->_current->parent;
						replace_parent_node(this->_current, new_node);
						new_node->left->parent = new_node;
						new_node->right->parent = new_node;
						this->_current = root;
						this->_size += 1;
						break ;
					}
					else
						replace_parent_node(this->_current, this->_current->left);
				}
				return (ft::make_pair(iterator(new_node, this->_nil), true));
			}

			iterator insert( iterator hint, const value_type & value ) // À vérifier
			{
				link_type root = this->_current;
				link_type new_node = create_node(value);
	
				while (this->_current->value != *hint)
				{
					else if (this->_compare(this->_current->value, *hint))
						this->_current = this->_current->right;
					else
						this->_current = this->_current->left;
				}
				while (true)
				{
					if (this->_current == this->_nil)
					{
						new_node->parent = this->_current->parent;
						if (this->_compare(value, this->_current->parent->value))
							this->_current->parent->left = new_node;
						else
							this->_current->parent->right = new_node;
						new_node->left->parent = new_node;
						new_node->right->parent = new_node;
						this->_current = root;
						this->_size += 1;
						break ;
					}
					else if (this->_compare(value, this->_current->value))
						this->_current = this->_current->left;
					else
						this->_current = this->_current->right;
				}
				this->_current = root;
				return (ft::make_pair(iterator(new_node, this->_nil), true));
			}

			template <class InputIt>
			void insert( InputIt first, InputIt last )
			{
				for (InputIt it = first ; it <= last ; it++)
					insert(*it);
			}

			void    erase(iterator pos)
			{
				iterator begin = begin();
				link_type node
				link_type replaced_node;
				if (pos == end())
					return;
				if (pos == begin())
					_begin = begin.next();
				node = pos.base();
				if (node->left == _nil && node->right == _nil)
				{
					replace_parent_node(node, _nil);
					delete_node(node);
				}
				else if (node->left != _nil && node->right == _nill)
				{
					replace_parent_node(node, node->left);
					node->left->parent = node->parent;
					delete_node(node);
				}
				else if (node->left == _nil && node->right != _nill)
				{
					replace_parent_node(node, node->right);
					node->right->parent = node->parent;
					delete_node(node);
				}
				else
				{
					replace_parent_node(node, node->right);
					node->left->parent = node->right;
					node->right->left = node->left;
					node->right->parent = node->parent;
					delete_node(node);
				}
			}

			void erase(iterator first, iterator last)
			{
				while (first <= last)
					erase(first++);
			}

			size_type erase( const Key & key );
			{
				iterator ite = find(key);
				if (ite == end())
					return(0);
				erase(ite);
				return(1);
			}
			//void swap( map& other );

			// Element access
			iterator find(const key_type & key)
			{
				while (true)
				{
					if (this->_current == this->_nil)
						break ;
					if (this->_current->value.first == key)
						return (iterator(this->_current, this->_nil));
					else if (this->_compare(key, this->_current->value))
						this->_current = this->_current->left;
					else if (!(this->_compare(key, this->_current->value)))
						this->_current = this->_current->right;
				}
				return (this->end());
			}

/* 			ft::pair<iterator,iterator> equal_range( const Key & key )
			{
				link_type lower = get_root();
				link_type upper = end_;
				while (lower != nil_)
				{
					if (compare_(key, lower->value))
					{
						upper = lower;
						lower = lower->left;
					}
					else if (compare_(lower->value, key))
					{
						lower = lower->right;
					}
					else
					{
						if (lower->right != nil_)
							upper = utils_.search_tree_min(lower->right, nil_);
						ft::pair<link_type, link_type> range = ft::make_pair(lower, upper);
					}
				}
					return ft::make_pair(const_iterator(range.first, nil_), const_iterator(range.second, nil_));
            	return ft::make_pair(upper, upper);
			} */

			//ft::pair<const_iterator,const_iterator> equal_range( const Key & key ) const;
/* 			iterator lower_bound( const Key & key ) // Renvoie key <= X
			{
				iterator it = this->_begin();
				while (this->_compare(key, *it)) // if key < *it
				{
					
				}
			} */
			//const_iterator lower_bound( const Key& key ) const;
			//iterator upper_bound( const Key& key );
			//const_iterator upper_bound( const Key& key ) const;
			
			// DEBUG
			void	print_tree() { print_tree_rec(_current, 0); };

		private:
			link_type			_current;
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
				this->_nil->parent = this->_nil; // Pas nécessaire ?

				this->_end = this->_alloc.allocate(1);
				this->_alloc.construct(this->_end, ptr_empty);
				this->_begin = this->_begin;
			}

			void	print_tabulation(int indentation)
			{
				for(int i = 0; i < indentation; i++)
				{
					std::cout << "\t";
				}
			}
			void	print_tree_rec(link_type root, int level)
			{
				if (root == NULL)
					return ;
				if (root == _nil)
				{
					print_tabulation(level);
					std::cout << "EMPTY" << std::endl;
					return ;
				}
				print_tabulation(level);
				std::cout << "(" << root->value.first << ", " << root->value.second << ")"<< std::endl;
				print_tabulation(level);
				std::cout << "LEFT" << std::endl;
				print_tree_rec(root->left, level + 1);
				print_tabulation(level);
				std::cout << "RIGHT" << std::endl;
				print_tree_rec(root->right, level + 1);
			}

			link_type create_node(const value_type & value)
			{
				link_type new_node = this->_alloc.allocate(1);
				_alloc.construct(new_node, node<value_type>(this->_nil, value)); // Ne fonctionne pas
				return (new_node);
			}

			void    delete_node(link_type node)
			{
				this->_alloc.destroy(node);
				this->_alloc.deallocate(node, 1);
			}

			void	delete_branch(link_type node)
			{
				if (node != this->_nil)
				{
					std::cout << "Deleting (" << node->value.first << ":" << node->value.second << ") ...\n";
					delete_branch(node->left);
					delete_branch(node->right);
					delete_node(node);
				}
			}

			void	replace_parent_node(link_type node, link_type new_node)
			{
				if (_compare(node->value, node->parent->value))
						node->parent->left = new_node;
					else
						node->parent->right = new_node;
			}
	};
}

// Non-member functions
/* 
template< class Key, class T, class Compare, class Alloc >
bool operator==( const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs );
template< class Key, class T, class Compare, class Alloc >
bool operator!=( const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs );
template< class Key, class T, class Compare, class Alloc >
bool operator<( const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs );
template< class Key, class T, class Compare, class Alloc >
bool operator<=( const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs );
template< class Key, class T, class Compare, class Alloc >
bool operator>( const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs );
template< class Key, class T, class Compare, class Alloc >
bool operator>=( const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs ); */

#endif

// nodes (parent, left, right, value)

// tree mon_arbre(); -> _current -> NULL
// mon_arbre.add_value(42); -> if (_current == NULL)
									// node
// mon_arbre.add_value(56); current -> right 52
