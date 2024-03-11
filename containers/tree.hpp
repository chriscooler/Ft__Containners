
#ifndef	TREE_HPP
# define TREE_HPP

// ------------------------------ BLACK RED TREES ------------------------------ 
	//    A RED-BLACK tree is a self-balancing binary search tree where each
	//    node has an extra bit, interpreted as the colour (RED or BLACK).
	//    Every RED-BLACK tree follows these 5 rules: 
	//    - Every node has a colour, either RED or BLACK ;
	//    - The root of the tree is always BLACK ;
	//	  - Every RED node must have two black child nodes
	//    - There are no two adjacent RED nodes (a RED node cannot have a RED
	//      parent or RED child) ;
	//    - All simple paths from a node to a leaf contain the same number of black nodes.
	//    - All leaf nodes (_NIL) are black
// ------------------------------------------------------------------------------

#include <memory>
#include <functional>
#include <iostream>

#include "node.hpp"
#include "tree_iterator.hpp"
#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"
#include "bidirectional_iterator.hpp"
#include "iterator.hpp"
#include "pair.hpp"
#include "typeTraits.hpp"

namespace ft
{
	template <class T, class Compare, class Alloc = std::allocator<node<T> > >
	class tree
	{
		public:
			typedef T												value_type;
			typedef Compare											key_compare;
			typedef Alloc											allocator_type;
			typedef size_t											size_type;
			typedef node<value_type>								node;
			typedef node*											node_ptr;
			typedef ft::tree_iterator<value_type, node>			iterator;
			typedef ft::tree_iterator<const value_type, node>		const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

		protected:
			node_ptr										_root;
			node_ptr										_NIL;
			size_type										_size;
			allocator_type									_alloc;
			key_compare										_comp;

		public:
			tree(const allocator_type &alloc = allocator_type()) : _comp(key_compare())
			{
				_size = 0;
				_alloc = alloc;
				_NIL = _alloc.allocate(1);
				_NIL->parent = _NIL;
				_NIL->right = _NIL;
				_NIL->left = _NIL;
				_NIL->color = BLACK;
				_root = _NIL;
			}

			tree(const tree &copy)
			{
				_alloc = copy._alloc;
				_comp = copy._comp;
				_size = copy._size;
				_NIL = _alloc.allocate(1);
				_NIL->parent = _NIL;
				_NIL->right = _NIL;
				_NIL->left = _NIL;
				_NIL->color = BLACK;

				_root = _NIL;
				_deepCopy(*this, copy._root, copy._NIL);
			}

			~tree(void)
			{
				clear();
				_alloc.deallocate(_NIL, 1);
			}

			tree &operator=(const tree &copy)
			{
				clear();
				_deepCopy(*this, copy._root, copy._NIL);
				return (*this);
			}

			iterator begin(void)
			{
				return iterator(_findMin(_root), _root, _NIL);
			}

			const_iterator begin(void) const
			{
				return const_iterator(_findMin(_root), _root, _NIL);
			}

			iterator end(void)
			{
				return iterator(_NIL, _root, _NIL);
			}

			const_iterator end(void) const
			{
				return const_iterator(_NIL, _root, _NIL);
			}

			reverse_iterator rbegin(void)
			{
				return reverse_iterator(end());
			}

			const_reverse_iterator rbegin(void) const
			{
				return const_reverse_iterator(end());
			}
			reverse_iterator rend(void)
			{
				return reverse_iterator(begin());
			}

			const_reverse_iterator rend(void) const
			{
				return const_reverse_iterator(begin());
			}

			void ft_clear(node_ptr data)
			{
				if (data == NULL)
					return ;
				if (data != _NIL)
				{
					ft_clear(data->left);
					ft_clear(data->right);
					this->_alloc.destroy(data);
					this->_alloc.deallocate(data, 1);
				}
			}

			void clear(void)
			{
				
				ft_clear(this->_root);
				this->_root = this->_NIL;
				this->_size = 0;
			}

			bool empty(void) const
			{
				return (this->size() == 0);
			}

			size_type size(void) const
			{
				return (this->_size);
			}

			size_type max_size(void) const
			{
				return (_alloc.max_size());
			}

