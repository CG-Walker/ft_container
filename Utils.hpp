#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft
{
    template<class Input1, class Input2>
    bool lexicographical_compare(Input1 first1, Input1 last1, Input2 first2, Input2 last2)
    {
        for(; (first1 != last1) && (first2 != last2); ++first1, ++first2)
        {
            if (*first1 < *first2)
            {
                return true;
            }
            if (*first1 > *first2)
            {
                return false;
            }
        }
         return (first1 == last1) && (first2 != last2);
    }
    template<class Input1, class Input2>
    bool equal(Input1 first1, Input1 last1, Input2 first2)
    {
        for (; first1 != last1; ++first1, ++first2)
        {
            if (*first1 != *first2)
            {
                return false;
            }
        }
        return true;
    }
}

#endif