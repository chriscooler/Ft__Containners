#ifndef INTEGRAL_HPP
# define INTEGRAL_HPP

#include <iostream>
#include <cstddef>
#include <memory>
#include <stdexcept>

	//------------------------------- ENABLE / IS_INTERGRAL ----------------------------
		// Enable type if condition is met
		// The type T is enabled as member type enable_if::type if Cond is true.
		// Otherwise, enable_if::type is not defined.
		// Cond = A compile-time constant of type bool. T = a type

		// integral_constant <----- is_integral
		// std::is_integral is a type trait in C++ 
		// that can be used to determine whether a given type is an integral type or not. 
		// An integral type is any type that can represent a whole number,
		// such as int, char, short, long, long long, unsigned int, unsigned char, and so on.
		// The std::is_integral type trait is defined in the <type_traits> header
		// and can be used as a template type trait.
		// It takes one template parameter which is the type being checked, 
		// and has a static member value that is true if the type is integral, and false otherwise.

		//https://www.cplusplus.com/reference/type_traits/integral_constant/
		//https://www.cplusplus.com/reference/type_traits/is_integral/

	//---------------------------------------------------------------------------------
namespace ft
{

	template<bool Cond, class T = void> 		struct enable_if {};
	template<class T> 							struct enable_if<true, T> { typedef T type;};
	

	template <class T, bool val>				struct is_integral_constant								
	{
		 static const		bool 									value = val;
		 typedef			T										val_type;
		 typedef			is_integral_constant<val_type, value> 	type;
		 operator 			val_type()	{ return (value);}
	};
	
	template <class T>//fasle_type
							struct is_integral									: public is_integral_constant<T, false> {};
	template <class T>//true_type						
							struct is_integral <const T>						: is_integral<T> {};					
	template <>				struct is_integral <bool>							: is_integral_constant<bool, true> {};
	template <>				struct is_integral <char>							: is_integral_constant<char, true> {};
	template <>				struct is_integral <wchar_t>						: is_integral_constant<wchar_t, true> {};
	template <>				struct is_integral <signed char>					: is_integral_constant<signed char, true> {};
	template <>				struct is_integral <short int>						: is_integral_constant<short int, true> {};
	template <>				struct is_integral <int>							: is_integral_constant<int, true> {};
	template <>				struct is_integral <long int>						: is_integral_constant<long int, true> {};
	template <>				struct is_integral <long long int>					: is_integral_constant<long long int, true> {};
	template <>				struct is_integral <unsigned int>					: is_integral_constant<unsigned int, true> {};
	template <>				struct is_integral <unsigned char>					: is_integral_constant<unsigned char, true> {};
	template <>				struct is_integral <unsigned short int>				: is_integral_constant<unsigned short int, true> {};
	template <>				struct is_integral <unsigned long int>				: is_integral_constant<unsigned long int, true> {};
	template <>				struct is_integral <unsigned long long int>			: is_integral_constant<unsigned long long int, true> {};
	template <>				struct is_integral <const bool>						: is_integral_constant<const bool, true> {};
	template <>				struct is_integral <const char>						: is_integral_constant<const char, true> {};
	template <>				struct is_integral <const wchar_t>					: is_integral_constant<const wchar_t, true> {};
	template <>				struct is_integral <const signed char>				: is_integral_constant<const signed char, true> {};
	template <>				struct is_integral <const short int>				: is_integral_constant<const short int, true> {};
	template <>				struct is_integral <const int>						: is_integral_constant<const int, true> {};
	template <>				struct is_integral <const long int>					: is_integral_constant<const long int, true> {};
	template <>				struct is_integral <const long long int>			: is_integral_constant<const long long int, true> {};
	template <>				struct is_integral <const unsigned int>				: is_integral_constant<const unsigned int, true> {};
	template <>				struct is_integral <const unsigned char>			: is_integral_constant<const unsigned char, true> {};
	template <>				struct is_integral <const unsigned short int>		: is_integral_constant<const unsigned short int, true> {};
	template <>				struct is_integral <const unsigned long int>		: is_integral_constant<const unsigned long int, true> {};
	template <>				struct is_integral <const unsigned long long int>	: is_integral_constant<const unsigned long long int, true> {};
}

#endif