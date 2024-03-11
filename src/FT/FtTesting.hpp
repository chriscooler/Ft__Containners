
#ifndef FT_TESTING_HPP
# define FT_TESTING_HPP

# include <stdlib.h>
# include <iostream>

# include <map>
# include <stack>
# include <vector>

void	testingVector(void);
void	testingVectorCapacity(std::vector<char> *test);
void	testingVectorIterator(std::vector<char> *test);
void	testingVetorModifiers(std::vector<char> *test);
void	testingVectorAllocator(void);

void	testingStack(void);
void	testingMap(void);

void	testingMapIterator(std::map<int, std::string> *test);
void	testingMapCapacity(std::map<int, std::string> *test);

#endif
