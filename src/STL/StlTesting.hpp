#ifndef STL_TESTING_HPP
# define STL_TESTING_HPP
# include <stdlib.h>
# include <iostream>

# include "./../../containers/vector.hpp"
# include "./../../containers/stack.hpp"
# include "./../../containers/map.hpp"

void	testingVector(void);
void	testingVectorCapacity(ft::vector<char> *test);
void	testingVectorIterator(ft::vector<char> *test);
void	testingVetorModifiers(ft::vector<char> *test);
void	testingVectorAllocator(void);

void	testingStack(void);
void	testingMap(void);

void	testingMapIterator(ft::map<int, std::string> *test);
void	testingMapCapacity(ft::map<int, std::string> *test);

#endif
