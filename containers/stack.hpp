#ifndef STACK_HPP
# define STACK_HPP

#include <vector>
#include "vector.hpp"

//------------------------------ STACKs ------------------------------ 
	// Stacks are a type of container adaptor, 
	// specifically designed to operate in a LIFO context (last-in first-out), 
	// where elements are inserted and extracted only from one end of the container.
	// stacks are implemented as container adaptors, 
	// which are classes that use an encapsulated object of a specific container 
	// class as its underlying container, 
	// providing a specific set of member functions to access its elements. 
	// Elements are pushed/popped from the "back" of the specific container,
	// which is known as the top of the stack.
//--------------------------------------------------------------------

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{	
	//______Member types
		public:
			typedef T				value_type;
			typedef Container		container_type;
			typedef unsigned int	size_type;

		private:
			container_type			_container;

	//_______Member functions
		public:
			explicit stack(const container_type& ctnr = container_type()) :_container(ctnr) {}
		
		bool empty() const 
		{ 
			return (this->_container.empty()); 
		}
		
		size_type size() const 
		{
			return (this->_container.size()); 
		}
		
		value_type& top() 
		{ 
			return (this->_container.back()); 
		}
		const value_type& top() const 
		{ 
			return (this->_container.back()); 
		}
		
		void push (const value_type& val) 
		{ 
			this->_container.push_back(val); 
		}

		void pop(void) 
		{ 
			this->_container.pop_back(); 
		}

		/*
			The friend declaration appears in a class body and grants a function or another class access to private 
			and protected members(container_type _container) of the class where the friend declaration appears.
		*/
		template <class _T, class _Container>
			friend bool operator==(const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs);

		template <class _T, class _Container>
			friend bool operator!=(const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs);

		template <class _T, class _Container>
			friend bool operator<(const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs);

		template <class _T, class _Container>
			friend bool operator<=(const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs);

		template <class _T, class _Container>
			friend bool operator>(const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs);

		template <class _T, class _Container>
			friend bool operator>=(const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs);
	};

	//______Non-member function overloads

	//Relational operators(stack)
	template <class _T, class _Container> 
		bool operator== (const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs) {
			return (lhs._container == rhs._container); }
		
	template <class _T, class _Container>
		bool operator!= (const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs) {
			return (lhs._container != rhs._container); }

	template <class _T, class _Container>
		bool operator<  (const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs) {
			return (lhs._container < rhs._container); }

	template <class _T, class _Container>
	bool operator<= (const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs) {
			return (lhs._container <= rhs._container); }

	template <class _T, class _Container>
		bool operator>  (const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs) {
			return (lhs._container > rhs._container); }

	template <class _T, class _Container>
		bool operator>= (const stack<_T, _Container>& lhs, const stack<_T, _Container>& rhs) {
			return (lhs._container >= rhs._container); }
}

#endif
