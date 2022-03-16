#include "Vector.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <iterator>

template <class T>
void SHOW(ft::vector<T> vector, std::string vector_name, std::string msg)
{
	std::cout << msg << std::endl;
	std::cout << vector_name << " : [ ";
	for (ft::iterator<T> it = vector.begin(); it != vector.end(); it++)
		std::cout << *it << ", ";
	std::cout << "]" << std::endl << std::endl;
}

template <class T>
void SHOW(std::vector<T> vector, std::string vector_name, std::string msg)
{
	std::cout << msg << std::endl;
	std::cout << vector_name << " : [ ";
	for (typename std::vector<T>::iterator it = vector.begin(); it != vector.end(); it++)
		std::cout << *it << ", ";
	std::cout << "]" << std::endl;
}

int main()
{
	std::vector<int>		std_vector_1;
	std::vector<int>		std_vector_2(5, 42);

	ft::vector<int>			ft_vector_1;
	ft::vector<int>			ft_vector_2(5, 42);

	for (size_t i = 0; i < 5; i++)
		ft_vector_1.push_back(i);

	for (size_t i = 0; i < 5; i++)
		std_vector_1.push_back(i);

	SHOW(ft_vector_1, "ft_vector_1", "<<< ft_vector_1 after 5 push_back() >>>");
	SHOW(std_vector_1, "std_vector_1", "<<< std_vector_1 after 5 push_back() >>>");

	SHOW(ft_vector_2, "ft_vector_2", "<<< ft_vector_2 >>>");
	std::cout << "<<< swapping ft_vector_1 with ft_vector_2 >>>" << std::endl;
	ft_vector_1.swap(ft_vector_2);
	SHOW(ft_vector_1, "ft_vector_1", "<<< ft_vector_1 after swapping >>>");
	SHOW(ft_vector_2, "ft_vector_2", "<<< ft_vector_2 after swapping >>>");

	std::cout << "ft_vector_2.back() : " << ft_vector_2.back() << std::endl;

	ft_vector_2.assign(4, 8);
	SHOW(ft_vector_2, "ft_vector_2", "<<< ft_vector_2 after assign(4, 8) >>>");

	std::cout << "ft_vector_1 size : " << ft_vector_1.size() << std::endl;
	std::cout << "ft_vector_1 at() 1 :" << ft_vector_1.at(1) << std::endl;
	std::cout << "is ft_vector_1 empty() ?" << ft_vector_1.empty() << std::endl;

	ft::vector<int>		ft_vector_3;
	ft::vector<int>		ft_vector_4;

	for (size_t i = 0; i < 3; i++)
		ft_vector_3.push_back(i);
	ft_vector_4.push_back(1);

	SHOW(ft_vector_3, "ft_vector_3", "<<< ft_vector_3 after 3 push_back() >>>");
	SHOW(ft_vector_4, "ft_vector_4", "<<< ft_vector_4 after 1 push_back() >>>");

	std::cout << "<<< assignation de ft_vector_4 avec ft_vector_3 (ft_vector_4 = ft_vector_3) >>>" << std::endl;
	ft_vector_4 = ft_vector_3;

	SHOW(ft_vector_3, "ft_vector_3", "<<< ft_vector_3 after assignation >>>");
	SHOW(ft_vector_4, "ft_vector_4", "<<< ft_vector_4 after assignation >>>");

	std::cout << "<<< Tests de comparaison >>>" << std::endl;
	if (ft_vector_3 == ft_vector_3)
		std::cout << "ft_vector_3 == ft_vector_3 : True" << std::endl;
	if (ft_vector_3 != ft_vector_4)
		std::cout << "ft_vector_3 != ft_vector_4 : True" << std::endl;
	if (ft_vector_3 > ft_vector_4)
		std::cout << "ft_vector_3 > ft_vector_4 : True" << std::endl;
	if (ft_vector_4 < ft_vector_3)
		std::cout << "ft_vector_4 < ft_vector_3 : True" << std::endl;
	
	return(0);
}