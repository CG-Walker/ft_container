#ifndef TREE_HPP
# define TREE_HPP

# include <memory>
# include <limits>
# include <iostream>
# include <cmath>

# include "../Iterators/MapIterator.hpp"
# include "../Utils/Utils.hpp"

namespace ft
{
	template <class Key, class T, class Compare, class Allocator = std::allocator<T> >
	class tree
	{
		public:
			// Member types
 			typedef ft::tree_iterator<T *>										iterator;
			typedef ft::tree_iterator<const T *>								const_iterator;
			typedef ft::reverse_iterator<T>										reverse_iterator;
			typedef ft::reverse_iterator<const T>								const_reverse_iterator;

		private:
			// Member types
			typedef Key															key_type;
			typedef T															value_type;	// T = value_type de map = ft::pair<const Key, T>
			typedef Compare														key_compare;
			typedef ft::node<T> *												link_type;
			typedef const ft::node<T> *											const_link_type;
			typedef typename Allocator::size_type 								size_type;
			typedef typename Allocator::template rebind<node<T> >::other		node_allocator_type;
			typedef typename node_allocator_type::difference_type 				difference_type;

		public:
			class value_compare : std::binary_function<value_type, value_type, bool>
			{
			//class tree;
			public:
				key_compare	comp;
				value_compare(Compare c) : comp(c) {}

				typedef bool 		result_type;
				typedef value_type	first_argument_type;
				typedef value_type	second_argument_type;

				bool operator()(const value_type & lhs, const value_type & rhs) const { return (comp(lhs.first, rhs.first)); }
				bool operator()(const Key & lhs, const value_type & rhs) const { return (comp(lhs, rhs.first)); }
				bool operator()(const value_type & lhs, const Key & rhs) const { return (comp(lhs.first, rhs)); }
			};


			// Constructors & Destructor
			tree(const key_compare & compare = key_compare(), const Allocator & allocator = Allocator())  : _current(NULL), _compare(compare), _size(0), _alloc(node_allocator_type(allocator)) { initialize(); };
			tree(const tree & tree) : _current(NULL), _compare(tree._compare), _size(0), _alloc(tree._alloc)
			{
                initialize();
				iterator it = tree.end();
				link_type root_to_copy = it.base()->left;
				copy_tree(root_to_copy, tree.get_nil());
			}
			~tree()	{};

			tree & operator=( const tree & other )
			{
				if (this != &other)
				{
					clear();
					_compare = other._compare;
					for (iterator i = other.begin(); i != other.end(); ++i)
						insert(*i);
				}
				return(*this);
			}

			Allocator get_allocator() const { return (this->_alloc); };
	
			// Iterators
			iterator begin() { 
				std::cout << "IN BEGIN\n";
				return (iterator(this->_begin, this->_nil)); }
			const_iterator begin() const { return const_iterator(this->_begin, this->_nil); }
			iterator end() { 
				std::cout << "IN REND\n";
				return iterator(this->_end, this->_nil); }
			const_iterator end() const { return const_iterator(this->_end, this->_nil); };

			// Capacity
			size_type size() const { return (this->_size); };
			size_type max_size() const
			{
				return (std::min(static_cast<size_type>(std::numeric_limits<difference_type>::max()), _alloc.max_size()));
			}

			// Modifiers
			void clear()
			{
				if (this->_size != 0)
				{
					this->delete_branch(this->_current);
					this->_size = 0;
					this->_begin = this->_end;
					this->_current = NULL;
				}
			}

