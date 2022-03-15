#include "Vector.hpp"
#include <iostream>
#include <vector>

int main()
{
	std::vector<int>		std_vec;
	ft::vector<int>		ft_vec;
	ft::iterator<int>	   ft_it;

	//ft_vec.reserve(20);

	ft_vec.push_back(42);
	ft_vec.push_back(45);
	ft_vec.push_back(487);
	ft_vec.push_back(21);

	std_vec.push_back(42);

	for (ft::iterator<int> it = ft_vec.begin(); it != ft_vec.end(); it++)
	{
		std::cout << "first : " << *it << std::endl;
	}
}