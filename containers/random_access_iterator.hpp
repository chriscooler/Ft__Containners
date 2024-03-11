#pragma once
#include "iterator.hpp"

namespace ft
{
	template <class Iterator>
		class random_access_iterator : 
		public iterator<random_access_iterator_tag, Iterator> 
        {
			// _______Member types
			protected:
				typedef iterator<random_access_iterator_tag, Iterator>	iterator;
			
			public:
				typedef typename iterator::value_type			value_type;
				typedef typename iterator::difference_type		difference_type;
				typedef typename iterator::pointer				pointer;
				typedef typename iterator::reference			reference;
				typedef typename iterator::iterator_category	iterator_category;
			
			// _______Member functions

			public:
				random_access_iterator(void) { this->_ptr = NULL; }
				random_access_iterator(pointer ptr) { this->_ptr = ptr; }
				random_access_iterator(random_access_iterator const &copy) { *this = copy;}
                
				pointer base(void) const { return (this->_ptr); }
                    
				operator random_access_iterator<const Iterator> () {
					return (random_access_iterator<const Iterator> (this->_ptr));
				}
		
				random_access_iterator&	operator=(random_access_iterator const &rhs) {
					if (this != &rhs)
						this->_ptr = rhs.base();
					return (*this);
				}

                reference   operator*() {
				    return (*(this->_ptr));
				}
                
				reference	operator*() const {
					return (*(this->_ptr));
				}
                    
                // '->' used with pointers to access the class or struct variables
				pointer		operator->() const {
					return (this->_ptr);
				}
                    
                // convertible to reference
				reference	operator[](difference_type n) const {
					return (*(this->_ptr + n));
				}
				
				//  Operator++ -> post-incrementation :
				random_access_iterator&	operator++(void) { 
					++this->_ptr;
					return (*this);
				}
                    
                //  Operator++ -> pre-incrementation :
				random_access_iterator	operator++(int) {
					random_access_iterator	tmp = this->_ptr;
					++this->_ptr;
					return (tmp);
				}

                //  Operator-- -> post-decrementation :
				random_access_iterator&	operator--(void) { 
					--this->_ptr;
					return (*this);
				}
					
                //   Operator-- -> pre-decrementation :
				random_access_iterator	operator--(int) { 
					random_access_iterator	tmp = this->_ptr;
					--this->_ptr;
					return (tmp);
				}
				
				// Operators : arithmetic
				random_access_iterator	operator-(difference_type n) const { 
                    return (this->_ptr - n);
				}
					
				random_access_iterator	operator+(difference_type n) const { 
                    return (this->_ptr + n);
				}
				
				template <class T>
				friend random_access_iterator<T>
                operator+(typename random_access_iterator<T>::difference_type n,
					random_access_iterator<T> const & rhs);

				template <class T>
				friend random_access_iterator<T> 
                operator-(typename random_access_iterator<T>::difference_type n,
					random_access_iterator<T> const & rhs);

				// Assignment Operators

				random_access_iterator	operator+=(difference_type n) {
					this->_ptr += n;
					return (*this);
				}

				random_access_iterator	operator-=(difference_type n) {
					this->_ptr -= n;
					return (*this);
				}

                // Operator : in/equality relational
				bool	operator==(random_access_iterator const &rhs) const {
					return (this->base() == rhs._ptr);
				}

				bool	operator==(random_access_iterator<const Iterator> &rhs) const {
					return (this->base() == rhs.base());
				}

				bool	operator!=(random_access_iterator const &rhs) const {
					return (this->base() != rhs._ptr);
				}

				bool	operator!=(random_access_iterator<const Iterator> &rhs) const {
					return  (this->base() != rhs.base());
				}

				//Operator : Inequality relational 
                
				bool	operator<(random_access_iterator const &rhs) const {
					return (this->base() < rhs._ptr);
				}

				bool	operator<(random_access_iterator<const Iterator> &rhs) const {
					return (this->base() < rhs.base());
				}

				bool	operator<=(random_access_iterator const &rhs) const { 
					return (this->base() <= rhs._ptr);
                }
				
				bool	operator<=(random_access_iterator<const Iterator> &rhs) const {
					return (this->base() <= rhs.base());
				}

				bool	operator>(random_access_iterator const &rhs) const { 
					return (this->base() > rhs._ptr);
				}

				bool	operator>(random_access_iterator<const Iterator> &rhs) const {
					return (this->base() > rhs.base());
				}

				bool	operator>=(random_access_iterator const &rhs) const {
					return (this->base() >= rhs._ptr);
				}

				bool	operator>=(random_access_iterator<const Iterator> &rhs) const {
					return (this->base() >= rhs.base());
				}
		};

		//non-member function overload
		template <typename It1, typename It2>
		bool operator==(const random_access_iterator<It1>& lhs, const random_access_iterator<It2>& rhs) {
				if (lhs.base() == rhs.base())
					return (true);
				return (false); 
		}

		template <typename It1, typename It2>
		bool operator!=(const random_access_iterator<It1>& lhs, const random_access_iterator<It2>& rhs) {
				if (lhs.base() != rhs.base())
					return (true);
				return (false);
		}

		template <typename It1, typename It2>
		bool operator<(const random_access_iterator<It1>& lhs, const random_access_iterator<It2>& rhs) {
				if (lhs.base() < rhs.base())
					return (true);
				return (false);
		}

		template <typename It1, typename It2> 
		bool operator<=(const random_access_iterator<It1>& lhs, const random_access_iterator<It2>& rhs) {
				if (lhs.base() <= rhs.base())
					return (true);
				return (false);
		}
	
		template <typename It1, typename It2>
		bool operator>(const random_access_iterator<It1>& lhs, const random_access_iterator<It2>& rhs) {
				if (lhs.base() > rhs.base())
					return (true);
				return (false); 
		}
	
		template <typename It1,typename It2>
		bool operator>=(const random_access_iterator<It1>& lhs, const random_access_iterator<It2>& rhs) {
				if (lhs.base() >= rhs.base())
					return (true);
				return (false);
		}
		
		// Non-member functions operators
        
		template <typename Iterator>
		random_access_iterator<Iterator>	
            operator+(typename random_access_iterator<Iterator>::difference_type n, random_access_iterator<Iterator> const &rhs) {
				return (rhs.base() + n); 
		}
		
		template <typename Iterator>
		random_access_iterator<Iterator>
            operator-(typename random_access_iterator<Iterator>::difference_type n, random_access_iterator<Iterator> const &rhs) {
				return (rhs.base() - n);
		}
		
		template <typename It1, typename It2> 
		typename random_access_iterator<It1>::difference_type
            operator+(random_access_iterator<It1> const &lhs, random_access_iterator<It2> const &rhs) {
				return (lhs.base() + rhs.base());
		}

		template <typename It1, typename It2> 
		typename random_access_iterator<It1>::difference_type 
            operator-(random_access_iterator<It1> const &lhs, random_access_iterator<It2> const &rhs) {
				return (lhs.base() - rhs.base());
		}
}

//https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator