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
	return (0);

}

void    tester_vector()
{
  	//	TEST DES DIFFERENTS CONSTRUCTEURS
	std::cout << "========== TEST CONSTRUCTEURS PAR DEFAUT ET PAR RANGE ==========\n";
	std::vector<int>		std_vector_1;
	std::vector<int>		std_vector_2(5, 42);

	ft::vector<int>			ft_vector_1;
	ft::vector<int>			ft_vector_2(5, 42);

	// TEST DE PUSH_BACK
	std::cout << "========== TEST DE PUSH_BACK ET POP_BACK() ==========\n";
	for (size_t i = 0; i < 5; i++)
		ft_vector_1.push_back(i);

	for (size_t i = 0; i < 5; i++)
		std_vector_1.push_back(i);

	ft_vector_1.pop_back();
	std_vector_1.pop_back();

	SHOW(ft_vector_1, "ft_vector_1", "<<< ft_vector_1 after 5 push_back() >>>");
	SHOW(std_vector_1, "std_vector_1", "<<< std_vector_1 after 5 push_back() >>>");
	std::cout << std::endl;

	// TEST DE COPY CONSTRUCTOR
	std::cout << "========== TEST CONSTRUCTEUR PAR COPIE (NORMAL ET RANGE) ==========\n";
	std::vector<int>		std_vector_5(std_vector_1.begin(), std_vector_1.end());
	ft::vector<int>			ft_vector_5(ft_vector_1.begin(), ft_vector_1.end());

	SHOW(ft_vector_5, "ft_vector_5", "<<< ft_vector_5 >>>");
	SHOW(std_vector_5, "std_vector_5", "<<< std_vector_5 >>>");

	ft::vector<int>	ft_vector_6(ft_vector_1);
	SHOW(ft_vector_6, "ft_vector_6", "<<< ft_vector_6 after copy constructor >>>");
	std::cout << std::endl;

	// TEST DE ASSIGN PAR INPUT ITERATOR
	std::cout << "========== TEST DE ASSIGN PAR INPUT ITERATOR ==========\n";
	SHOW(ft_vector_2, "ft_vector_2", "<<< ft_vector_2 >>>");
	ft_vector_6.assign(ft_vector_2.begin(), ft_vector_2.end());
	SHOW(ft_vector_6, "ft_vector_6", "<<< ft_vector_6 after assign from ft_vector_2 >>>");
	std::cout << std::endl;

	// TEST DE AT
	std::cout << "========== TEST DE AT ==========\n";
	std::cout << "ft_vector_1.at(3) : " << ft_vector_1.at(3) << std::endl;
	std::cout << "ft_vector_1.at(1) : " << ft_vector_1.at(1) << std::endl;
	std::cout << std::endl;

	// TEST DES OPERATEUR[], DES BACK, FRONT, ETC..
	std::cout << "========== TEST DES OPERATEUR[], DES BACK, FRONT, ETC.. ==========\n";
	std::cout << "ft_vector_1[3] : " << ft_vector_1[3] << std::endl;
	std::cout << "ft_vector_1.front() : " << ft_vector_1.front() << std::endl;
	std::cout << "ft_vector_1.back() : " << ft_vector_1.back() << std::endl;
	std::cout << "ft_vector_1.data() : " << ft_vector_1.data() << std::endl;
	std::cout << "ft_vector_1.max_size() : " << ft_vector_1.max_size() << std::endl;

	std::cout << std::endl;

	// TEST DE SWAP
	std::cout << "========== TEST DE SWAP ==========\n";
	std::cout << "<<< swapping ft_vector_1 with ft_vector_2 >>>" << std::endl;
	ft_vector_1.swap(ft_vector_2);
	SHOW(ft_vector_1, "ft_vector_1", "<<< ft_vector_1 after swapping >>>");
	SHOW(ft_vector_2, "ft_vector_2", "<<< ft_vector_2 after swapping >>>");

	std::cout << "ft_vector_2.back() : " << ft_vector_2.back() << std::endl;
	std::cout << std::endl;

	// TEST DE ASSIGN
	std::cout << "========== TEST DE ASSIGN ==========\n";
	ft_vector_2.assign(4, 8);
	SHOW(ft_vector_2, "ft_vector_2", "<<< ft_vector_2 after assign(4, 8) >>>");

	std::cout << "ft_vector_1 size : " << ft_vector_1.size() << std::endl;
	std::cout << "ft_vector_1 at() 1 :" << ft_vector_1.at(1) << std::endl;
	std::cout << "is ft_vector_1 empty() ?" << ft_vector_1.empty() << std::endl;
	std::cout << std::endl;

	// TEST DE INSERT // NE FONCTIONNE PAS
/* 	std::cout << "========== TEST DE INSERT ==========\n";
	SHOW(ft_vector_2, "ft_vector_2", "<<< ft_vector_2 before insert() >>>");
	ft_vector_2.insert(ft_vector_2.end(), 56);
	SHOW(ft_vector_2, "ft_vector_2", "<<< ft_vector_2 after insert(4, 8) >>>"); */
	/* ft_vector_2.insert();
	SHOW(ft_vector_2, "ft_vector_2", "<<< ft_vector_2 after insert(4, 8) >>>");
	ft_vector_2.insert();
	SHOW(ft_vector_2, "ft_vector_2", "<<< ft_vector_2 after insert(4, 8) >>>"); */

	// TEST D'ASSIGNATION
	std::cout << "========== TEST D'ASSIGNATION ==========\n";
	ft::vector<int>		ft_vector_3;
	ft::vector<int>		ft_vector_4;

	for (size_t i = 0; i < 3; i++)
		ft_vector_3.push_back(i);
	ft_vector_4.push_back(1);
		

	SHOW(ft_vector_3, "ft_vector_3", "<<< ft_vector_3 after 3 push_back() >>>");
	SHOW(ft_vector_4, "ft_vector_4", "<<< ft_vector_4 after 1 push_back() >>>");

	
	// TEST DE COMPARAISONS
	std::cout << "========== TEST DE COMPARAISONS ==========\n";
	if (ft_vector_3 == ft_vector_3)
		std::cout << "ft_vector_3 == ft_vector_3 : True" << std::endl;
	if (ft_vector_3 != ft_vector_4)
		std::cout << "ft_vector_3 != ft_vector_4 : True" << std::endl;
	if (ft_vector_3 > ft_vector_4)
		std::cout << "ft_vector_3 > ft_vector_4 : True" << std::endl;
	if (ft_vector_4 < ft_vector_3)
		std::cout << "ft_vector_4 < ft_vector_3 : True" << std::endl;
	std::cout << "<<< assignation de ft_vector_4 avec ft_vector_3 (ft_vector_4 = ft_vector_3) >>>" << std::endl;
	ft_vector_4 = ft_vector_3;

	SHOW(ft_vector_3, "ft_vector_3", "<<< ft_vector_3 after assignation >>>");
	SHOW(ft_vector_4, "ft_vector_4", "<<< ft_vector_4 after assignation >>>");
	std::cout << std::endl;

	// TEST DE ERASE ET RESIZE

	
}

int main(void)
{
    std::cout << "_______________TEST_STACK_______________" << std::endl << std::endl;
	tester_stack();
    std::cout << "_______________TEST_VECTOR_______________" << std::endl << std::endl;
    tester_vector();
	return (0);
}