			ft::pair<iterator, bool> insert(const value_type &val)
			{
				bool idx = false;
				node_ptr newNode = _newNode(val);
				ft::pair<node_ptr, bool> leaf = ft_insert(this->_root, newNode);
				if (leaf.second)
				{
					if (newNode->parent == _NIL)
						newNode->color = BLACK;
					else
						_insertFix(newNode, newNode);
					idx = true;
					this->_size += 1;
					node_ptr tmp = newNode;
					while (tmp->parent != _NIL)
						tmp = tmp->parent;
					this->_root = tmp;
					return (ft::make_pair(iterator(newNode, _root, _NIL), idx));
				}
				else
				{
					_alloc.destroy(newNode);
					_alloc.deallocate(newNode, 1);
					return (ft::make_pair(iterator(leaf.first, _root, _NIL), false));
				}
			}

			iterator insert(iterator hint, const value_type &value)
			{
				node_ptr n = _NIL;
				node_ptr tmp = _NIL;
				
				tmp = n->parent;
				while (tmp != _NIL && n == tmp->right)
				{
					n = tmp;
					tmp = tmp->parent;
				}
				if (n->right != _NIL)
					this->_root = _findMax(n->right);
				node_ptr next = tmp;
				if (_comp(hint.base()->data, value) && _comp(value, next->data))
				{
					node_ptr newNode = _newNode(value);
					ft::pair<node_ptr, bool> r = ft_insert(hint.base(), newNode);
					this->_size += 1;
					return (iterator(r.first, _root, _NIL));
				}
				return (insert(value).first);
			}

			void erase(iterator position)
			{
				node_ptr tmp = this->_NIL;
				if (position.base() != _NIL)
					_nodeRemove(position.base(), tmp);
			}

			size_type erase(value_type const &key)
			{
				node_ptr toFind = ft_find(key);
				node_ptr tmp = this->_NIL;
				if (toFind)
					return _nodeRemove(toFind, tmp);
				return (0);
			}

			void swap(tree &rhs)
			{
				node_ptr				tmp_NIL = this->_NIL;
				node_ptr				tmp_root = this->_root;
				size_type				tmp_size = this->_size;
				allocator_type			tmp_alloc = this->_alloc;
				key_compare				tmp_comp = this->_comp;
				
				this->_NIL = rhs._NIL;
				this->_root = rhs._root;
				this->_size = rhs._size;
				this->_alloc = rhs._alloc;
				this->_comp = rhs._comp;
				rhs._NIL = tmp_NIL;
				rhs._root = tmp_root;
				rhs._size = tmp_size;
				rhs._alloc = tmp_alloc;
				rhs._comp = tmp_comp;
			}

			node_ptr ft_find(const value_type &val) const
			{
				node_ptr tmp = this->_root;
					
				while (tmp != _NIL)
				{
					if (_comp(tmp->data, val))
						tmp = tmp->right;
					else if (_comp(val, tmp->data))
						tmp = tmp->left;
					else
						return (tmp);
				}
				return (nullptr);
			}

			iterator find(const value_type &k)
			{
				node_ptr key = ft_find(k);
				if (!key)
					return (end());
				else		
					return (iterator(key, this->_root, NULL));
			}

			const_iterator find(const value_type &k) const
			{
				node_ptr key = ft_find(k);
				if (!key)
					return (end());
				else
					return (const_iterator(key, _root, NULL));
			}

			bool count(const value_type &k) const
			{
				if (ft_find(k) != NULL)
					return (1);
				else
					return (0);
			}

			//If all the element in the range compare less than val, the function returns last
			iterator lower_bound(const value_type &k)
			{
				for (iterator it = begin(); it != end(); ++it)
				{
					node_ptr tmp = it.base();
					if ((!_comp(k, tmp->data) && !_comp(tmp->data, k)) || _comp(k, tmp->data))
						return (it);
				}
				return (end());
			}

			const_iterator lower_bound(const value_type &k) const
			{
				for (const_iterator it = begin(); it != end(); ++it)
				{
					node_ptr tmp = it.base();
					if (_comp(k, tmp->data) || (!_comp(k, tmp->data) && !_comp(tmp->data, k)))
						return (it);
				}
				return (end());
			}

			//If no element in the range compares greater than val, the function returns last.
			iterator upper_bound(const value_type &k)
			{
				for (iterator it = begin(); it != end(); ++it)
				{
					node_ptr tmp = it.base();
					if (_comp(k, tmp->data))
						return (it);
				}
				return (end());
			}

			const_iterator upper_bound(const value_type &k) const
			{
				for (const_iterator it = begin(); it != end(); ++it)
				{
					node_ptr tmp = it.base();
					if (_comp(k, tmp->data))
						return (it);
				}
				return (end());
			}

