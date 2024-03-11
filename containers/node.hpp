#ifndef NODE_HPP
# define NODE_HPP

//  --------------------------------NODES---------------------------------
//    * Struct Template
//    A binary tree is made of nodes, where each node contains a "left"
//    reference, a "right" reference, and a data element.
//    The topmost node in the tree is called the root.
//    Every node (excluding a root) in a tree is connected by a directed
//    edge from exactly one other node.
//  ----------------------------------------------------------------------

namespace ft
{
	enum color { BLACK, RED };
	
	template< class value_type>
	struct node
	{
		node			*left;
		node			*right;
		node			*parent;
		bool			color;
		value_type		data;
		
		node(const value_type &src) : color(RED), data(src) 
		{
			this->parent = NULL;
			this->left = NULL;
			this->right = NULL;
		}

		node	&operator=(const node& rhs)
		{
			if (this != rhs)
			{
				this->left = rhs.left;
				this->right = rhs.right;
				this->parent = rhs.parent;
				this->color = rhs.color;
			}
			return (*this);
		}	
	};
}

#endif
