#include "Stack.hpp"

#include <stack>
#include <iostream>

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

void    tester_stack()
{
    std::stack<int> std_stack;
	ft::stack<int> ft_stack;
	ft::stack<int> tmp;

	std_stack.push(42);
	ft_stack.push(42);
	std::cout << "___TEST PUSH___" << std::endl;
	std::cout << std_stack.top() << std::endl;
	std::cout << ft_stack.top() << std::endl;
	std::cout << std_stack.size() << std::endl;
	std::cout << ft_stack.size() << std::endl;

	std_stack.pop();
	ft_stack.pop();
	std::cout << "___TEST POP AND EMPTY___" << std::endl;
	std::cout << std_stack.empty() << std::endl;
	std::cout << ft_stack.empty() << std::endl;

	std::cout << std_stack.size() << std::endl;
	std::cout << ft_stack.size() << std::endl;

    ft_stack.push(45);
    ft_stack.push(42);
    ft_stack.push(45);

    tmp = ft_stack;
	std::cout << "tmp top() : " << tmp.top() << std::endl;

	//SHOW(tmp, "tmp", "<<< tmp after assignation >>>");

	std::cout << "___TEST OPERATOR = ___" << std::endl;
	std::cout << tmp.size() << std::endl;
	std::cout << ft_stack.size() << std::endl;

	std::cout << "___TEST construtor by copy ___" << std::endl;
	ft::stack<int> clone(ft_stack);
	std::cout << clone.size() << std::endl;

	tmp.pop();
	if (clone == ft_stack)
		std::cout << "clone == ft_stack" << std::endl;
	if (tmp != clone)
		std::cout << "tmp != clone" << std::endl;
	if (clone > tmp)
		std::cout << "clone > tmpk" << std::endl;
	if (tmp < clone)
		std::cout << "tmp < clone" << std::endl;
	std::cout << "Fin du test." << std::endl;
}

void    tester_vector()
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
	
}

int main(void)
{
    std::cout << "_______________TEST_STACK_______________" << std::endl << std::endl;
	tester_stack();
    std::cout << "_______________TEST_VECTOR_______________" << std::endl << std::endl;
    tester_vector();
	return (0);
}