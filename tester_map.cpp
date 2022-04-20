#include <map>
#include "Map.hpp"
#include <string>
#include "Utils.hpp"
#include <iostream>


int main()
{
	std::map<int, int> std_map;
	ft::map<int, int> ft_map;
	ft::map<int, int> map_to_swap;

	ft_map.insert(ft::pair<int, int>(10, 1));
	ft_map.insert(ft::pair<int, int>(9, 1));
	ft_map.insert(ft::pair<int, int>(8, 1));
	ft_map.insert(ft::pair<int, int>(1, 42));
	ft_map.insert(ft::pair<int, int>(11, 3));
	ft_map.insert(ft::pair<int, int>(12, 5));
	ft_map.insert(ft::pair<int, int>(13, 4));

	map_to_swap.insert(ft::pair<int, int>(15, 6));
	map_to_swap.insert(ft::pair<int, int>(51, 2));
	map_to_swap.insert(ft::pair<int, int>(16, 42));

/* 	ft::map<int, int>::iterator it_b = ft_map.begin();
	ft::map<int, int>::iterator it_e = ft_map.end();

	while (it_b != it_e)
	{
		std::cout << it_b.base()->value.first << "\n";
		it_b++;
	} */

	//ft::map<int, int> cpy_map(ft_map);
	
	//ft_map.print_tree();
	//cpy_map.print_tree();

//	ft::map<int, int> cpy_map(ft_map);
	
	ft_map.print_tree();
	map_to_swap.print_tree();

	ft_map.swap(map_to_swap);

	ft_map.print_tree();
	map_to_swap.print_tree();
	/* ft::map<int, int>::iterator it = ft_map.lower_bound(0);
	std::cout << "iterator : " << it.base()->value.first << "\n"; */
	/* std::cout << "size before : " << ft_map.size();
	ft_map.clear();
	std::cout << "\nsize after : " << ft_map.size();
	std::cout << "-\n"; */
	/* ft_map.insert(ft::pair<int, int>(6, 63));
	ft_map.insert(ft::pair<int, int>(45, 456));
	ft_map.insert(ft::pair<int, int>(26, 261)); */
	//ft_map.print_tree();
	//ft::map<int, int>::iterator it = ft_map.find(5);
	//std::cout << it.base()->value.second << std::endl;
	return(0);
}