		private:
			//removes a node from a red-black tree.
			int _nodeRemove(node_ptr toFind, node_ptr x)
			{
				//x: A pointer to the node that will replace toFind
				node_ptr y = toFind;
				bool y_color_base = y->color;

				if (toFind->left == _NIL)
					x->parent = check_left(toFind, x);
				else if (toFind->right == _NIL)
					x->parent = check_right(toFind, x);
				else
				{
					y = _findMin(toFind->right);
					x = y->right;
					y_color_base = y->color;
					if (y->parent == toFind)
						x->parent = y;
					else
					{
						check_left(y, x);
						y->right =toFind->right;
						y->right->parent = y;
					}
					if (toFind->parent == _NIL)
						this->_root = y;
					else if (toFind == toFind->parent->left)
						toFind->parent->left = y;
					else
						toFind->parent->right = y;
					y->parent = toFind->parent;
					y->left = toFind->left;
					y->left->parent = y;
					y->color = toFind->color;
				}
				this->_alloc.destroy(toFind);
				this->_alloc.deallocate(toFind, 1);
				this->_size -= 1;
				if (y_color_base == BLACK)
					ft_balanceFix(x, _NIL);
				return (1);
			}

			node_ptr check_left(node_ptr toFind, node_ptr x)
			{
				//If toFind has no left child, x is set to toFind's right child 
				//and its parent is updated to toFind's parent.
				x = toFind->right;
				if (toFind->parent == _NIL)
					this->_root = x;
				else if (toFind == toFind->parent->left)
					toFind->parent->left = x;
				else
					toFind->parent->right = x;
				x->parent = toFind->parent;
				return (x->parent);
			}

			node_ptr check_right(node_ptr toFind, node_ptr x)
			{
				//If toFind has no right child, x is set to toFind's left child and
				//its parent is updated to toFind's parent.
				x = toFind->left;
				if (toFind->parent == _NIL)
					this->_root = x;
				else if (toFind == toFind->parent->left)
					toFind->parent->left = x;
				else
					toFind->parent->right = x;
				x->parent = toFind->parent;
				return (x->parent);
			}


			node_ptr leftFix(node_ptr x,node_ptr s)
			{
				if (s != _NIL && s->color == RED)
				{
					s->color = BLACK;
					x->parent->color = RED;
					_rightRotate(x->parent, NULL);
					s = x->parent->left;
				}
				return (s);
			}

			node_ptr rightFix(node_ptr x,node_ptr s)
			{
				if (s != _NIL && s->color == RED)
				{
					s->color = BLACK;
					x->parent->color = RED;
					_leftRotate(x->parent, NULL);
					s = x->parent->left;
				}
				return (s);
			}

			void ft_balanceFix(node_ptr x, node_ptr y)
			{	
				while (x->color == BLACK && x != this->_root)
				{
					if (x == x->parent->right)
					{
						y = leftFix(x, x->parent->left);
						if (!((y->right->color && y->left->color) == BLACK))
						{
							if (y->left->color == BLACK)
							{
								y->right->color = BLACK;
								y->color = RED;
								_leftRotate(y, NULL);
								y = x->parent->left;
							}
							y->color = x->parent->color;
							y->left->color = BLACK;
							x->parent->color = BLACK;
							_rightRotate(y, NULL);
							x = this->_root;
						}
						else if ((y->right->color && y->left->color) == BLACK)
						{
							y->color = RED;
							x = x->parent;
						}
					}
					else
					{
						y = rightFix(x, x->parent->right);
						if (!((y->right->color && y->left->color) == BLACK))
						{
							if (y->left->color == BLACK)
							{
								y->right->color = BLACK;
								y->color = RED;
								_leftRotate(y, NULL);
								y = x->parent->left;
							}
							y->color = x->parent->color;
							x->parent->color = BLACK;
							y->left->color = BLACK;
							_rightRotate(x->parent, NULL);
							x = this->_root;
						}
						else if ((y->right->color && y->left->color) == BLACK)
						{
							y->color = RED;
							x = x->parent;
						}
					}
				}
				x->color = BLACK;
			}

			node_ptr _findMin(node_ptr root) const
			{
				for (;root->left != _NIL;)
					root = root->left;
				return (root);
			}

			node_ptr _findMax(node_ptr root) const
			{

				for (;root->right != _NIL;)
					root = root->right;
				return (root);
			}

			node_ptr _getRoot(node_ptr n) const
			{
				node_ptr tmp = n;

				while (tmp->parent != _NIL)
					tmp = tmp->parent;
				return (tmp);
			}

			void _deepCopy(tree &tree_dst, node_ptr root_src, node_ptr nil_src)
			{
				if (root_src != nil_src)
				{
					_deepCopy(tree_dst, root_src->left, nil_src);
					tree_dst.insert(root_src->data);
					_deepCopy(tree_dst, root_src->right, nil_src);
				}
			}

