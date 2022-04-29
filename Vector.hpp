#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <stdexcept>
# include <limits>
# include <iostream>
# include <iterator>
	
# include "Iterator.hpp"
# include "ReverseIterator.hpp"
# include "Utils.hpp"
# include "IteratorTrait.hpp"

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
			// Member types
			typedef T											value_type;
			typedef Allocator									allocator_type;
			typedef typename allocator_type::size_type			size_type;
			typedef typename allocator_type::difference_type	difference_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef ft::iterator<T>								iterator;
			typedef ft::iterator<const T>						const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

			// Constructors & Destructor
			explicit vector( const Allocator & alloc = allocator_type()) : _alloc(alloc), _first(NULL), _last(NULL), _capacity(0) {};
			explicit vector( size_type count, const T & value = T(), const Allocator & alloc = Allocator()) : _alloc(alloc), _first(NULL), _last(NULL), _capacity(0)
			{
				if (count > 0)
				{
					this->_first = this->_alloc.allocate(count);
					this->_last = _first + count;
					this->_capacity = count;
					std::uninitialized_fill_n(this->_first, count, value);
				}
			}
			template<class InputIt>
			vector( InputIt first, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type last, const Allocator & alloc = Allocator() ) : _alloc(alloc)
			{
				size_type new_size = std::distance(first, last);
				this->_first = this->_alloc.allocate(new_size);
				this->_last = this->_first + new_size;
				this->_capacity = new_size;
				std::uninitialized_copy(first, last, this->_first);
			}
			vector( const vector & other ) : _alloc(other._alloc), _first(NULL), _last(NULL), _capacity(0)
			{
				size_type size = other.size();
				if (size > 0)
				{
					this->_first = this->_alloc.allocate(size);
					this->_last = this->_first + size;
					this->_capacity = other._capacity; // Attention
					std::uninitialized_copy(other._first, other._last, this->_first);
				}
			}
			
			~vector()
			{
				this->clear();
				this->_alloc.deallocate(this->_first, this->_capacity);
			}

			vector					&operator=(const vector &other)
			{
				assign(other._first, other._last);
				//std::cout << "this size: " << this->size() << std::endl;
				//std::cout << "dist : " << std::distance(_first, _last) << std::endl;
				return (*this);
			}

			allocator_type get_allocator() const { return (this->_alloc); };

			void assign( size_type count, const T & value )
			{
				if (count > capacity())
				{
					this->clear();
					this->reserve(count);
		            std::uninitialized_fill_n(this->_first, count, value);
				}
				else
				{
					//this->clear();
					std::fill_n(this->_first, count, value);
				}
				this->_last = this->_first + count;
			}

			template<class InputIt>
			void assign( InputIt first, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type last )
			{
				size_type new_size = std::distance(first, last);
				
				if (new_size > capacity())
				{
					this->clear();
					this->reserve(new_size);
					std::uninitialized_copy(first, last, this->_first);
				}
				else
				{
					//->clear();
					std::copy(first, last, this->_first);
				}
				this->_last = this->_first + new_size;
			}

			// Element access
			reference at( size_type pos ) 
			{
				if (pos >= this->size())
					throw (std::out_of_range("vector::at:"));
				return (this->_first[pos]);
			}

			const_reference at( size_type pos ) const
			{
				if (pos >= this->size())
					throw (std::out_of_range("vector::at:"));
				return (this->_first[pos]);
			}

			reference operator[]( size_type pos ) {	return *(this->_first + pos);	};

			reference front() { return *(this->begin()); };

			const_reference front() const { return *(this->begin()); };

			reference back() { return *(this->end() - 1); };

			const_reference back() const { return *(this->end() - 1); };

			T * data() { return (this->_first); };

			const T * data() const { return (this->_first); };

			// Iterators
			iterator begin() { return iterator(this->_first); };

			const_iterator begin() const { return const_iterator(this->_first); };

			reverse_iterator rbegin() { return reverse_iterator(this->_last); };

			const_reverse_iterator rbegin() const { return const_reverse_iterator(this->_last); };

			iterator end() { return iterator(this->_last); };

			reverse_iterator rend() { return reverse_iterator(this->_first); };

			const_reverse_iterator rend() const { return const_reverse_iterator(this->_first); };

			const_iterator end() const { return const_iterator(this->_last); };

			// Capacity
			bool empty() const { return (this->_first == _last); };

			size_type size() const { return (this->_last - this->_first); };

			size_type max_size() const {
				return (std::min(static_cast<size_type>(std::numeric_limits<difference_type>::max()), this->_alloc.max_size()));
			}

			void reserve( size_type new_cap )
			{
				if (new_cap > this->_capacity)
				{
					pointer new_first;
					new_first = this->_alloc.allocate(new_cap);
					size_type old_size = this->size();
					std::uninitialized_copy(this->_first, this->_last, new_first);
					this->clear();
					this->_alloc.deallocate(this->_first, this->_capacity);
					this->_first = new_first;
					this->_last = this->_first + old_size;
					this->_capacity = new_cap;
				}
			}

			size_type capacity() const { return (this->_capacity); };

			// Modifiers
			void clear()
			{
				pointer now = this->_last;
				while (now != this->_first)
				{
					this->_alloc.destroy(--now);
				}
				this->_last = this->_first;
			}

			iterator insert( iterator pos, const value_type & value ) // Insert value before pos
			{
				size_type offset = pos - this->begin();
				insert(pos, 1, value);
				return (this->begin() + offset);
			}

			void insert( iterator pos, size_type count, const value_type & value ) // Insert count value before pos
			{
				size_type new_size = this->size() + count;
				size_type offset = pos - begin();
				
				if (new_size > this->_capacity) // Si le nombre d'élements à ajouter font passer la size au delà de la capacity
				{
					size_type old_capacity = this->_capacity;
					size_type old_size = this->size();
									
					new_size = calc_new_capacity(new_size);
					//std::cout << "1 new_size : " << new_size << std::endl;
					pointer new_first = this->_alloc.allocate(new_size);

					std::uninitialized_copy(this->begin(), pos, new_first); // Copie les nombres de begin à pos dans le nouvel espace mémoire réservé
					std::uninitialized_fill_n(new_first + offset, count, value); // Remplit cet espace mémoire avec count x value
					std::uninitialized_copy(pos, this->end(), new_first + offset + count); // Copie les anciens élements

					clear(); // On destroy l'ancienne mémoire
					this->_alloc.deallocate(this->_first, old_capacity);
					this->_first = new_first;
					this->_last = this->_first + old_size + count;
					//std::cout << "2 new_size : " << new_size << std::endl;
					this->_capacity = new_size;
					//std::cout << "capacity : " << this->_capacity << std::endl;
				}
				else // Si la capacity est suffisante pour ajouter les nouveaux élements
				{
					size_type old_size = this->size();
					new_size = old_size + count;

					for (size_type i = 0; i < old_size - offset; i++)
					{
						if (new_size - i > old_size)
							this->_alloc.construct(&this->_first[new_size - i - 1], this->_first[old_size - i - 1]);
						else
							this->_first[new_size - i - 1] = this->_first[old_size - i - 1];
					}
					for (size_type i = 0; i < count; i++)
					{
						if (offset + i >= size())
							this->_alloc.construct(&this->_first[offset + i], value);
						else
							this->_first[offset + i] = value;
					}
					this->_last += count;
				}
			}

			template <class InputIterator>
        	void insert( iterator position, InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last )
        	{
				size_type count = std::distance(first, last);
				size_type new_size = this->size() + count;
				size_type offset = position - begin();
				
				if (new_size > this->_capacity) // Si le nombre d'élements à ajouter font passer la size au delà de la capacity
				{
					size_type old_capacity = this->_capacity;
					size_type old_size = this->size();

					new_size = calc_new_capacity(new_size);
					pointer new_first = this->_alloc.allocate(new_size);

					std::uninitialized_copy(this->begin(), position, new_first); // Copie les nombres de begin à pos dans le nouvel espace mémoire réservé
					std::uninitialized_copy(first, last, new_first + offset); // Remplit cet espace mémoire avec count x value
					std::uninitialized_copy(position, this->end(), new_first + offset + count); // Copie les anciens élements

					clear(); // On destroy l'ancienne mémoire
					this->_alloc.deallocate(this->_first, old_capacity);
					this->_first = new_first;
					this->_last = this->_first + old_size + count;
					this->_capacity = new_size;
				}
				else // Si la capacity est suffisante pour ajouter les nouveaux élements
				{
					size_type old_size = this->size();
					new_size = old_size + count;

					for (size_type i = 0; i < old_size - offset; i++)
					{
						if (new_size - i > old_size)
							this->_alloc.construct(&this->_first[new_size - i - 1], this->_first[old_size - i - 1]);
						else
							this->_first[new_size - i - 1] = this->_first[old_size - i - 1];
					}
					for (size_type i = 0; i < count; i++)
					{
						if (offset + i >= size())
							this->_alloc.construct(&this->_first[offset + i], *first);
						else
							this->_first[offset + i] = *first;
						++first;
					}
					this->_last += count;
				}
			}

			iterator erase( iterator pos ) { return this->erase(pos, pos + 1); };

			iterator erase( iterator first, iterator last )
			{
				difference_type offset = std::distance(first, last);
				for (iterator it = first; it + offset != this->end(); ++it)
					*it = *(it + offset);
				pointer now = this->_last;
				while (now != (this->_last - offset))
					this->_alloc.destroy(--now);
				this->_last = this->_last - offset;
				return (first);
			}

			void push_back( const value_type & value )
			{
				size_type new_size = this->size() + 1;
				if (new_size > this->_capacity)
					this->reserve(calc_new_capacity(new_size));
				this->_alloc.construct(this->_last, value);
				this->_last++;
			}

			void pop_back()
			{
				this->_alloc.destroy((this->_last - 1));
				this->_last--;
			}

			void resize( size_type count, value_type value = value_type() )
			{
				if (count < size()) // Si la nouvelle size est plus petite que celle actuelle
				{
					this->erase(this->begin() + count, this->end());
				}
				else if (count > this->size()) // Si la nouvelle size est plus grande que celle actuelle
				{
					insert(this->end(), count - this->size(), value);
				}
			}

			void swap( vector & other )
			{
				pointer buffer_first = other._first;
				pointer buffer_last = other._last;
				size_type buffer_capacity = other._capacity;

				other._first = this->_first;
				other._last = this->_last;
				other._capacity = this->_capacity;

				this->_first = buffer_first;
				this->_last = buffer_last;
				this->_capacity = buffer_capacity;
			}

		private:
			allocator_type	_alloc;
			pointer			_first;
			pointer			_last;
			size_type		_capacity;

		// Private member functions

		size_type calc_new_capacity(size_type new_cap)
        {
			size_type max_cap = max_size();
			if (new_cap > max_cap)
				throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
			size_type cap = this->_capacity;
			if (cap >= max_cap / 2)
				return max_cap;
			//std::cout << "cap * 2 : " << cap * 2 << " | new_cap : " << new_cap << std::endl;
			//std::cout << "max : " << std::max((cap * 2), new_cap) <<  std::endl;
			return std::max((cap * 2), new_cap);
       	}
	}; // class Vector

	// Non-member functions
	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
	{
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
    bool operator!=(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
    {
        return !(lhs == rhs);
    }

	template <class T, class Alloc>
    bool operator<(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
    {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }

	template <class T, class Alloc>
    bool operator<=(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
    {
        return !(rhs < lhs);
    }

    template <class T, class Alloc>
    bool operator>(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
    {
        return (rhs < lhs);
    }

    template <class T, class Alloc>
    bool operator>=(const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs)
    {
        return !(lhs < rhs);
    }
	template< class T, class Alloc >
	void swap( ft::vector<T,Alloc> & lhs, ft::vector<T,Alloc> & rhs )
	{
		lhs.swap(rhs);
	}
} // namespace ft

 #endif