			ft::pair<iterator, bool> insert(const value_type & value)
			{
				link_type root = this->_current;
				link_type new_node = create_node(value);
				bool is_nil = false;

				if (this->_current == NULL) // Signifie que l'arbe est vide
				{
					this->_current = new_node;
					this->_current->left->parent = this->_current;
					this->_current->right->parent = this->_current;
					this->_size += 1;
					this->_begin = new_node;
					this->_current->parent = this->_end;
					this->_end->left = this->_current; // Left de end pointe toujours sur root
					return (ft::make_pair(iterator(new_node, this->_nil), true));
				}
				if (this->find(value.first) != this->end())	// Signifie que la clé existe déjà
					return (ft::make_pair(iterator(new_node, this->_nil), false));
				while (true) // Ajout du nouveau node au bon endroit dans l'arbre
				{
					if (is_nil)
					{	
						new_node->parent = this->_current;
						if (this->_compare(new_node->value, this->_begin->value))
							this->_begin = new_node;
						if (this->_compare(value, this->_current->value))
							this->_current->left = new_node;
						else
							this->_current->right = new_node;
						new_node->left->parent = new_node;
						new_node->right->parent = new_node;
						this->_size += 1;
						break ;
					}
					else if (this->_compare(value, this->_current->value))
					{
						if (this->_current->left == this->_nil)
							is_nil = true;
						else
							this->_current = this->_current->left;
					}
					else
					{
						if (this->_current->right == this->_nil)
							is_nil = true;
						else
						this->_current = this->_current->right;
					}
				}
				this->_current = root;
				return (ft::make_pair(iterator(new_node, this->_nil), true));
			}

			iterator insert( iterator hint, const value_type & value )
			{
				link_type root = this->_current;
				link_type new_node = create_node(value);
				bool is_nil = false;

				if (hint == begin() && this->_current == NULL) // Signifie que l'arbe est vide
				{
					this->_current = new_node;
					this->_current->left->parent = this->_current;
					this->_current->right->parent = this->_current;
					this->_size += 1;
					this->_begin = new_node;
					this->_current->parent = this->_end;
					this->_end->left = this->_current; // Left de end pointe toujours sur root
					return (ft::make_pair(iterator(new_node, this->_nil), true).first);
				}
				if (this->find(value.first) != this->end())	// Signifie que la clé existe déjà
				{
					//delete_node(new_node);
					return (ft::make_pair(iterator(new_node, this->_nil), false).first);
				}
				while (true) // Ajout du nouveau node au bon endroit dans l'arbre
				{
					if (is_nil)
					{	
						new_node->parent = this->_current;
						if (this->_compare(new_node->value, this->_begin->value))
							this->_begin = new_node;
						if (this->_compare(value, this->_current->value))
							this->_current->left = new_node;
						else
							this->_current->right = new_node;
						new_node->left->parent = new_node;
						new_node->right->parent = new_node;
						this->_size += 1;
						break ;
					}
					else if (this->_compare(value, this->_current->value))
					{
						if (this->_current->left == this->_nil)
							is_nil = true;
						else
							this->_current = this->_current->left;
					}
					else
					{
						if (this->_current->right == this->_nil)
							is_nil = true;
						else
						this->_current = this->_current->right;
					}
				}
				this->_current = root;
				return (ft::make_pair(iterator(new_node, this->_nil), true).first);
			}

			template <class InputIt>
			void insert( InputIt first, InputIt last )
			{
				for (InputIt it = first ; it != last ; it++)
					insert(*it);
			}

			void erase( iterator pos )
			{
				link_type root = this->_current;
				link_type node;

				if (pos == end())
					return ;

				node = pos.base();
				// Réorganisation de l'arbre
				if (node->left == _nil && node->right == _nil)
				{
                    if (node != root)
					    replace_parent_node(node, _nil);
                    else
                        node->parent->left = _nil;
				}
				else if (node->left != _nil && node->right == _nil)
				{
                    if (node != root)
					    replace_parent_node(node, node->left);
                    else
                        node->parent->left = node->left;
					node->left->parent = node->parent;
					
				}
				else if (node->left == _nil && node->right != _nil)
				{
                    if (node != root)
					    replace_parent_node(node, node->right);
                    else
                        node->parent->left = node->right;
					node->right->parent = node->parent;
				}
				else
				{
                    if (node != root)
					    replace_parent_node(node, node->right);
                    else
                        node->parent->left = node->right;
					node->left->parent = node->right;
					node->right->left = node->left;
					node->right->parent = node->parent;
					
				}
				// Si le node à supprimer est le root
                if (node == root)
                {
                    if(node->right != _nil)
                        _current = node->right;
                    else
                        _current = node->left;
                }
                if (node)
                {
                    delete_node(node);
                    _size--;
                    if (_size == 0) // L'arbre est désormais vide
                        _current = NULL;
                }
			}

