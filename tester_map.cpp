#include <map>
#include "Map.hpp"
#include <string>
#include "Utils.hpp"
#include <iostream>


int main()
{
	ft::map<int, int> ft_map;
	ft::map<char, int> ft_map_char;
	ft_map.insert(ft::pair<int, int>(10, 1));
	ft_map.insert(ft::pair<int, int>(9, 1));
	ft_map.insert(ft::pair<int, int>(8, 1));
	ft_map.insert(ft::pair<int, int>(11, 1));
	ft_map.print_tree("ft_map");

	ft_map_char.insert(ft::pair<char, int>('Q', 8));
	ft_map_char.insert(ft::pair<char, int>('A', 3));
	ft_map_char.insert(ft::pair<char, int>('z', 1));
	ft_map_char.print_tree("ft_map_char");

	ft::map<int, int> ft_cpy(ft_map);
	ft_cpy.print_tree("ft_cpy");

	ft::map<int, int>::iterator it_first = ft_map.begin();
	ft::map<int, int>::iterator it_last = ft_map.end();
	ft::map<int, int> map_to_insert(it_first, it_last);

	map_to_insert.print_tree("map_to_insert");
	ft::map<int, int> ft_empty;
	if(ft_empty.empty())
		std::cout << "\nft_empty is empty" << std::endl;
	if(!ft_map.empty())
	std::cout << "ft_map is not empty" << std::endl;

/* 	ft::map<int, int>::iterator it_b = ft_map.begin();
	ft::map<int, int>::iterator it_e = ft_map.end();

	while (it_b != it_e)
	{
		std::cout << it_b.base()->value.first << "\n";
		it_b++;
	} 

	//ft::map<int, int> cpy_map(ft_map);
	
	//ft_map.print_tree();
	//cpy_map.print_tree();

//	ft::map<int, int> cpy_map(ft_map);
	
	ft_map.print_tree();
	map_to_swap.print_tree();

	ft_map.swap(map_to_swap);

	
	map_to_swap.print_tree();

	ft_map.at(51);
	
	ft::map<int, int>::iterator it_first = ft_map.begin();
	ft::map<int, int>::iterator it_last = it_first;
	it_last++;
	it_last++;

	ft::map<int, int> map_to_insert(it_first, it_last);

	map_to_insert.print_tree();

	 ft::map<int, int>::iterator it = ft_map.lower_bound(0);
	std::cout << "iterator : " << it.base()->value.first << "\n"; 
	 std::cout << "size before : " << ft_map.size();
	ft_map.clear();
	std::cout << "\nsize after : " << ft_map.size();
	std::cout << "-\n"; 
	 ft_map.insert(ft::pair<int, int>(6, 63));
	ft_map.insert(ft::pair<int, int>(45, 456));
	ft_map.insert(ft::pair<int, int>(26, 261)); */
	//ft_map.print_tree();
	//ft::map<int, int>::iterator it = ft_map.find(5);
	//std::cout << it.base()->value.second << std::endl;
	
	return(0);
}


