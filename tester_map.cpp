#include <map>
#include "Map.hpp"
#include <string>
#include "Utils.hpp"

int main()
{
    std::map<int, int> std_map;
    ft::map<int, int> ft_map;

    ft_map.insert(ft::make_pair(1, 42));
    return(0);
}