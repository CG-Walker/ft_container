#include "Vector.hpp"
#include <iostream>
#include <vector>

int main()
{
	ft::vector<int>		ft_vec;
	std::vector<int>    std_vec;
	ft::vector<int>		ft_vec2(5, 42);
	ft::iterator<int>	   ft_it;

	ft_vec.push_back(1);
	ft_vec.push_back(2);
	ft_vec.push_back(3);
	ft_vec.push_back(4);

	std_vec.push_back(4);
	std_vec.push_back(5);
	std_vec.push_back(6);
	std_vec.push_back(7);

	std::cout << "ft_vec after push_back" << std::endl;
	for (ft::iterator<int> it = ft_vec.begin(); it != ft_vec.end(); it++)
	{
		std::cout << "ft_vec : " << *it << std::endl;
	}
	std::cout << "ft_vec after push_back but in reverse" << std::endl;
	for (ft::reverse_iterator<int> it = ft_vec.rbegin(); it != ft_vec.rend(); it++)
	{
		std::cout << "ft_vec : " << *it << std::endl;
	}
	ft_vec.swap(ft_vec2);
	std::cout << "ft_vec after swap with ft_vec2" << std::endl;
	for (ft::iterator<int> it = ft_vec.begin(); it != ft_vec.end(); it++)
	{
		std::cout << "ft_vec : " << *it << std::endl;
	}
	ft_vec2.assign(4, 8);
	std::cout << "ft_vec2 after assign(4, 8)" << std::endl;
	for (ft::iterator<int> it = ft_vec2.begin(); it != ft_vec2.end(); it++)
	{
		std::cout << "ft_vec2 : " << *it << std::endl;
	}
	 std::cout << "ft_vec size : " << ft_vec.size() << std::endl;
   std::cout << "ft_vec at 1 :" << ft_vec.at(1) << std::endl;
   std::cout << "empty ft_vec" << std::endl;
   ft_vec.empty();
	for (ft::iterator<int> it = ft_vec.begin(); it != ft_vec.end(); it++)
	{
		std::cout << "ft_vec : " << *it << std::endl;
	}
	ft::vector<int>		ft_vec3;
	ft::vector<int>		ft_vec4;
	ft_vec3.push_back(1);
	ft_vec3.push_back(2);

	ft_vec4.push_back(1);
	if (ft_vec3 == ft_vec3)
		std::cout << "ft_vec == ft_vec" << std::endl;
	if (ft_vec3 != ft_vec4)
		std::cout << "ft_vec != ft_vec2" << std::endl;
	if (ft_vec3 > ft_vec4)
		std::cout << "ft_vec2 > ft_vec" << std::endl;
	if (ft_vec4 < ft_vec3)
		std::cout << "ft_vec < ft_vec2" << std::endl;
	
	return(0);
}