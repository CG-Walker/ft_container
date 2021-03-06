#include "Stack.hpp"

#include <stack>
#include <iostream>

int main(void)
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

    
	std::cout << "___TEST COPY___" << std::endl;
    ft::stack<int>  copy(ft_stack);
    std::cout << std_stack.top() << std::endl;
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
	return (0);
}