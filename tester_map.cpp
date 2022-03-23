#include <map>
#include "Map.hpp"
#include <string>
#include "Utils.hpp"
#include <iostream>

int main()
{
    std::map<int, int> std_map;
    ft::map<int, int> ft_map;

    ft_map.insert(ft::pair<int, int>(1, 42));
    ft_map.insert(ft::pair<int, int>(1, 42));
    ft_map.insert(ft::pair<int, int>(5, 452));
    ft_map.insert(ft::pair<int, int>(3, 42));
    ft::map<int, int>::iterator it = ft_map.find(1);
    std::cout << it.base()->value.second << std::endl;
    return(0);
}