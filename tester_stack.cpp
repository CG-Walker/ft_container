#include "Stack.hpp"
#include "tester.hpp"

#include <stack>
#include <iostream>

int main(void)
{
	std::stack<int> std_stack;
	ft::stack<int> ft_stack;

	std_stack.push(42);
	ft_stack.push(42);

	std::cout << std_stack.top() << std::endl;
	std::cout << ft_stack.top() << std::endl;
	std::cout << std_stack.size() << std::endl;
	std::cout << ft_stack.size() << std::endl;

	std_stack.pop();
	ft_stack.pop();

	std::cout << std_stack.empty() << std::endl;
	std::cout << ft_stack.empty() << std::endl;

	std::cout << std_stack.size() << std::endl;
	std::cout << ft_stack.size() << std::endl;
}