#ifndef ITERATORTRAIT_HPP
# define ITERATORTRAIT_HPP
# include "Utils.hpp"

namespace ft
{
	template <class Iter>
	struct iterator_traits
	{
        typedef typename Iter::difference_type difference_type;
		typedef typename Iter::value_type value_type;
		typedef typename Iter::pointer pointer;
		typedef typename Iter::reference reference;
		typedef typename Iter::iterator_category iterator_category;
	};

	template <class T>
	struct iterator_traits<T *>
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T * pointer;
		typedef T & reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template <class T>
	struct iterator_traits<const T *>
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef const T * pointer;
		typedef const T & reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

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


	template<class Tp, Tp v>
	struct integral_constant
	{
		enum									{ value = v };
		typedef Tp								value_type;
		typedef integral_constant<Tp, v>		type;
		operator value_type() const
		{
			return value;
		}
		value_type operator()()
		{
			return value;
		}
	};

	//So true_type is an integral_constant where type is bool and value is true.
	typedef integral_constant<bool, true>		true_type;
	typedef integral_constant<bool, false>		false_type;

	template<class Tp>
	struct _is_integral_helper : public false_type
	{
	};
	template<>
	struct _is_integral_helper<bool> : public true_type
	{
	};
	template<>
	struct _is_integral_helper<char> : public true_type
	{
	};
	template<>
	struct _is_integral_helper<signed char> : public true_type
	{
	};
	template<>
	struct _is_integral_helper<unsigned char> : public true_type
	{
	};
	template<>
	struct _is_integral_helper<wchar_t> : public true_type
	{
	};
	template<>
	struct _is_integral_helper<short> : public true_type
	{
	};
	template<>
	struct _is_integral_helper<unsigned short> : public true_type
	{
	};
	template<>
	struct _is_integral_helper<int> : public true_type
	{
	};
	template<>
	struct _is_integral_helper<unsigned int> : public true_type
	{
	};
	template<>
	struct _is_integral_helper<long> : public true_type
	{
	};
	template<>
	struct _is_integral_helper<unsigned long> : public true_type
	{
	};
	template<>
	struct _is_integral_helper<long long> : public true_type
	{
	};
	template<>
	struct _is_integral_helper<unsigned long long> : public true_type
	{
	};

	// is_integral class inherits from the false or true type, wich is an integral constant
	template<class Tp>
	struct is_integral : public _is_integral_helper<typename remove_cv<Tp>::type>::type
	{
	};
} // namespace ft

#endif