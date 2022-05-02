#include <map>
#include <string>
#include <iostream>

#include "../Includes/Containers/Map.hpp"

// TEST DES FONCTIONS ITERATORS
void	tests_iterators()
{
	std::cout << "TESTS DES FONCTIONS ITERATORS\n";

	ft::map<int, int> map_iterators;
	ft::map<int, int>::iterator it;
	ft::map<int, int>::reverse_iterator r_it;
    std::map<int, int> std_map;
    std::map<int, int>::iterator std_it;

    std::map<int, int>::reverse_iterator stdr_it;

	map_iterators.insert(ft::pair<int, int>(10, 1));
	map_iterators.insert(ft::pair<int, int>(9, 1));
	map_iterators.insert(ft::pair<int, int>(8, 1));
    map_iterators.insert(ft::pair<int, int>(7, 1));

	map_iterators.print_tree("map_iterators");

	it = map_iterators.begin();
	std::cout << "\nbegin() : " << it->first << std::endl;
	it = map_iterators.end();
	std::cout << "end() : " << it->first << std::endl;

    std_map.insert(std::pair<int, int>(10, 1));
    std_map.insert(std::pair<int, int>(9, 1));
    std_map.insert(std::pair<int, int>(8, 1));
    std_map.insert(std::pair<int, int>(7, 1));
    std_map.insert(std::pair<int, int>(11, 1));
    std_it = std_map.begin();
    std::cout << "\nstd_it begin() : " << std_it->first << std::endl;
    std_it = std_map.end();
    std::cout << "std_it end() : " << std_it->first << std::endl;
    
    stdr_it = std_map.rbegin();
    std::cout << "stdr rbegin() : " << stdr_it->first << std::endl;

	r_it = map_iterators.rbegin();
	std::cout << "rbegin() : " << r_it->first << std::endl;
	r_it = map_iterators.rend();
	std::cout << "rend() : " << r_it->first << std::endl;

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

	map_modifiers.print_tree("map_modifiers");

	std::cout << "erase()...\n";
	map_modifiers.erase(map_modifiers.begin());
	map_modifiers.erase(10);
    //map_modifiers.erase(map_modifiers.begin(), map_modifiers.end());
    map_modifiers.erase(9);

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
	ft::pair<ft::map<int, int>::iterator, ft::map<int, int>::iterator> map_pair;

	map_element_access.insert(ft::pair<int, int>(10, 1));
	map_element_access.insert(ft::pair<int, int>(9, 1));
	map_element_access.insert(ft::pair<int, int>(8, 1));
	
	// Ne fonctionne pas
	std::cout << "count(5) : " << map_element_access.count(8) << std::endl;
	std::cout << "count(5) : " << map_element_access.count(5) << std::endl;

	it = map_element_access.find(8);
	std::cout << "find(8) : " << it->first << std::endl;
	it = map_element_access.find(42);
	std::cout << "find(42) : " << it->first << std::endl;

	// Ne fonctionne pas
	map_pair = map_element_access.equal_range(9);
	std::cout << "equal_range(9) : " << (map_pair.first)->first << std::endl;

	// Ne fonctionne pas
	it = map_element_access.lower_bound(8);
	std::cout << "lower_bound(8) : " << it->first << std::endl;
	it = map_element_access.upper_bound(9);
	std::cout << "upper_bound(9) : " << it->first << std::endl;

	std::cout << "\n";
}

void	tests_observers()
{
	ft::map<int, int> map_iterators;
    map_iterators.insert(ft::pair<int, int>(10, 1));
	map_iterators.insert(ft::pair<int, int>(9, 1));
	map_iterators.insert(ft::pair<int, int>(11, 1));
    map_iterators.insert(ft::pair<int, int>(7, 1));

    ft::map<int, int>::value_compare value = map_iterators.value_comp();
	ft::map<int, int>::key_compare key = map_iterators.key_comp();
}

int main()
{
	tests_iterators();
	tests_capacity();
	tests_modifiers();
	tests_element_access();
    tests_observers();
	
	return(0);
}


