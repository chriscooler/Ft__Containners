#ifndef MAP_HPP
# define MAP_HPP

#include "iterator.hpp"
#include "bidirectional_iterator.hpp"
#include "reverse_iterator.hpp"
#include "random_access_iterator.hpp"

#include <memory>		// allocator
#include <functional>	//  Less -> Determines whether its first argument compares less than the second
#include "vector.hpp"
#include "equal.hpp"
#include "typeTraits.hpp"
#include "compare.hpp"

#include "tree.hpp"
#include "node.hpp"
#include "pair.hpp"
#include "tree_iterator.hpp"

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:
		    typedef Key											key_type;
            typedef T											mapped_type;
			typedef ft::pair<const key_type, mapped_type>		value_type;
			typedef Compare										key_compare;
            typedef Alloc										allocator_type;
			

			class value_compare  : public std::binary_function<value_type,value_type, bool> 
			{
				friend class map;
				protected:
					Compare										comp;

				public:
					typedef bool								result_type;
					typedef value_type							first_argument_type;
					typedef value_type							second_argument_type;
				
					value_compare () : comp() {}
					bool operator()(const value_type & x, const value_type & y) const
					{
						return (comp(x.first, y.first));
					}
			};
			
		public :
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef	typename allocator_type::size_type			size_type;
			typedef ft::tree<value_type, value_compare>		tree_type;
			typedef typename tree_type::iterator				iterator;
			typedef typename tree_type::const_iterator			const_iterator;
			typedef typename tree_type::reverse_iterator		reverse_iterator;
			typedef typename tree_type::const_reverse_iterator	const_reverse_iterator;

		private:
			tree_type											_tree;
			value_compare										_valComp;
			allocator_type										_alloc;
			key_compare											_keyComp;
		
		public:
			// empty container constructor (default constructor)
			explicit map(const key_compare &comp = key_compare(), 
						 const allocator_type &alloc = allocator_type())
			{
				this->_valComp = value_compare();
				this->_alloc = alloc;
				this->_keyComp = comp;
			}
			
			// Range constructor
			template <class InputIterator>
			map(InputIterator first, InputIterator last,
				const key_compare &comp = key_compare(),
				const allocator_type &alloc = allocator_type())
			{
				this->_valComp = value_compare();
				this->_alloc = alloc;
				this->_keyComp = comp;
				while (first != last)
					this->insert(*first++);
			}
			
			// Copy construcotr
			map(const map& x){ *this = x; }

			map &operator=(const map &x)
			{
				_alloc = x._alloc;
				_keyComp = x._keyComp;
				_valComp = x._valComp;
				_tree = x._tree;
				clear();
				insert(x.begin(), x.end());
				return (*this);
			}


			//Iterators:
			iterator begin()
			{
				return (this->_tree.begin()); 
			}

			const_iterator begin() const
			{
				return (this->_tree.begin()); 
			}

			iterator end()
			{	iterator it = _tree.end();
				it++;
				return (it);
			}

			const_iterator end() const
			{
				const_iterator it = _tree.end();
				it++;
				return (it);
			}

			reverse_iterator rbegin()
			{
				return (this->_tree.rbegin());
			}

			const_reverse_iterator rbegin() const
			{
				return (this->_tree.rbegin());
			}

			reverse_iterator rend()
			{
				return (this->_tree.rend());
			}

			const_reverse_iterator rend() const
			{
				return (this->_tree.rend());
			}

			//Capacity:
			size_type size(void) const
			{
				return (this->_tree.size());
			}

			bool		empty(void) const 
			{ 
				return (this->_tree.empty()); 
			}

			size_type max_size(void) const
			{
				return (this->_tree.max_size());
			}

			//Element access: alternative way to insert elements in a map is by using member function map::operator[].
			mapped_type &operator[](const key_type &k)
			{
				return ((*((this->insert(ft::make_pair(k, mapped_type()))).first)).second);
			}

			//Modifiers:
			// three types : insert
			pair<iterator, bool> insert(const value_type &val)
			{
				return (this->_tree.insert(val));
			}

			iterator insert(iterator position, const value_type &val)
			{
				return (this->_tree.insert(position, val));
			}

			template <class InputIterator>
			void insert(InputIterator first, InputIterator last)
			{
				while (first != last)
					this->_tree.insert(*first++);
			}

			// three types : erase
			void erase(iterator position)
			{
				this->_tree.erase(position);
			}

			size_type erase(const key_type &k)
			{
				return (_tree.erase(ft::make_pair(k, mapped_type())));
			}

			void erase(iterator first, iterator last)
			{
				while (first != last)
					_tree.erase(first++);
			}

			void swap(map &x)
			{
				value_compare	tmp_comp = this->_valComp;
				allocator_type	tmp_alloc = this->_alloc;
				
				this->_valComp = x._valComp;
				this->_alloc = x._alloc;
				x._valComp = tmp_comp;
				x._alloc = tmp_alloc;
				_tree.swap(x._tree);
			}

			void clear(void)
			{
				_tree.clear();
			}

			//Observers:
			key_compare key_comp(void) const
			{
				return (this->_keyComp);
			}

			value_compare value_comp(void) const
			{
				return (this->_valComp);
			}

			//Operations:
			iterator find(const key_type &k)
			{
				return (_tree.find(ft::make_pair(k, mapped_type())));
			}

			const_iterator find(const key_type &k) const
			{
				return (_tree.find(ft::make_pair(k, mapped_type())));
			}

			size_type count(const key_type &k) const
			{
				return (_tree.count(ft::make_pair(k, mapped_type())));
			}

			iterator lower_bound(const key_type &k)
			{
				return (_tree.lower_bound(ft::make_pair(k, mapped_type())));
			}

			const_iterator lower_bound(const key_type &k) const
			{
				return (_tree.lower_bound(ft::make_pair(k, mapped_type())));
			}

			iterator upper_bound(const key_type &k)
			{
				return (_tree.upper_bound(ft::make_pair(k, mapped_type())));
			}

			const_iterator upper_bound(const key_type &k) const
			{
				return (_tree.upper_bound(ft::make_pair(k, mapped_type())));
			}

			pair<iterator,iterator>	equal_range(const key_type& k)
			{
				return (ft::make_pair<iterator, iterator>(lower_bound(k), upper_bound(k)));
			}
			
			pair<const_iterator, const_iterator> equal_range(const key_type& k) const 
			{
				return (ft::make_pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k)));
			}

			//Allocator:
			allocator_type get_allocator(void) const
			{
				return (this->_alloc);
			}
	};

	// Non-member functions overloads: Rational operators

	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
	{
		return ((lhs.size() == rhs.size()) && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}
	
	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>( const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs) 
	{
		return (rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const map<Key,T , Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
		return !(lhs < rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	
	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs) 
	{
		return !(rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	void swap(map<Key, T, Compare, Alloc>& rhs, map<Key, T, Compare, Alloc>& lhs) { rhs.swap(lhs); }
};

#endif