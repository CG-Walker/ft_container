#include <map>
#include "Map.hpp"
#include <string>
#include "Utils.hpp"
#include <iostream>

// TEST DES FONCTIONS ITERATORS
void	tests_iterators()
{
	std::cout << "TESTS DES FONCTIONS ITERATORS\n";

	ft::map<int, int> map_iterators;
	ft::map<int, int>::iterator it;
	ft::map<int, int>::reverse_iterator r_it;

	map_iterators.insert(ft::pair<int, int>(10, 1));
	map_iterators.insert(ft::pair<int, int>(9, 1));
	map_iterators.insert(ft::pair<int, int>(8, 1));

	map_iterators.print_tree("map_iterators");

	it = map_iterators.begin();
	std::cout << "\nbegin() : " << it.base() << std::endl;
	it = map_iterators.end();
	std::cout << "end() : " << it.base() << std::endl;

	// Ne fonctionne pas
	/* r_it = map_iterators.rbegin();
	std::cout << "rbegin() : " << r_it.base() << std::endl;
	r_it = map_iterators.rend();
	std::cout << "rend() : " << r_it.base() << std::endl; */

	std::cout << "\n";
}

void	tests_capacity()
{
	std::cout << "TESTS DES FONCTIONS CAPACITY\n";

	ft::map<int, int> map_capacity;

	std::cout << "empty() Is map_capacity empty ? " << (map_capacity.empty() ? "Yes" : "No") << std::endl;
	map_capacity.insert(ft::pair<int, int>(10, 1));
	std::cout << "empty() Is map_capacity empty ? " << (map_capacity.empty() ? "Yes" : "No") << std::endl;

	std::cout << "size() : " << map_capacity.size() << std::endl;
	std::cout << "max_size() : " << map_capacity.max_size() << std::endl;

	std::cout << "\n";
}

void	tests_modifiers()
{
	std::cout << "TESTS DES FONCTIONS MODIFIERS\n";

	ft::map<int, int> map_modifiers;

	std::cout << "insert()...\n";
	map_modifiers.insert(ft::pair<int, int>(10, 1));
	map_modifiers.insert(ft::pair<int, int>(9, 1));
	map_modifiers.insert(ft::pair<int, int>(8, 1));

	// Tester les deux autres inserts.

	map_modifiers.print_tree("map_modifiers");

	// Ne fonctionne pas
	std::cout << "\nerase()...\n";
	//map_modifiers.erase(map_modifiers.begin());
	//map_modifiers.erase(8);

	map_modifiers.print_tree("map_modifiers");

	ft::map<int, int> map_modifiers_swap;

	map_modifiers.insert(ft::pair<int, int>(66, 1));
	map_modifiers.insert(ft::pair<int, int>(52, 1));
	map_modifiers.insert(ft::pair<int, int>(85, 1));

	map_modifiers_swap.swap(map_modifiers);

	map_modifiers.print_tree("map_modifiers");
	map_modifiers_swap.print_tree("map_modifiers_swap");

	map_modifiers.clear();
	map_modifiers_swap.clear();

	map_modifiers.print_tree("map_modifiers");
	map_modifiers_swap.print_tree("map_modifiers_swap");

	std::cout << "\n";
}

void	tests_element_access()
{
	std::cout << "TESTS DES FONCTIONS ELEMENT_ACCESS\n";

	ft::map<int, int> map_element_access;
	ft::map<int, int>::iterator it;
	ft::pair<ft::map<int, int>::iterator,ft::map<int, int>::iterator> map_pair;

	map_element_access.insert(ft::pair<int, int>(10, 1));
	map_element_access.insert(ft::pair<int, int>(9, 1));
	map_element_access.insert(ft::pair<int, int>(8, 1));
	
	// Ne fonctionne pas
	std::cout << "count(8) : " << map_element_access.count(8) << std::endl;
	//std::cout << "count(5) : " << map_element_access.count(5) << std::endl;

	// Vérifier la valeur de it
	it = map_element_access.find(8);
	std::cout << "find(8) : " << it.base() << std::endl;
	it = map_element_access.find(42);
	std::cout << "find(42) : " << it.base() << std::endl;

	// Ne fonctionne pas
	//map_pair = map_element_access.equal_range(9);
	//std::cout << "equal_range(9) : " << map_pair.first << std::endl;

	// Ne fonctionne pas
	//it = map_element_access.lower_bound(8);
	//std::cout << "lower_bound(8) : " << it.base() << std::endl;
	//it = map_element_access.upper_bound(9);
	//std::cout << "upper_bound(9) : " << it.base() << std::endl;

	std::cout << "\n";
}

void	tests_observers()
{
	// TODO
}


int main()
{
	tests_iterators();
	tests_capacity();
	tests_modifiers();
	tests_element_access();

	/* ft::map<int, int> ft_map;
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
	std::cout << "ft_map is not empty" << std::endl; */

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