			ft::pair<node_ptr, bool> ft_insert(node_ptr root, node_ptr addNode)
			{
				if (root != _NIL && _comp(root->data, addNode->data))
				{
					if (root->right != _NIL)
						return (ft_insert(root->right, addNode));
					else
						root->right = addNode;
				}
				else if (root != _NIL && _comp(addNode->data, root->data))
				{
					if (root->left != _NIL)
						return (ft_insert(root->left, addNode));
					else
						root->left = addNode;
				}
				else if (root != _NIL)
					return (ft::make_pair(root, false));
				addNode->parent = root;
				addNode->color = RED;
				addNode->left = _NIL;
				addNode->right = _NIL;
				return (ft::make_pair(addNode, true));
			}

			node_ptr _newNode(const value_type &val)
			{
				node_ptr newNode = _alloc.allocate(1);
				_alloc.construct(newNode, val);
				newNode->color = RED;
				newNode->left = _NIL;
				newNode->right = _NIL;
				newNode->parent = _NIL;
				return (newNode);
			}

			void _leftRotate(node_ptr root, node_ptr pt)
			{
				node_ptr pt_right = pt->right;

				pt->right = pt_right->left;
				if (pt->right != NULL)
					pt->right->parent = pt;
				pt_right->parent = pt->parent;
				if (pt->parent == NULL)
					root = pt_right;
				else if (pt == pt->parent->left)
					pt->parent->left = pt_right;
				else
					pt->parent->right = pt_right;
				pt_right->left = pt;
				pt->parent = pt_right;
			}

			node_ptr _next(node_ptr n) const
			{
				node_ptr tmp = _NIL;

				if (n->right != _NIL)
					return (_findMin(n->right));
				tmp = n->parent;
				while (tmp != _NIL && n == tmp->right)
				{
					n = tmp;
					tmp = tmp->parent;
				}
				return (tmp);
			}

			void _rightRotate(node_ptr root, node_ptr pt)
			{

				node_ptr pt_left = pt->left;
				pt->left = pt_left->right;

				if (pt->left != NULL)
					pt->left->parent = pt;

				pt_left->parent = pt->parent;

				if (pt->parent == NULL)
					root = pt_left;
				else if (pt == pt->parent->left)
					pt->parent->left = pt_left;
				else
					pt->parent->right = pt_left;

				pt_left->right = pt;
				pt->parent = pt_left;
			}

			/*
			it takes a pointer to the newly inserted node (k) as an input and performs rotations and color changes on the nodes to maintain these properties. The function is executed as long as the parent of the newly inserted node is red, which violates property 4.
			The main logic of the function is inside a while loop:
			If the parent of k is the right child of its grandparent, the function checks the color of the left sibling of k's parent.
			If the left sibling is red, both the parent and the left sibling are colored black, and the grandparent is colored red. k is then updated to its grandparent, and the loop continues.
			If the left sibling is black, the function performs either a left or right rotation and color changes to balance the tree. The specific rotation performed depends on the position of k relative to its parent.
			If the parent of k is the left child of its grandparent, the function performs a similar check and set of operations as in steps 1-3, but now on the right sibling of k's parent.
			The while loop continues until either k becomes the root node or its parent is black. Finally, the root node is colored black to ensure property 2 is satisfied.
			*/
			void _insertFix(node_ptr k, node_ptr y)
			{
				while ((k != y) && (y->color != BLACK) && k->parent->color == RED)
				{
					if (k->parent == k->parent->parent->right)
					{
						y = k->parent->parent->left;
						if (y != NULL && y->color == RED)
						{
							k->parent->color = BLACK;
							y->color = BLACK;
							k->parent->parent->color = RED;
							k = k->parent->parent;
						}
						else
						{
							if (k == k->parent->right)
							{
								k = k->parent;
								_leftRotate(k, y);
							}
							k->parent->color = BLACK;
							k->parent->parent->color = RED;
							_leftRotate(k->parent->parent, y);
						}
					}
					else
					{
						node_ptr y = k->parent->parent->left;
						if (y->color == RED)
						{
							k->parent->color = BLACK;
							y->color = BLACK;
							k->parent->parent->color = RED;
							k = k->parent->parent;
						}
						else
						{
							if (k == k->parent->left)
							{
								_rightRotate(k, y);
								k = k->parent;
							}
							k->parent->color = BLACK;
							k->parent->parent->color = RED;
							_leftRotate(k->parent->parent, y);
						}
					}	
				}
				_root->color = BLACK;
			}
		};
}

#endif
