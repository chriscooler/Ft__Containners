#ifndef TREE_ITERATOR_HPP
# define  TREE_ITERATOR_HPP

#include "typeTraits.hpp"
#include "iterator.hpp"
#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"
#include "bidirectional_iterator.hpp"

namespace ft
{
	template <class data, class T>
	class tree_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		public:
			typedef T								value_type;
			typedef T*								node_ptr;
			typedef data&							reference;
			typedef data*							pointer;
			typedef ptrdiff_t						difference_type;
			typedef ft::bidirectional_iterator_tag	iterator_category;

		protected:
			node_ptr	_it;
			node_ptr	_root;
			node_ptr	_NIL;

		public:
		
			tree_iterator(void) : _it(NULL), _root(NULL), _NIL(NULL) {}
			tree_iterator(node_ptr it, node_ptr root, node_ptr NIL) : _it(it), _root(root), _NIL(NIL) {}
			tree_iterator(const tree_iterator &cpy) : _it(cpy._it), _root(cpy._root), _NIL(cpy._NIL) {}

			operator tree_iterator<const data, T>(void) const
			{
				return (tree_iterator<const data, T>(_it, _root, _NIL));
			}

			tree_iterator &operator=(const tree_iterator &it)
			{
				this->_it = it._it;
				this->_root = it._root;
				this->_NIL = it._NIL;
				return (*this);
			}

			bool operator==(const tree_iterator &it) const
			{
				return (this->_it == it._it);
			}

			bool operator!=(const tree_iterator &it) const
			{
				return (this->_it != it._it);
			}

			reference operator*(void)
			{
				return (this->_it->data);
			}

			reference operator*(void) const
			{
				return (this->_it->data);
			}

			pointer operator->(void) const
			{
				return (&_it->data);
			}

			tree_iterator &operator++(void)
			{
				if (this->_it != this->_NIL)
					this->_it = _findNext();
				return (*this);
			}

			tree_iterator operator++(int)
			{
				tree_iterator tmp(*this);
				++(*this);
				return (tmp);
			}

			tree_iterator &operator--(void)
			{
				if (_it != _NIL)
					_it = _findPrev();
				else
					_it = _findMax(_root);
				return (*this);
			}

			tree_iterator operator--(int)
			{
				tree_iterator tmp(*this);
				--(*this);
				return (tmp);
			}

			node_ptr base(void) const
			{
				return (this->_it);
			}

		private:
			node_ptr _findMin(node_ptr n)
			{
				while (n->left != this->_NIL)
					n = n->left;
				return (n);
			}

			node_ptr _findMax(node_ptr n)
			{
				while (n->right != this->_NIL)
					n = n->right;
				return (n);
			}

			node_ptr _findNext(void)
			{
				node_ptr n = _it;
				if (n->right != this->_NIL)
					return (_findMin(n->right));
				node_ptr next = n->parent;
				for (; next != _NIL && n == next->right; n = next, next = next->parent)
				{}
    			return (next);
			}

			node_ptr _findPrev(void)
			{
				node_ptr n = _it;
				if (n->left != this->_NIL)
					return (_findMax(n->left));

				node_ptr prev = n->parent;
				for (; prev != this->_NIL && n == prev->left; n = prev, prev = prev->parent)
				{}
				return (prev);
			}
	};

	template <class data, class T1, class T2>
	bool operator==(const tree_iterator<data, T1> &it1, const tree_iterator<data, T2> &it2)
	{
		return (it1.base() == it2.base());
	}

	template <class data, class T1, class T2>
	bool operator!=(const tree_iterator<data, T1> &it1, const tree_iterator<data, T2> &it2)
	{
		return (!(it1 == it2));
	}
}

#endif
