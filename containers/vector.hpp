#ifndef VECTOR_HPP
# define VECTOR_HPP

#include "equal.hpp"
#include "typeTraits.hpp"
#include "compare.hpp"
#include "iterator.hpp"
#include "bidirectional_iterator.hpp"
#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include "random_access_iterator.hpp"
#include <cstring>

		// allocate   --> malloc array
		// constrcut  --> malloc elements
		// destroy    --> free elements
		// deallocate --> free array
		
namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		//_______Member types
		public:
			typedef T											value_type;     //first template parameter
			typedef Alloc										allocator_type; //second template parameter
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef ft::random_access_iterator<T>				iterator;
			typedef ft::random_access_iterator<const T>			const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
			typedef typename allocator_type::difference_type	difference_type;
			typedef typename allocator_type::size_type 			size_type;
			
		private:
			allocator_type		_alloc;
			size_type			_size;
			size_type			_capacity;
			pointer 			_ptr;
			pointer				_start;
			pointer				_end;
			
		private:
			size_type newCapacity(size_type size, size_type capacity)
			{
				capacity *= 2;
				if (capacity <= 0)
					capacity = 1;
				while (size + 1 > capacity)
					this->_capacity *= 2;
				return (capacity);
			};
		
			//______Member functions
			//empty container constructor (default constructor) 
		public:
			explicit vector (const allocator_type& alloc = allocator_type())
			{
				this->_alloc = alloc;
				this->_size = 0;
				this->_capacity = 0;
				this->_ptr = NULL;
				this->_start = NULL;
				this->_end = NULL;
			}
			
			//fill constructor
			explicit vector (size_type n, const value_type & val = value_type(),
						const allocator_type & alloc = allocator_type()) : 
			_alloc(alloc),  _size(n), _capacity(n), _ptr(NULL), _start(NULL), _end(NULL)
			{
				if (!(this->_ptr = this->_alloc.allocate(n)))
						throw std::bad_alloc();
				for (size_type i = 0; i < n; i++)
					this->_alloc.construct(_ptr + i, val);
				this->_start = this->_ptr;
				this->_end = this->_ptr + n;
			}

			//range constructor
			template <typename InputIterator>
        	vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), 
					typename enable_if<!is_integral<InputIterator>::value, bool>::type = false)
					: _alloc(alloc), _size(0), _capacity(0), _ptr(NULL), _start(NULL), _end(NULL)
			{
				difference_type	dist = ft::distance<InputIterator>(first, last);
				if (!(this->_ptr = this->_alloc.allocate(dist)))
					throw std::bad_alloc();
				for (size_type i = 0; first != last; i++)
					this->_alloc.construct(this->_ptr + i, *first++);
				this->_start = this->_ptr;
				this->_end = this->_ptr + (dist);
				this->_size = dist;
				this->_capacity = dist;
			}
			
			//copy constructor
			vector (const vector& x) : _alloc(x._alloc), _size(0) , _capacity(0), _ptr(NULL), _start(NULL), _end(NULL)
			{
				if (!(this->_ptr = this->_alloc.allocate(x.capacity())))
					throw std::bad_alloc();
				size_type i = 0;
				for (const_iterator it = x.begin(); it != x.end(); it++)
				{
					this->_alloc.construct(this->_ptr + i, *it);
					i++;
				}
				this->_capacity = x.capacity();
				this->_size = x._size;
				this->_start = this->_ptr;
				this->_end = this->_ptr + (this->_size);
				this->_alloc = x._alloc;
			}
			
			//destructor
			~vector(void)
			{
				this->clear();
				this->_alloc.deallocate(_start,_capacity);
			}
	
			vector& operator=(const vector& x) 
			{
				if (this == &x)
					return (*this);
				if (this->_size)
					this->clear();
				if (this->_start)
					this->_alloc.deallocate(this->_ptr, this->_capacity);
				if (this != &x)
				{
					if (!x._ptr)
					{
						this->_start = NULL;
						this->_end = NULL;
						this->_ptr = NULL;
						this->_size = 0;
						return (*this);
					}
					size_type i = 0;
					if (!(this->_ptr = this->_alloc.allocate(x._size)))
						throw std::bad_alloc();
					this->_capacity = x.capacity();
					this->_size = x._size;
					for (const_iterator it = x.begin(); it != x.end(); it++)
						this->_alloc.construct(this->_ptr + i++, *it);
					this->_start = this->_ptr;
					this->_end = this->_ptr + (this->_size);
				}
				return (*this);
			}

			//_______iterator
			iterator				begin(void) 		
			{ 
				return iterator(this->_start);
			}
			const_iterator			begin(void)const	
			{ 
				return const_iterator(this->_start); 
			}
			iterator				end(void)			
			{ 
				return iterator(this->_end); 
			}
			const_iterator			end(void)const		
			{ 
				return const_iterator(this->_end); 
			}
			reverse_iterator		rbegin(void)		
			{ 
				return reverse_iterator(this->end()); 
			}
			const_reverse_iterator	rbegin(void)const	
			{ 
				return const_reverse_iterator(this->end()); 
			}
			reverse_iterator		rend(void)			
			{ 
				return reverse_iterator(this->begin()); 
			}
			const_reverse_iterator	rend(void)	const	
			{ 
				return const_reverse_iterator(this->begin());
			}

			//______Capacity
			//size : return size
			size_type	size() const 
			{ 
				return (this->_size); 
			}
			//max_size : return maximum size
			size_type 	max_size() const 
			{ 
				return (this->_alloc.max_size()); 
			}

			//resize: Change size
			void	resize (size_type n, value_type val = value_type()) 
			{
				if (n >= SIZE_MAX)
					throw std::length_error("vector::resize");
				while (n < this->_size)
					pop_back();
				while (n > this->_size)
					push_back(val);
			}
			
			//capacity: Return size of allocated storage capacity
			size_type capacity() const
			{
				return (this->_capacity);
			}
			//empty():
			bool empty() const 
			{
				if (this->size() == 0)
					return (true);
				return (false);
			}
			//reserve: Request a change in capacity
			void reserve (size_type n) 
			{
				pointer			new_ptr;
				allocator_type	new_alloc;
				size_type		size = this->size();

				if(n <= this->capacity())
					return;
				if (n > this->max_size())
					throw std::length_error("element n exceeds maximum supported size in the container");
				else if (n > this->capacity()) 
				{
					if (!(new_ptr = new_alloc.allocate(n)))
						throw std::bad_alloc();
					for (size_type i = 0; i < size; i++)
						new_alloc.construct(new_ptr + i, this->_ptr[i]);
					this->clear();
					this->_alloc.deallocate(this->_ptr, this->capacity());
					this->_size = size;
					this->_capacity = n;
					this->_ptr = new_ptr;
					this->_start = this->_ptr;
					this->_end = this->_ptr + (size);
				}
			}

			//______Element access
			//operator[]: Access element
			reference operator[] (size_type n)
			{
				return (*(this->_start + n));
			}

			const_reference operator[] (size_type n) const 
			{
				return (*(this->_start + n));
			}

			//at: Access element
			reference at (size_type n) {
				if(n >= this->size())
					throw std::out_of_range("vector::at");
				return (_start[n]);
			}

			const_reference at (size_type n) const
			{
				if (n >= this->size())
					throw std::out_of_range("vector::at const");
				return (_start[n]);
			}

			//front: Access first element
			reference front(void)
			{
				return ((*this)[0]);
			}
			const_reference front(void) const
			{
				return ((*this)[0]);
			}
			
			//back: Access last element
			reference back(void)
			{
				return(*(this->_end - 1));
			}
			const_reference back(void) const
			{
				return(*(this->_end - 1));
			}
				
			//_______Modifies
			//assign: range
			template <class InputIterator>
			void assign (InputIterator first, InputIterator last, 
			typename enable_if<!is_integral<InputIterator>::value,bool>::type = false)
			{	
				size_type distance = ft::distance(first, last);
				if (distance > max_size())
					throw std::length_error("vector::assign");
				if (distance > capacity())
				{
					_alloc.deallocate(this->_start, this->_capacity);
					this->_start = _alloc.allocate(distance);
					this->_capacity = distance;
				}
				size_type i = 0;
				for (; first != last; ++first, ++i)
				{
					_alloc.construct(this->_start + i, *first);
				}
				for (; i < size(); ++i)
				{
					_alloc.destroy(this->_start + i);
				}
				this->_size = distance;
				this->_end = this->_start + distance;
			}
		
			//assign: fill
			void assign (size_type n, const value_type& val)
			{
				pointer			new_ptr;
				allocator_type	new_alloc;

				this->clear();
				if (n > this->capacity()) {
					if (!(new_ptr = new_alloc.allocate(n)))
						throw std::bad_alloc();
					this->clear();
					this->_alloc.deallocate(this->_ptr, this->capacity());
					this->_capacity = n;
					this->_ptr = new_ptr;
					this->_start = this->_ptr;
				}
				for (size_type i = 0; i< n; i++)
					this->_alloc.construct(this->_ptr + i, val);
				this->_size += n;
				this->_end = this->_ptr + (this->size());
			}
			
			//push_back
			void push_back (const value_type& val)
			{
				pointer			new_ptr;
				allocator_type	new_alloc;
				size_type		new_capacity = this->capacity();
				size_type		size = this->size();
				size_type		capacity = this->capacity();
				
				if (size >= new_capacity)
				{
					if (!(new_capacity))
						new_capacity = 1;
					else
						new_capacity *= 2;
					if (!(new_ptr = new_alloc.allocate(new_capacity)))
						throw std::bad_alloc();
					for (size_type i = 0; i < size; i++)
						new_alloc.construct(new_ptr + i, this->_ptr[i]);
					new_alloc.construct(new_ptr + size, val);
					for (size_t i = 0; i < this->size(); i++)
						_alloc.destroy(_ptr + i);
					this->_alloc.deallocate(this->_ptr, capacity);
					this->_capacity = new_capacity;
					this->_ptr = new_ptr;
					this->_start = this->_ptr;
				}
				else
					this->_alloc.construct(this->_ptr + size, val);
				this->_size = size + 1;
				this->_end = this->_ptr + this->_size;
			}

			//pop_back : Delete last element
			void pop_back(void) 
			{ 
				if (this->_size > 0)
				{
					this->_alloc.destroy(this->_end - 1);
					this->_size--;
					this->_end--;
				}
			}
			
			//insert(1): single element
			iterator insert(iterator position, const value_type& val) 
			{
				pointer			new_ptr;
				allocator_type	new_alloc;
				size_type		new_size = this->size();
				difference_type	new_dst = ft::distance(this->begin(), position);
			
				if (new_size >= this->capacity())
				{
					size_type new_capacity = newCapacity(new_size, this->capacity());
					if (!(new_ptr = new_alloc.allocate(new_capacity)))
						throw std::bad_alloc();
					for (size_type i = 0; i < new_size; i++)
						new_alloc.construct(new_ptr + i, this->_ptr[i]);
					new_alloc.construct(new_ptr + new_size, val);
					this->clear();
					this->_alloc.deallocate(this->_ptr, new_capacity);
					this->_capacity = new_capacity;
					this->_ptr = new_ptr;
					this->_size = new_size;
					this->_start = this->_ptr;
					this->_end = this->_ptr + (this->size() - 1);
				}
				this->_alloc.construct(this->_ptr + this->size(), val);
				this->_size++;
				this->_end = this->_start + (this->size());
				for (iterator it = this->end() - 1; it != (this->begin() + new_dst - 1); it--)
				{
					if ((it - 1) != (this->begin() - 1))
						*it = *(it - 1);
				}
				*(this->begin() + new_dst) = val;
				return (iterator(this->_start + new_dst));
			}
			
			void insert (iterator position, size_type n, const value_type& val)
			{
				for (size_type i = 0; i < n; i++)
					position = this->insert(position, val);
			}
			
			//insert(3): range
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last,
			typename enable_if<!is_integral<InputIterator>::value,bool>::type = false) 
			{
				vector<value_type> tmp;
				for (InputIterator it = first; it != last; it++) 
					tmp.push_back(*it);
				for (reverse_iterator rit = tmp.rbegin(); rit != tmp.rend(); rit++)
					position = this->insert(position, *rit);
			}
			
			iterator erase (iterator position)
			{
				for (iterator it = this->begin(); it != this->end(); it++)
				{
					if (it > position)
						*(it - 1)= *it;
				}
				this->_size--;
				this->_alloc.destroy(this->_ptr + this->size());
				this->_end = this->_start + (this->size());
				return (position);
			}
		
			//erase(2)
			iterator erase (iterator first, iterator last)
			{
				for (iterator it = first; it != last; it++)
					this->erase(first);
				return (first);
			}
			
			//swap
			void swap(vector & x)
			{
				if (this == &x)
					return ;
				allocator_type	tmp_alloc = this->_alloc;
				pointer			tmp_ptr = this->_ptr, tmp_start = this->_start, tmp_end = this->_end;
				size_type		tmp_size = this->_size, tmp_capacity = this->_capacity;

				this->_alloc = x._alloc;
				this->_size = x._size;
				this->_capacity = x._capacity;
				this->_ptr = x._ptr;
				this->_start = x._start;
				this->_end = x._end;
				x._alloc = tmp_alloc;
				x._size = tmp_size;
				x._capacity = tmp_capacity;
				x._ptr = tmp_ptr;
				x._start = tmp_start;
				x._end = tmp_end;
			}
			
			//clear
			void clear()
			{
				for (size_type i = 0; i < this->_size; i++)
					this->_alloc.destroy(this->_start + i);
				this->_end = this->_start;
				this->_size = 0;
				this->_capacity = 0;
			}

			allocator_type get_allocator(void) const 
			{
				return (this->_alloc); 
			}
	};

	template <class T, class Alloc>
	bool operator==( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
	{
		if (lhs.size() == rhs.size())
			return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		return (false);
	}
	
	template <class T, class Alloc>
	bool operator!=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
	{
		return (!(lhs == rhs));
	}
	
	template <class T, class Alloc>
	bool operator<( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
	{
		return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator<=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
	{
		return (lhs < rhs || lhs == rhs);
	}
	
	template <class T, class Alloc>
	bool operator>( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
	{
		if (lhs < rhs || lhs == rhs)
			return (false);
		return (true);
	}
	
	template <class T, class Alloc>
	bool operator>=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
	{
		if (lhs == rhs || lhs > rhs)
			return (true);
		return (false);
	}
}
#endif