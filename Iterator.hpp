#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <cstddef>

namespace ft
{
    template <typename T>
	class Iterator
    {
        public:
            typedef std::random_access_iterator_tag iterator_category;
            typedef T                               value_type;
            typedef T*                              pointer;
            typedef T&                              reference;
            typedef std::ptrdiff_t                  difference_type;

            // constructor and destructor
            Iterator(void) : _ptr(NULL) {};
            Iterator(const Iterator & other) {};
            ~Iterator(void) {};

        private:
            pointer _ptr;
            //Iterator(pointer elem) : _ptr(elem);  
    };
}

#endif