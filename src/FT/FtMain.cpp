
#include "./FtTesting.hpp"

int		main(void) 
{
	std::cout << "-------------- [ TESTING ] --------------" << std::endl;
	std::cout << std::endl;
	std::cout << "-------------- [ VECTOR ] ---------------" << std::endl;
	testingVector();
	std::cout << "--------------- [ STACK ] ---------------" << std::endl;
	testingStack();
	std::cout << std::endl << "---------------- [ MAP ] ----------------"  << std::endl;
	testingMap();
	std::cout << std::endl << "--------------- [ LEAKS ] ---------------"  << std::endl;
	system("leaks ft_container");
	return (0);
}
