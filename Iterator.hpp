#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <cstddef>

namespace ft
{
    template <typename T>
	class iterator
    {
        public:
            typedef std::random_access_iterator_tag iterator_category;
            typedef T                               value_type;
            typedef T*                              pointer;
            typedef T&                              reference;
            typedef std::ptrdiff_t                  difference_type;

            // constructor and destructor
            iterator(void) : _ptr(NULL) {};
            iterator(const iterator & other) {};
            ~iterator(void) {};

        private:
            pointer _ptr;
            //iterator(pointer elem) : _ptr(elem);  
    };
}

#endif