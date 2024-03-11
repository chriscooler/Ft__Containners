#pragma once
#include "iterator.hpp"

//https://legacy.cplusplus.com/reference/iterator/reverse_iterator/

namespace ft
{
	template <class Iterator>
		class reverse_iterator
        {
			// _______Member types
			public:
				typedef Iterator													iterator_type;
				typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
				typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
				typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
				typedef typename ft::iterator_traits<Iterator>::reference			reference;
				typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			
            protected:
				Iterator		_iterator;

			// _______Member functions
			public:
				reverse_iterator(void) : _iterator() {}
				explicit reverse_iterator (iterator_type const it) : _iterator(it) {}
				template <class T>
					reverse_iterator (reverse_iterator<T> const &rev_it) : _iterator(rev_it.base()) {}
				
				iterator_type 		base() const { 
					return (this->_iterator); 
				} 
				
				operator reverse_iterator<const Iterator>() const {
					reverse_iterator<const Iterator> res(this->_iterator);
					return (res);
				}
				template<class It> 
					reverse_iterator & operator=(reverse_iterator<It> const &rhs) {
						if (*this != rhs)
							this->_iterator = rhs.base();
						return (*this);
					}
                
                // Dereference iterator
				reference operator*() {
					iterator_type tmp(_iterator);
					return *(--tmp);
				}
				
				const reference operator*() const {
					iterator_type tmp(_iterator);
					return *(--tmp);
				}
                
				//  Operator++ -> post-incrementation
				reverse_iterator&	operator++(void) { 
					this->_iterator--;
					return (*this);
				}
                
                //  Operator++ -> pre-incrementation
				reverse_iterator	operator++(int) { 
					reverse_iterator	tmp(*this);
					this->_iterator--;
					return (tmp);
				}

				//  Operator-- -> post-decrementation
				reverse_iterator&	operator--(void) { 
					this->_iterator++;
					return (*this);
				}
                
			    // Operator-- -> pre-decrementation
				reverse_iterator	operator--(int) { 
					reverse_iterator	tmp(*this);
					this->_iterator++;
					return (tmp);
				}

				// Operators : arithmetic
				reverse_iterator    operator+(difference_type n) const {
				    return (reverse_iterator(this->_iterator - n));
				}

				reverse_iterator	operator-(difference_type n) const {
					return (reverse_iterator(this->_iterator + n));
				}

				difference_type		operator-(reverse_iterator rhs) { 
                    return (rhs._iterator - this->_iterator); 
                }

				//  Assignment Operators
				reverse_iterator&	operator+=(difference_type n) { 
					this->_iterator -= n;
					return (*this);
				}

				reverse_iterator&	operator-=(difference_type n) {
					this->_iterator += n;
					return (*this);
				}

                // Dereference iterator    
				pointer				operator->() const { 
					iterator_type	tmp(_iterator);
					--tmp;
				    return (&(*tmp));
				}

                // Dereference iterator with offset
				reference			operator[](difference_type n) { 
                    return (*(this->_iterator - n - 1)); 
                }
                
				const reference		operator[](difference_type n) const { 
                    return (*(this->_iterator - n - 1));
                }

		};
				
		// ________Non-member function overloads
		template <class It1, class It2>
			bool operator==(reverse_iterator<It1> const &lhs, reverse_iterator <It2> const &rhs) {
				return (lhs.base() == rhs.base());
			}

		template <class It1, class It2>
			bool operator!=(reverse_iterator<It1> const &lhs, reverse_iterator <It2> const &rhs) {
				return (!(lhs == rhs));
			}

		template <class It1, class It2>
			bool operator<(reverse_iterator<It1>const &lhs, reverse_iterator <It2> const &rhs) {
				return (lhs.base() > rhs.base());
			}

		template <class It1, class It2> 
			bool operator<=(reverse_iterator<It1> const &lhs, reverse_iterator <It2> const &rhs) {
				return (!(lhs > rhs));
			}

		template <class It1, class It2>
			bool operator> (reverse_iterator<It1> const &lhs, reverse_iterator <It2> const &rhs) {
				return (rhs < lhs);
			}

		template <class It1, class It2>
			bool operator>=(reverse_iterator<It1> const &lhs, reverse_iterator <It2> const &rhs) {
				return (!(lhs < rhs));
			}

		// ________Non-member functions operators
		template <typename Iterator> 
			reverse_iterator<Iterator> 
            operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) {
                 return (rev_it + n);
        }
		
		template <typename Iterator>
			typename reverse_iterator<Iterator>::difference_type 
            operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
                return (rhs - lhs); 
        }
}

