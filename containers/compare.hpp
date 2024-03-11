#ifndef COMPARE_HPP
# define COMPARE_HPP

// ------------------------------- COMPARE ----------------------------
	// lexicographical_compare function in the provided code is similar in functionality 
	// to the std::lexicographical_compare function in C++.
	// std::lexicographical_compare is a standard library function in C++ 
	// that compares two sequences lexicographically, 
	// just like the function defined in the code snippet you provided.
	// the functions follow the lexicographical comparison algorithm, 
	// allowing you to compare two sequences of elements efficiently,
	// and they both provide overloads to support custom comparison 
	// operations through a comparison function object.

	// https://www.cplusplus.com/reference/algorithm/lexicographical_compare/
//----------------------------------------------------------------------

namespace ft
{
	template <class InputIterator1, class InputIterator2>
  	    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                        InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1) 
                return false;
			else if (*first1 < *first2) 
                return true;
			++first1; 
            ++first2;
		}
		return (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
									    InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || comp(*first2, *first1))
                return false;
			else if (comp(*first1, *first2))
                return true;
			++first1;
            ++first2;
		}
		return (first2 != last2);
	};
}
#endif