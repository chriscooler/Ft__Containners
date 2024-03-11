#ifndef EQUAL_HPP
# define EQUAL_HPP

//  ------------------------------- EQUAL ----------------------------------
	// Binary function that accepts two elements as argument 
	// (one of each of the two sequences, in the same order),
	// and returns a value convertible to bool. 
	// The value returned indicates whether the elements are 
	// considered to match in the context of this function.
	// The function shall not modify any of its arguments.
	// This can either be a function pointer or a function object.

	// https://www.cplusplus.com/reference/algorithm/equal/
//  -----------------------------------------------------------------------
namespace ft
{
    //default
	template <class InputIterator1, class InputIterator2>
	    bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2))
				return false;
			++first1; 
			++first2;
		}
		return true;
	}
   
	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	    bool equal (InputIterator1 first1, InputIterator1 last1,
				    InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1 != last1)
		{
			if (!pred(*first1, *first2))
				return false;
			++first1; 
			++first2;
		}
		return true;
	};
}

#endif
