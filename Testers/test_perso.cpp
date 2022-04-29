#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include "Vector.hpp"
#include <iostream>

int main()
{
	ft::vector<int>		test1;

    test1.push_back(3);
	test1.push_back(2);
	test1.push_back(1);
	test1.push_back(0);

    std::cout << "begin() with const_iterator" << std::endl;
	for( ft::vector<int>::const_iterator it3 = test1.begin() ; it3 != test1.end() ; ++it3 )
		{ std::cout << *it3 << std::endl; }
}