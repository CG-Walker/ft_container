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
 			typedef ft::tree_iterator_<T *>										iterator;
			typedef ft::tree_iterator_<const T *>								const_iterator;

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
			/* iterator begin() { return (iterator(this->_begin, this->_nil)); }
			const_iterator begin() const { return const_iterator(this->_begin, this->_nil); }
			iterator end() { return iterator(this->_end, this->_nil); }
			const_iterator end() const { return const_iterator(this->_end, this->_nil); }; */ // A corriger

			// Modifiers
			ft::pair<iterator, bool> insert(const value_type & value)
			{
				link_type root = this->_current;
				link_type new_node = NULL;
				if (this->_current == NULL) // Signifie que l'arbe est vide
				{
					link_type new_node = create_node(value);
					this->_current = new_node;
					std::cout << "new node created : (" << new_node->value.first << ":" << new_node->value.second << ")" << std::endl;
					this->_current->left->parent = this->_current;
					this->_current->right->parent = this->_current;
					return (ft::make_pair(iterator(new_node, this->_nil), true));
				}
				// Vérifier si la clé existe déjà
				// Si c'est le cas -> return (ft::make_pair(iterator(value), false));
				while (true)
				{
					if (this->_current == this->_nil)
					{
						new_node = create_node(value);
						new_node->parent = this->_current->parent;
/* 						new_node->left->parent = new_node;
						new_node->right->parent = new_node; */
						if (this->_compare(value, this->_current->parent->value)) // A vérifier en cas d'égalité
							this->_current->parent->left = new_node;
						else
							this->_current->parent->right = new_node;
						this->_current = root;
						break ;
					}
					else if (this->_compare(value, this->_current->value)) // A vérifier en cas d'égalité
					{
						std::cout << "(" << this->_current->value.first << ":" << value.first << ") - Direction la gauche\n";
						this->_current = this->_current->left;
					}
					else if (!(this->_compare(value, this->_current->value)))
					{
						std::cout << "(" << this->_current->value.first << ":" << value.first << ") - Direction la droite\n";
						this->_current = this->_current->right;
					}
				}
				//std::cout << new_node << std::endl;
				std::cout << "new node created : (" << new_node->value.first << ":" << new_node->value.second << ")" << std::endl;
				return (ft::make_pair(iterator(new_node, this->_nil), true));
			}

			// Element access
			iterator find(const key_type & key)
			{
				while (true)
				{
					if (this->_current == this->_nil)
					{
						std::cout << "Pas de " << key << " trouvé, fin de l'arbre.\n";
						break ;
					}
					if (this->_current->value.first == key)
						return (iterator(this->_current, this->_nil));
					else if (this->_compare(key, this->_current->value)) // A vérifier en cas d'égalité
					{
						std::cout << "Pas de " << key << ", direction la gauche.\n";
						this->_current = this->_current->left;
					}
					else if (!(this->_compare(key, this->_current->value)))
										{
						std::cout << "Pas de " << key << ", direction la droite.\n";
						this->_current = this->_current->right;
					}
				}
				//return (this->end());
				return (iterator(this->_current, this->_nil)); // PAS BON
			}

			void	print_tree()
			{
				print_tree_rec(_current, 0);
			}
			// Capacity
			size_type size() const { return (this->_size); };

		private:
			link_type			_current;
			link_type			_nil;
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
			}

			void	print_tabulation(int indentation)
			{
				for(int i = 0; i < indentation; i++)
				{
					std::cout << "    ";
				}
			}
			void	print_tree_rec(link_type root, int level)
			{
				if(root == _nil)
				{
					print_tabulation(level);
					std::cout << "EMPTY" << std::endl;
					return ;
				}
				print_tabulation(level);
				std::cout << "KEY: " << root->value.first <<  " VALUE: " << root->value.second << std::endl;
				print_tabulation(level);
				std::cout << "LEFT" << std::endl;
				print_tree_rec(root->left, level + 1);
				print_tabulation(level);
				std::cout << "RIGHT" << std::endl;
				print_tree_rec(root->right, level + 1);
				print_tabulation(level);
				std::cout << "END" << std::endl;
			}

		// void construct(pointer ptr, const Type& val);
		// new ((void *) ptr) Type(val)

			//node(node * nil, const T * value) : parent(nil), left(nil), right(nil), value(value) {};
			//  ‘const ft::pair<const int, int>’}
			//	‘const ft::pair<const int, int>*’

			link_type create_node(const value_type & value)
			{
				link_type new_node = this->_alloc.allocate(1);
				_alloc.construct(new_node, node<value_type>(this->_nil, value)); // Ne fonctionne pas
				return (new_node);
			}

		/* 	void delete_node( link_type node )
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
				if (insert_place == this->_nil) // 
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
			} */
	};
}

#endif

// nodes (parent, left, right, value)

// tree mon_arbre(); -> _current -> NULL
// mon_arbre.add_value(42); -> if (_current == NULL)
									// node
// mon_arbre.add_value(56); current -> right 52
