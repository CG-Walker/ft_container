#include <map>
#include "Map.hpp"
#include <string>
#include "Utils.hpp"
#include <iostream>


int main()
{
	std::map<int, int> std_map;
	ft::map<int, int> ft_map;

	ft_map.insert(ft::pair<int, int>(1, 1));
	//ft_map.insert(ft::pair<int, int>(1, 42));
	ft_map.insert(ft::pair<int, int>(3, 3));
    ft_map.insert(ft::pair<int, int>(5, 5));
    ft_map.insert(ft::pair<int, int>(4, 4));

    ft_map.print_tree();
	//ft::map<int, int>::iterator it = ft_map.find(5);
	//std::cout << it.base()->value.second << std::endl;
	return(0);
}


