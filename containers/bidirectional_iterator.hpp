#pragma once
#include "iterator.hpp"

//------------------------------- BIDIRECTIONAL_ITERATOR----------------------------
	// A bidirectional iterator in C++ is a type of iterator that allows traversal through 
	// a sequence of elements in both forward and backward directions.
	// Unlike forward iterators, which only support moving forward through a container, 
	// bidirectional iterators provide the capability to move both forward and backward.
	// This flexibility enables operations such as decrementing the iterator position,
	// which is useful in scenarios where bidirectional movement is required, 
	// such as traversing a doubly linked list or iterating over elements in reverse order. 
	// Bidirectional iterators are one of the five iterator categories defined in the C++ Standard Library, 
	// offering a balance between functionality and efficiency for various container types and algorithms.
// ------------------------------------------------------------------------------	

namespace ft
{
	template <class Iterator>
	class bidirectional_iterator : public iterator<bidirectional_iterator_tag, Iterator>
	{
		// _______Member types
		protected:
			typedef iterator<bidirectional_iterator_tag, Iterator>	iterator;
            
		public:
			typedef typename iterator::value_type					value_type;
			typedef typename iterator::difference_type				difference_type;
			typedef typename iterator::iterator_category			iterator_category;
			typedef typename iterator::pointer						pointer;
			typedef typename iterator::reference 					reference;
		
	    // _______Member functions
		public:
			bidirectional_iterator () { this->_ptr = NULL; }
			bidirectional_iterator (pointer ptr) { this->_ptr = ptr; }
			bidirectional_iterator (bidirectional_iterator const &rhs) { *this = rhs; }
			pointer base(void) const { return (this->_ptr); };

			operator bidirectional_iterator<const Iterator> (void) {
				return (bidirectional_iterator<const Iterator> (this->_ptr));
			};
		
			// Dereference operator
			bidirectional_iterator &operator=(bidirectional_iterator const &rhs) { 
				if (*this != rhs)
					this->_ptr = rhs._ptr;
				return (*this);
			}

			reference 	operator*(void) const {
				return (*(this->_ptr));
			}
			
			pointer 	operator->(void) { 
				return (this->_ptr);
			}
			
			// Operator : increment
			bidirectional_iterator & operator++(void) { 
				this->_ptr += 1;
				return (*this);
			}

			bidirectional_iterator operator++(int) { 
				bidirectional_iterator tmp = this->_ptr;
			
				this->_ptr += 1;
				return (tmp);
			}

			// Operator : decrement
			bidirectional_iterator & operator--(void) {
				this->_ptr -= 1;
				return (*this);
			}

			bidirectional_iterator operator--(int) {
				bidirectional_iterator tmp = this->_ptr;
	
				this->_ptr -= 1;
				return (tmp);
			}

			bool operator==(bidirectional_iterator const & rhs) const {
				return  (this->base() == rhs._ptr);
			}

			bool operator==(bidirectional_iterator<const Iterator> & rhs) const { 
				return  (this->base() == rhs._ptr);
			}

			bool operator!=(bidirectional_iterator const & rhs) const {
				return  (this->base() != rhs._ptr);
			}

			bool operator!=(bidirectional_iterator<const Iterator> & rhs) const {
				return  (this->base() != rhs._ptr);
			}

	};

// ________Non-member function overloads
	
	template <class It1, class It2>
		bool operator==(const bidirectional_iterator<It1>& lhs, const bidirectional_iterator<It2>& rhs) {
			return (&(*lhs.base()) == &(*rhs.base()));
		}

	template <class It1, class It2>
		bool operator!=(const bidirectional_iterator<It1>& lhs, const bidirectional_iterator<It2>& rhs) {
			return (&(*lhs.base()) != &(*rhs.base()));
		}
}