			void erase( iterator first, iterator last )
			{
				while (first != last)
					erase(first++);
			}

			size_type erase( const Key & key )
			{
				iterator ite = find(key);
				if (ite == end())
					return(0);
				erase(ite);
				return(1);
			}

			void swap( tree & other )
			{
				swappy(this->_current, other._current);
				swappy(_nil, other._nil);
				swappy(_begin, other._begin);
				swappy(_end, other._end);
				//swappy(_compare, other._compare);
				swappy(_alloc, other._alloc);
				swappy(_size, other._size);
			}

			// Element access
			iterator find(const key_type & key)
			{
				link_type root = this->_current;
				link_type current = this->_current;
				bool is_nil = false;

				while (true)
				{
					if (is_nil)
						break ;
					if (current->value.first == key)
					{
						link_type tmp = current;
						current = root;
						return (iterator(tmp, this->_nil));
					}
					else if (this->_compare(key, current->value))
					{
						if (current->left == this->_nil)
							is_nil = true;
						else
							current = current->left;
					}
					else
					{
						if (current->right == this->_nil)
							is_nil = true;
						else
						current = current->right;
					}
				}
				return (this->end());
			}

			const_iterator find(const key_type & key) const
			{
				link_type root = this->_current;
				link_type current = this->_current;
				bool is_nil = false;

				while (true)
				{
					if (is_nil)
						break ;
					if (current->value.first == key)
					{
						link_type tmp = current;
						current = root;
						return (const_iterator(tmp, this->_nil));
					}
					else if (this->_compare(key, current->value))
					{
						if (current->left == this->_nil)
							is_nil = true;
						else
							current = current->left;
					}
					else
					{
						if (current->right == this->_nil)
							is_nil = true;
						else
						current = current->right;
					}
				}
				return (this->end());
			}

			ft::pair<iterator,iterator> equal_range( const Key & key )
			{
				return (make_pair(lower_bound(key), upper_bound(key)));
			}

			iterator lower_bound( const Key & key )
			{
				iterator it = this->begin();
				while (this->_compare(*it, key) && it != this->end())
					it++;
				return (it);
			}

			iterator upper_bound( const Key & key )
			{
				iterator it = this->begin();
				while (this->_compare(*it, key) && it != this->end())
					it++;
				if (it->first == key)
					it++;
				return (it);
			}

			link_type get_nil() const { return (this->_nil); };
	
			// DEBUG
			void	print_tree(std::string name)
			{
				std::cout << "\n--- " << name << " ---" << std::endl;
				printBT("", this->_current, false);
			}

		private:
			link_type			_current;
			link_type			_nil;
			link_type			_begin;
			link_type			_end;
			value_compare		_compare;
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
				this->_begin = this->_end;
			}
			template<class SW>
			void swappy(SW & first, SW & second)
			{
				SW	tmp;
				tmp = first;
				first = second;
				second = tmp;
			}
            void copy_tree(const link_type node_to_copy, const link_type nil)
			{
                insert(node_to_copy->value);
				if (node_to_copy->left != nil)	
					copy_tree(node_to_copy->left, nil);
				if (node_to_copy->right != nil)
					copy_tree(node_to_copy->right, nil);
			}
            
			void	print_tabulation(int indentation)
			{
				for(int i = 0; i < indentation; i++)
				{
					std::cout << "\t";
				}
			}

			void printBT(const std::string & prefix, const link_type node, bool isLeft)
			{
				if ( node != NULL )
				{
					std::cout << prefix;

					std::cout << (isLeft ? "├──" : "└──" );

					// print the value of the node
					std::cout << "(" << node->value.first << ", " << node->value.second << ")" << std::endl;

					// enter the next tree level - left and right branch
					if (node->left != this->_nil)
						printBT( prefix + (isLeft ? "│   " : "    "), node->left, true);
					if (node->right != this->_nil)
						printBT( prefix + (isLeft ? "│   " : "    "), node->right, false);
				}
			}

			link_type create_node(const value_type & value)
			{
				link_type new_node = this->_alloc.allocate(1);
				_alloc.construct(new_node, node<value_type>(this->_nil, value));
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
    
} // namespace ft

#endif
