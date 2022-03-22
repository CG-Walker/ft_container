#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft
{
	template <class Input1, class Input2>
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
	template <class Input1, class Input2>
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

	template <class T1, class T2>
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		first_type  first;
		second_type	second;
		pair() : first(), second() {};

		template <class U, class V>
       	pair(const pair<U, V> &pr) : first(pr.first), second(pr.second) {};

		pair(const first_type &a, const second_type &b) : first(a), second(b) {};

		pair &operator=(const pair &pr)
       	{
        	first = pr.first;
    		second = pr.second;
            return *this;
        }
	};

	template <class T1, class T2>
    pair<T1, T2> make_pair(T1 x, T2 y)
    {
        return (pair<T1, T2>(x, y));
    }

	template <class T1, class T2>
    bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }
	template <class T1, class T2>
    bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return !(lhs == rhs);
    }
    template <class T1, class T2>
    bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return lhs.first < rhs.first ||
               (!(rhs.first < lhs.first) && lhs.second < rhs.second);
    }
    template <class T1, class T2>
    bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return !(rhs < lhs);
    }
    template <class T1, class T2>
    bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return rhs < lhs;
    }
    template <class T1, class T2>
    bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
    {
        return !(lhs < rhs);
    }
	
	// Simple copie non-comprise pour l'instant !!
	template <class T>
	struct remove_cv
	{
		typedef T type;
	};

	template <class T>
	struct remove_cv<const T>
	{
		typedef T type;
	};

	template <class T>
	struct remove_cv<volatile T>
	{
		typedef T type;
	};

	template <class T>
	struct remove_cv<const volatile T>
	{
		typedef T type;
	};
	// -------------------------------------------------

	template <bool B, class T = void>
	struct enable_if {};

	template <class T>
	struct enable_if<true, T> { typedef T type; };

	template <class T, T v>
	struct integral_constant
	{
		enum {value = v};
		typedef T value_type;
		typedef integral_constant<T, v> type;
		operator value_type() const { return (value); }
	};

	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;

	template <class T>
	struct is_integral_helper : public false_type {};
	template <>
	struct is_integral_helper<bool> : public true_type {};
	template <>
	struct is_integral_helper<char> : public true_type {};
	template <>
	struct is_integral_helper<signed char> : public true_type {};
	template <>
	struct is_integral_helper<unsigned char> : public true_type {};
	template <>
	struct is_integral_helper<wchar_t> : public true_type {};
	template <>
	struct is_integral_helper<short> : public true_type {};
	template <>
	struct is_integral_helper<unsigned short> : public true_type {};
	template <>
	struct is_integral_helper<int> : public true_type {};
	template <>
	struct is_integral_helper<unsigned int> : public true_type {};
	template <>
	struct is_integral_helper<long> : public true_type {};
	template <>
	struct is_integral_helper<unsigned long> : public true_type {};

	template <class T>
	struct is_integral : public is_integral_helper<typename remove_cv<T>::type> {}; // Pas encore bien pigé
} //namespace ft

#endif