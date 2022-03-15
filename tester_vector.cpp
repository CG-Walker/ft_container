#include "Vector.hpp"
#include <iostream>
#include <vector>

int main()
{
	ft::vector<int>		ft_vec;
	ft::vector<int>		ft_vec2(5, 42);
	ft::iterator<int>	   ft_it;

	//ft_vec.reserve(20);

	ft_vec.push_back(42);
	ft_vec.push_back(45);
	ft_vec.push_back(487);
	ft_vec.push_back(21);

	//ft::vector<int> ft_vec3(ft_vec2);

	ft_vec.swap(ft_vec2);
	for (ft::iterator<int> it = ft_vec.begin(); it != ft_vec.end(); it++)
	{
		std::cout << "ft_vec : " << *it << std::endl;
	}
/* 	for (ft::iterator<int> it = ft_vec3.begin(); it != ft_vec3.end(); it++)
	{
		std::cout << "ft_vec3 : " << *it << std::endl;
	} */
}