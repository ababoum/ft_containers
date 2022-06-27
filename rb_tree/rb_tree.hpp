/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 20:27:11 by mababou           #+#    #+#             */
/*   Updated: 2022/06/27 12:14:52 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <iostream>

namespace ft
{

	// definition of red and black colors
	enum rb_tree_color
	{
		_S_red = false,
		_S_black = true
	};

	// structure of a node in the tree
	template <typename T>
	struct rb_tree_node
	{
		typedef rb_tree_node *base_ptr;
		typedef const rb_tree_node *const_base_ptr;

		rb_tree_color color;
		base_ptr parent;
		base_ptr left;
		base_ptr right;
		T value;
		size_t node_count;

		static base_ptr
		_S_minimum(base_ptr node_base)
		{
			while (node_base->left != 0)
				node_base = node_base->left;
			return node_base;
		}

		static const_base_ptr
		_S_minimum(const_base_ptr node_base)
		{
			while (node_base->left != 0)
				node_base = node_base->left;
			return node_base;
		}

		static base_ptr
		_S_maximum(base_ptr node_base)
		{
			while (node_base->right != 0)
				node_base = node_base->right;
			return node_base;
		}

		static const_base_ptr
		_S_maximum(const_base_ptr node_base)
		{
			while (node_base->right != 0)
				node_base = node_base->right;
			return node_base;
		}

		T *value_ptr()
		{
			return &(value);
		}

		const T *value_ptr() const
		{
			return &(value);
		}
	};

	// iterator increment/decrement

	static rb_tree_node *
	local_rb_tree_increment(rb_tree_node *node_ptr) throw()
	{
		if (node_ptr->right != 0)
		{
			node_ptr = node_ptr->right;
			while (node_ptr->left != 0)
				node_ptr = node_ptr->left;
		}
		else
		{
			rb_tree_node *tmp_node = node_ptr->parent;
			while (node_ptr == tmp_node->right)
			{
				node_ptr = tmp_node;
				tmp_node = tmp_node->parent;
			}
			if (node_ptr->right != tmp_node)
				node_ptr = tmp_node;
		}
		return node_ptr;
	}

	rb_tree_node *
	rb_tree_increment(rb_tree_node *node_ptr) throw()
	{
		return local_rb_tree_increment(node_ptr);
	}

	const rb_tree_node *
	rb_tree_increment(const rb_tree_node *node_ptr) throw()
	{
		return local_rb_tree_increment(const_cast<rb_tree_node *>(node_ptr));
	}

	static rb_tree_node *
	local_rb_tree_decrement(rb_tree_node *left) throw()
	{
		if (node_ptr->color == _S_red && node_ptr->parent->parent == node_ptr)
			node_ptr = node_ptr->right;
		else if (node_ptr->left != 0)
		{
			rb_tree_node *tmp_node = node_ptr->left;
			while (tmp_node->right != 0)
				tmp_node = tmp_node->right;
			node_ptr = tmp_node;
		}
		else
		{
			rb_tree_node *tmp_node = node_ptr->parent;
			while (node_ptr == tmp_node->left)
			{
				node_ptr = tmp_node;
				tmp_node = tmp_node->parent;
			}
			node_ptr = tmp_node;
		}
		return node_ptr;
	}

	rb_tree_node *
	rb_tree_decrement(rb_tree_node *node_ptr) throw()
	{
		return local_rb_tree_decrement(node_ptr);
	}

	const rb_tree_node *
	rb_tree_decrement(const rb_tree_node *node_ptr) throw()
	{
		return local_rb_tree_decrement(const_cast<rb_tree_node *>(node_ptr));
	}

	// red-black tree iterator
	template <typename T>
	struct rb_tree_iterator
	{
		typedef T value_type;
		typedef T &reference;
		typedef T *pointer;

		typedef std::bidirectional_iterator_tag iterator_category;
		typedef std::ptrdiff_t difference_type;

		typedef rb_tree_iterator<T> iterator;
		typedef rb_tree_node::base_ptr base_ptr;
		typedef rb_tree_node<T> *ptr_node;

		base_ptr node_ptr;

		rb_tree_iterator()
			: node_ptr() {}

		explicit rb_tree_iterator(base_ptr node_ptr_input)
			: node_ptr(node_ptr_input) {}

		reference
		operator*() const
		{
			return *static_cast<ptr_node>(node_ptr)->value_ptr();
		}

		pointer
		operator->() const
		{
			return static_cast<ptr_node>(node_ptr)->value_ptr();
		}

		iterator &
		operator++()
		{
			node_ptr = rb_tree_increment(node_ptr);
			return *this;
		}

		iterator
		operator++(int)
		{
			iterator tmp = *this;
			node_ptr = rb_tree_increment(node_ptr);
			return tmp;
		}

		iterator &
		operator--()
		{
			node_ptr = rb_tree_decrement(node_ptr);
			return *this;
		}

		iterator
		operator--(int)
		{
			iterator tmp = *this;
			node_ptr = rb_tree_decrement(node_ptr);
			return tmp;
		}

		friend bool
		operator==(const iterator &lhs, const iterator &rhs)
		{
			return lhs.node_ptr == rhs.node_ptr;
		}
	};

	// red-black tree const iterator

	template <typename T>
	struct rb_tree_const_iterator
	{
		typedef T value_type;
		typedef const T &reference;
		typedef const T *pointer;

		typedef rb_tree_iterator<T> iterator;

		typedef std::bidirectional_iterator_tag iterator_category;
		typedef std::ptrdiff_t difference_type;

		typedef rb_tree_const_iterator<T> const_iterator;
		typedef rb_tree_node::const_base_ptr base_ptr;
		typedef const rb_tree_node<T> *ptr_node;

		base_ptr node_ptr;

		rb_tree_const_iterator()
			: node_ptr() {}

		explicit rb_tree_const_iterator(base_ptr node_ptr_input)
			: node_ptr(node_ptr_input) {}

		rb_tree_const_iterator(const iterator &it)
			: node_ptr(it.node_ptr) {}

		iterator const_cast() const
		{
			return iterator(const_cast<typename iterator::base_ptr>(node_ptr));
		}

		reference
		operator*() const
		{
			return *static_cast<ptr_node>(node_ptr)->value_ptr();
		}

		pointer
		operator->() const
		{
			return static_cast<ptr_node>(node_ptr)->value_ptr();
		}

		const_iterator &
		operator++()
		{
			node_ptr = rb_tree_increment(node_ptr);
			return *this;
		}

		const_iterator
		operator++(int)
		{
			const_iterator tmp = *this;
			node_ptr = rb_tree_increment(node_ptr);
			return tmp;
		}

		const_iterator &
		operator--()
		{
			node_ptr = rb_tree_decrement(node_ptr);
			return *this;
		}

		const_iterator
		operator--(int)
		{
			const_iterator tmp = *this;
			node_ptr = rb_tree_decrement(node_ptr);
			return tmp;
		}

		friend bool
		operator==(const const_iterator &lhs, const const_iterator &rhs)
		{
			return lhs.node_ptr == rhs.node_ptr;
		}
	};

	// tree rotations (https://www.programiz.com/dsa/red-black-tree)

	static void
	local_Rb_tree_rotate_left(rb_tree_node *const x,
							  rb_tree_node *&root)
	{
		rb_tree_node *const y = x->right;
		x->right = y->left;
		if (y->left != 0)
			y->left->parent = x;
		y->parent = x->_M_parent;
		if (x == root)
			root = y;
		else if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
		y->left = x;
		x->parent = y;
	}

	static void
	local_Rb_tree_rotate_right(rb_tree_node *const x,
							   rb_tree_node *&root)
	{
		rb_tree_node *const y = x->left;
		x->left = y->right;
		if (y->right != 0)
			y->right->parent = x;
		y->parent = x->_M_parent;
		if (x == root)
			root = y;
		else if (x == x->parent->right)
			x->parent->right = y;
		else
			x->parent->left = y;
		y->right = x;
		x->parent = y;
	}

	// insertion / deletion functions declaration

	void
	Rb_tree_insert_and_rebalance(const bool insert_left,
								  rb_tree_node *node_to_insert,
								  rb_tree_node *node_to_attach_to,
								  rb_tree_node &tree_root) throw()
	{
		_Rb_tree_node_base *&__root = tree_root.parent;
		// Initialize fields in new node to insert.
		node_to_insert->parent = node_to_attach_to;
		node_to_insert->left = 0;
		node_to_insert->right = 0;
		node_to_insert->color = _S_red;
		// Insert.
		// Make new node child of parent and maintain root, leftmost and rightmost nodes.
		// N.B. First node is always inserted left.
		if (insert_left)
		{
			node_to_attach_to->left = node_to_insert; // also makes leftmost = node_to_insert when node_to_attach_to == &tree_root
			if (node_to_attach_to == &tree_root)
			{
				tree_root.parent = node_to_insert;
				tree_root.right = node_to_insert;
			}
			else if (node_to_attach_to == tree_root.left)
				tree_root.left = node_to_insert; // maintain leftmost pointing to min node
		}
		else
		{
			node_to_attach_to->right = node_to_insert;
			if (node_to_attach_to == tree_root.right)
				tree_root.right = node_to_insert; // maintain rightmost pointing to max node
		}
		// Rebalance
		while (node_to_insert != __root && node_to_insert->parent->color == _S_red)
		{
			_Rb_tree_node_base *const __xpp = node_to_insert->parent->parent;
			if (node_to_insert->parent == __xpp->left)
			{
				_Rb_tree_node_base *const __y = __xpp->right;
				if (__y && __y->color == _S_red)
				{
					node_to_insert->parent->color = _S_black;
					__y->color = _S_black;
					__xpp->color = _S_red;
					node_to_insert = __xpp;
				}
				else
				{
					if (node_to_insert == node_to_insert->parent->right)
					{
						node_to_insert = node_to_insert->parent;
						local_Rb_tree_rotate_left(node_to_insert, __root);
					}
					node_to_insert->parent->color = _S_black;
					__xpp->color = _S_red;
					local_Rb_tree_rotate_right(__xpp, __root);
				}
			}
			else
			{
				_Rb_tree_node_base *const __y = __xpp->left;
				if (__y && __y->color == _S_red)
				{
					node_to_insert->parent->color = _S_black;
					__y->color = _S_black;
					__xpp->color = _S_red;
					node_to_insert = __xpp;
				}
				else
				{
					if (node_to_insert == node_to_insert->parent->left)
					{
						node_to_insert = node_to_insert->parent;
						local_Rb_tree_rotate_right(node_to_insert, __root);
					}
					node_to_insert->parent->color = _S_black;
					__xpp->color = _S_red;
					local_Rb_tree_rotate_left(__xpp, __root);
				}
			}
		}
		__root->color = _S_black;
	}
	
	_Rb_tree_node_base *
	_Rb_tree_rebalance_for_erase(_Rb_tree_node_base *const __z,
								 _Rb_tree_node_base &tree_root) throw()
	{
		_Rb_tree_node_base *&__root = tree_root.parent;
		_Rb_tree_node_base *&__leftmost = tree_root.left;
		_Rb_tree_node_base *&__rightmost = tree_root.right;
		_Rb_tree_node_base *__y = __z;
		_Rb_tree_node_base *node_to_insert = 0;
		_Rb_tree_node_base *__x_parent = 0;
		if (__y->left == 0)		  // __z has at most one non-null child. y == z.
			node_to_insert = __y->right;	  // node_to_insert might be null.
		else if (__y->right == 0) // __z has exactly one non-null child. y == z.
			node_to_insert = __y->left;	  // node_to_insert is not null.
		else
		{
			// __z has two non-null children.  Set __y to
			__y = __y->right; //   __z's successor.  node_to_insert might be null.
			while (__y->left != 0)
				__y = __y->left;
			node_to_insert = __y->right;
		}
		if (__y != __z)
		{
			// relink y in place of z.  y is z's successor
			__z->left->parent = __y;
			__y->left = __z->left;
			if (__y != __z->right)
			{
				__x_parent = __y->parent;
				if (node_to_insert)
					node_to_insert->parent = __y->parent;
				__y->parent->left = node_to_insert; // __y must be a child of left
				__y->right = __z->right;
				__z->right->parent = __y;
			}
			else
				__x_parent = __y;
			if (__root == __z)
				__root = __y;
			else if (__z->parent->left == __z)
				__z->parent->left = __y;
			else
				__z->parent->right = __y;
			__y->parent = __z->parent;
			std::swap(__y->color, __z->color);
			__y = __z;
			// __y now points to node to be actually deleted
		}
		else
		{ // __y == __z
			__x_parent = __y->parent;
			if (node_to_insert)
				node_to_insert->parent = __y->parent;
			if (__root == __z)
				__root = node_to_insert;
			else if (__z->parent->left == __z)
				__z->parent->left = node_to_insert;
			else
				__z->parent->right = node_to_insert;
			if (__leftmost == __z)
			{
				if (__z->right == 0) // __z->left must be null also
					__leftmost = __z->parent;
				// makes __leftmost == _M_header if __z == __root
				else
					__leftmost = _Rb_tree_node_base::_S_minimum(node_to_insert);
			}
			if (__rightmost == __z)
			{
				if (__z->left == 0) // __z->right must be null also
					__rightmost = __z->parent;
				// makes __rightmost == _M_header if __z == __root
				else // node_to_insert == __z->left
					__rightmost = _Rb_tree_node_base::_S_maximum(node_to_insert);
			}
		}
		if (__y->color != _S_red)
		{
			while (node_to_insert != __root && (node_to_insert == 0 || node_to_insert->color == _S_black))
				if (node_to_insert == __x_parent->left)
				{
					_Rb_tree_node_base *__w = __x_parent->right;
					if (__w->color == _S_red)
					{
						__w->color = _S_black;
						__x_parent->color = _S_red;
						local_Rb_tree_rotate_left(__x_parent, __root);
						__w = __x_parent->right;
					}
					if ((__w->left == 0 ||
						 __w->left->color == _S_black) &&
						(__w->right == 0 ||
						 __w->right->color == _S_black))
					{
						__w->color = _S_red;
						node_to_insert = __x_parent;
						__x_parent = __x_parent->parent;
					}
					else
					{
						if (__w->right == 0 || __w->right->color == _S_black)
						{
							__w->left->color = _S_black;
							__w->color = _S_red;
							local_Rb_tree_rotate_right(__w, __root);
							__w = __x_parent->right;
						}
						__w->color = __x_parent->color;
						__x_parent->color = _S_black;
						if (__w->right)
							__w->right->color = _S_black;
						local_Rb_tree_rotate_left(__x_parent, __root);
						break;
					}
				}
				else
				{
					// same as above, with right <-> left.
					_Rb_tree_node_base *__w = __x_parent->left;
					if (__w->color == _S_red)
					{
						__w->color = _S_black;
						__x_parent->color = _S_red;
						local_Rb_tree_rotate_right(__x_parent, __root);
						__w = __x_parent->left;
					}
					if ((__w->right == 0 ||
						 __w->right->color == _S_black) &&
						(__w->left == 0 ||
						 __w->left->color == _S_black))
					{
						__w->color = _S_red;
						node_to_insert = __x_parent;
						__x_parent = __x_parent->parent;
					}
					else
					{
						if (__w->left == 0 || __w->left->color == _S_black)
						{
							__w->right->color = _S_black;
							__w->color = _S_red;
							local_Rb_tree_rotate_left(__w, __root);
							__w = __x_parent->left;
						}
						__w->color = __x_parent->color;
						__x_parent->color = _S_black;
						if (__w->left)
							__w->left->color = _S_black;
						local_Rb_tree_rotate_right(__x_parent, __root);
						break;
					}
				}
			if (node_to_insert)
				node_to_insert->color = _S_black;
		}
		return __y;
	}

} // namespace ft

#endif /* ********************************************************* RB_TREE_H */