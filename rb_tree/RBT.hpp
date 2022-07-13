/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 20:27:11 by mababou           #+#    #+#             */
/*   Updated: 2022/07/13 15:51:17 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_HPP
#define RBT_HPP

#include <iostream>
#include "../pairs/pair.hpp"

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
	struct RBT_node
	{
		typedef RBT_node *base_ptr;
		typedef const RBT_node *const_base_ptr;

		rb_tree_color color;
		base_ptr parent;
		base_ptr left;
		base_ptr right;
		T value;

		RBT_node(): color(_S_red), parent(NULL), left(NULL), 
						right(NULL), value(T()) {} 
		
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

	static RBT_node *
	local_rb_tree_increment(RBT_node *node_ptr) throw()
	{
		if (node_ptr->right != 0)
		{
			node_ptr = node_ptr->right;
			while (node_ptr->left != 0)
				node_ptr = node_ptr->left;
		}
		else
		{
			RBT_node *tmp_node = node_ptr->parent;
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

	RBT_node *
	rb_tree_increment(RBT_node *node_ptr) throw()
	{
		return local_rb_tree_increment(node_ptr);
	}

	const RBT_node *
	rb_tree_increment(const RBT_node *node_ptr) throw()
	{
		return local_rb_tree_increment(const_cast<RBT_node *>(node_ptr));
	}

	static RBT_node *
	local_rb_tree_decrement(RBT_node *left) throw()
	{
		if (node_ptr->color == _S_red && node_ptr->parent->parent == node_ptr)
			node_ptr = node_ptr->right;
		else if (node_ptr->left != 0)
		{
			RBT_node *tmp_node = node_ptr->left;
			while (tmp_node->right != 0)
				tmp_node = tmp_node->right;
			node_ptr = tmp_node;
		}
		else
		{
			RBT_node *tmp_node = node_ptr->parent;
			while (node_ptr == tmp_node->left)
			{
				node_ptr = tmp_node;
				tmp_node = tmp_node->parent;
			}
			node_ptr = tmp_node;
		}
		return node_ptr;
	}

	RBT_node *
	rb_tree_decrement(RBT_node *node_ptr) throw()
	{
		return local_rb_tree_decrement(node_ptr);
	}

	const RBT_node *
	rb_tree_decrement(const RBT_node *node_ptr) throw()
	{
		return local_rb_tree_decrement(const_cast<RBT_node *>(node_ptr));
	}

	// red-black tree iterator
	template <typename T>
	struct RBT_iterator
	{
		typedef T value_type;
		typedef T &reference;
		typedef T *pointer;

		typedef std::bidirectional_iterator_tag iterator_category;
		typedef std::ptrdiff_t difference_type;

		typedef RBT_iterator<T> iterator;
		typedef RBT_node::base_ptr base_ptr;
		typedef RBT_node<T> *ptr_node;

		base_ptr node_ptr;

		RBT_iterator()
			: node_ptr() {}

		explicit RBT_iterator(base_ptr node_ptr_input)
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
	struct RBT_const_iterator
	{
		typedef T value_type;
		typedef const T &reference;
		typedef const T *pointer;

		typedef RBT_iterator<T> iterator;

		typedef std::bidirectional_iterator_tag iterator_category;
		typedef std::ptrdiff_t difference_type;

		typedef RBT_const_iterator<T> const_iterator;
		typedef RBT_node::const_base_ptr base_ptr;
		typedef const RBT_node<T> *ptr_node;

		base_ptr node_ptr;

		RBT_const_iterator()
			: node_ptr() {}

		explicit RBT_const_iterator(base_ptr node_ptr_input)
			: node_ptr(node_ptr_input) {}

		RBT_const_iterator(const iterator &it)
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
	local_Rb_tree_rotate_left(RBT_node *const x,
							  RBT_node *&root)
	{
		RBT_node *const y = x->right;
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
	local_Rb_tree_rotate_right(RBT_node *const x,
							   RBT_node *&root)
	{
		RBT_node *const y = x->left;
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
								 RBT_node *node_to_insert,
								 RBT_node *node_to_attach_to,
								 RBT_node &tree_root) throw()
	{
		RBT_node *&__root = tree_root.parent;
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
			RBT_node *const grand_father = node_to_insert->parent->parent;
			if (node_to_insert->parent == grand_father->left)
			{
				RBT_node *const uncle = grand_father->right;
				if (uncle && uncle->color == _S_red)
				{
					node_to_insert->parent->color = _S_black;
					uncle->color = _S_black;
					grand_father->color = _S_red;
					node_to_insert = grand_father;
				}
				else
				{
					if (node_to_insert == node_to_insert->parent->right)
					{
						node_to_insert = node_to_insert->parent;
						local_Rb_tree_rotate_left(node_to_insert, __root);
					}
					node_to_insert->parent->color = _S_black;
					grand_father->color = _S_red;
					local_Rb_tree_rotate_right(grand_father, __root);
				}
			}
			else
			{
				RBT_node *const uncle = grand_father->left;
				if (uncle && uncle->color == _S_red)
				{
					node_to_insert->parent->color = _S_black;
					uncle->color = _S_black;
					grand_father->color = _S_red;
					node_to_insert = grand_father;
				}
				else
				{
					if (node_to_insert == node_to_insert->parent->left)
					{
						node_to_insert = node_to_insert->parent;
						local_Rb_tree_rotate_right(node_to_insert, __root);
					}
					node_to_insert->parent->color = _S_black;
					grand_father->color = _S_red;
					local_Rb_tree_rotate_left(grand_father, __root);
				}
			}
		}
		__root->color = _S_black;
	}

	RBT_node *
	Rb_tree_rebalance_for_erase(RBT_node *const node_to_be_deleted,
								RBT_node &tree_root) throw()
	{
		RBT_node *&__root = tree_root.parent;
		RBT_node *&__leftmost = tree_root.left;
		RBT_node *&__rightmost = tree_root.right;
		RBT_node *y = node_to_be_deleted;
		RBT_node *x = 0;
		RBT_node *x_parent = 0;
		if (y->left == 0)		// node_to_be_deleted has at most one non-null child. y == z.
			x = y->right;		// x might be null.
		else if (y->right == 0) // node_to_be_deleted has exactly one non-null child. y == z.
			x = y->left;		// x is not null.
		else
		{
			// node_to_be_deleted has two non-null children.  Set y to
			y = y->right; //   node_to_be_deleted's successor.  x might be null.
			while (y->left != 0)
				y = y->left;
			x = y->right;
		}
		if (y != node_to_be_deleted)
		{
			// relink y in place of z.  y is z's successor
			node_to_be_deleted->left->parent = y;
			y->left = node_to_be_deleted->left;
			if (y != node_to_be_deleted->right)
			{
				x_parent = y->parent;
				if (x)
					x->parent = y->parent;
				y->parent->left = x; // y must be a child of left
				y->right = node_to_be_deleted->right;
				node_to_be_deleted->right->parent = y;
			}
			else
				x_parent = y;
			if (__root == node_to_be_deleted)
				__root = y;
			else if (node_to_be_deleted->parent->left == node_to_be_deleted)
				node_to_be_deleted->parent->left = y;
			else
				node_to_be_deleted->parent->right = y;
			y->parent = node_to_be_deleted->parent;
			std::swap(y->color, node_to_be_deleted->color);
			y = node_to_be_deleted;
			// y now points to node to be actually deleted
		}
		else
		{ // y == node_to_be_deleted
			x_parent = y->parent;
			if (x)
				x->parent = y->parent;
			if (__root == node_to_be_deleted)
				__root = x;
			else if (node_to_be_deleted->parent->left == node_to_be_deleted)
				node_to_be_deleted->parent->left = x;
			else
				node_to_be_deleted->parent->right = x;
			if (__leftmost == node_to_be_deleted)
			{
				if (node_to_be_deleted->right == 0) // node_to_be_deleted->left must be null also
					__leftmost = node_to_be_deleted->parent;
				// makes __leftmost == _M_header if node_to_be_deleted == __root
				else
					__leftmost = RBT_node::_S_minimum(x);
			}
			if (__rightmost == node_to_be_deleted)
			{
				if (node_to_be_deleted->left == 0) // node_to_be_deleted->right must be null also
					__rightmost = node_to_be_deleted->parent;
				// makes __rightmost == _M_header if node_to_be_deleted == __root
				else // x == node_to_be_deleted->left
					__rightmost = RBT_node::_S_maximum(x);
			}
		}
		if (y->color != _S_red)
		{
			while (x != __root && (x == 0 || x->color == _S_black))
				if (x == x_parent->left)
				{
					RBT_node *__w = x_parent->right;
					if (__w->color == _S_red)
					{
						__w->color = _S_black;
						x_parent->color = _S_red;
						local_Rb_tree_rotate_left(x_parent, __root);
						__w = x_parent->right;
					}
					if ((__w->left == 0 ||
						 __w->left->color == _S_black) &&
						(__w->right == 0 ||
						 __w->right->color == _S_black))
					{
						__w->color = _S_red;
						x = x_parent;
						x_parent = x_parent->parent;
					}
					else
					{
						if (__w->right == 0 || __w->right->color == _S_black)
						{
							__w->left->color = _S_black;
							__w->color = _S_red;
							local_Rb_tree_rotate_right(__w, __root);
							__w = x_parent->right;
						}
						__w->color = x_parent->color;
						x_parent->color = _S_black;
						if (__w->right)
							__w->right->color = _S_black;
						local_Rb_tree_rotate_left(x_parent, __root);
						break;
					}
				}
				else
				{
					// same as above, with right <-> left
					RBT_node *__w = x_parent->left;
					if (__w->color == _S_red)
					{
						__w->color = _S_black;
						x_parent->color = _S_red;
						local_Rb_tree_rotate_right(x_parent, __root);
						__w = x_parent->left;
					}
					if ((__w->right == 0 ||
						 __w->right->color == _S_black) &&
						(__w->left == 0 ||
						 __w->left->color == _S_black))
					{
						__w->color = _S_red;
						x = x_parent;
						x_parent = x_parent->parent;
					}
					else
					{
						if (__w->left == 0 || __w->left->color == _S_black)
						{
							__w->right->color = _S_black;
							__w->color = _S_red;
							local_Rb_tree_rotate_left(__w, __root);
							__w = x_parent->left;
						}
						__w->color = x_parent->color;
						x_parent->color = _S_black;
						if (__w->left)
							__w->left->color = _S_black;
						local_Rb_tree_rotate_right(x_parent, __root);
						break;
					}
				}
			if (x)
				x->color = _S_black;
		}
		return y;
	}

	template <
		class Key,
		class T,
		class Compare,
		class Allocator>
	class RBT
	{
	public:
		typedef std::size_t size_type;
		typedef Compare key_compare;
		typedef Allocator pair_allocator;
		typedef Allocator::rebind < RBT_node<pair<const Key, T>>::other node_allocator;
		typedef Key key_type;
		typedef T mapped_type;
		typedef pair<const key_type,mapped_type> value_type;

	private:
		RBT_node<value_type> *_root;
		size_type _node_count;
		pair_allocator _pair_alloc;
		node_allocator _node_alloc;
		key_compare _comp;

	public:
		RBT()
			: _root(0), _node_count(0), _pair_alloc(pair_allocator()),
			_node_alloc(node_allocator()), _comp(key_compare()) {}

		/* ACCESSORS */
		void setAllocator(Allocator alloc)
		{
			_pair_alloc = alloc;
		};
		void setComp(Compare comp)
		{
			_comp = comp;
		}

		/* MODIFIERS */

		// Is called only after checking if key doesn't exist already
		iterator insert_node(const value_type &value)
		{
			RBT_node<value_type> *node_to_insert;
			RBT_node<value_type> *node_to_attach_to;
			
			// prepare the new node
			node_to_insert = _node_alloc.allocate(sizeof(RBT_node<value_type>));
			_node_alloc.construct(node_to_insert, RBT_node<typename value_type>());

			node_to_insert->value = value;

			// search for the node to attach to (the preceding key)
			node_to_attach_to = lower_bound(value.first);

			Rb_tree_insert_and_rebalance(true,
				node_to_insert, node_to_attach_to, _root);

			iterator ret(node_to_insert);

			++_node_count;
			
			return ret;			
		}

		iterator insert_node_loc(iterator pos_to_attach, const value_type &value)
		{
			RBT_node<value_type> *node_to_insert;
			RBT_node<value_type> *node_to_attach_to = pos_to_attach;
			
			// prepare the new node
			node_to_insert = _node_alloc.allocate(sizeof(RBT_node<value_type>));
			_node_alloc.construct(node_to_insert, RBT_node<typename value_type>());

			node_to_insert->value = value;

			Rb_tree_insert_and_rebalance(true,
				node_to_insert, node_to_attach_to, _root);

			iterator ret(node_to_insert);

			++_node_count;
			
			return ret;				
		}

		void erase_node(iterator pos)
		{
			base_ptr	node_to_be_deleted = pos.node_ptr;	
			
			node_to_be_deleted = 
				Rb_tree_rebalance_for_erase(node_to_be_deleted, _root);
			_node_allocator.destroy(node_to_be_deleted);		
			
			--_node_count;
		}

		void swap(RBT & other)
		{
			std::swap(_root, other._root);
			std::swap(_node_count, other._node_count);
			std::swap(_pair_alloc, other._pair_alloc);
			std::swap(_node_alloc, other._node_alloc);
			std::swap(_comp, other._comp);
		}

		typedef RBT_node *base_ptr;
		typedef const RBT_node *const_base_ptr;
		typedef RBT_iterator<T> iterator;
		typedef RBT_const_iterator<T> const_iterator;
		typedef reverse_iterator<iterator> reverse_iterator;
		typedef reverse_iterator<const_iterator> const_reverse_iterator;

		/* ITERATORS */
		iterator begin(void)
		{
			return (RBT_iterator<T>(RBT_node::_S_minimum(_root)));
		}

		const_iterator begin() const
		{
			return RBT_const_iterator<T>(RBT_node::_S_minimum(_root));
		}

		iterator end()
		{
			return RBT_iterator<T>(RBT_node::_S_maximum(_root) + 1);
		}

		const_iterator end() const
		{
			return RBT_const_iterator<T>(RBT_node::_S_maximum(_root) + 1);
		}

		reverse_iterator rbegin(void)
		{
			return RBT_iterator<T>(RBT_node::_S_maximum(_root));
		}

		const_reverse_iterator rbegin() const
		{
			return RBT_const_iterator<T>(RBT_node::_S_maximum(_root));
		}

		reverse_iterator rend()
		{
			return RBT_iterator<T>(RBT_node::_S_minimum(_root) - 1);
		}

		const_reverse_iterator rend() const
		{
			return RBT_const_iterator<T>(RBT_node::_S_minimum(_root) - 1);
		}

		/* CAPACITY */

		bool empty() const
		{
			return _node_count == 0;
		}

		size_type size() const
		{
			return _node_count;
		}

		/* LOOKUP */

		iterator lower_bound(const Key &key)
		{
			iterator it = begin();

			while (it != end())
			{
				if (key == (*it).first)
					break;
				++it;
			}
			return it;
		}

		const_iterator lower_bound(const Key &key) const
		{
			const_iterator it = begin();

			while (it != end())
			{
				if (key == (*it).first)
					break;
				++it;
			}
			return it;
		}

		iterator upper_bound(const Key &key)
		{
			iterator it = begin();

			while (it != end())
			{
				if (key == (*it).first)
				{
					++it;
					break;
				}
				++it;
			}
			return it;
		}

		const_iterator upper_bound(const Key &key)
		{
			const_iterator it = begin();

			while (it != end())
			{
				if (key == (*it).first)
				{
					++it;
					break;
				}
				++it;
			}
			return it;
		}
	}

	

} // namespace ft

#endif /* ********************************************************* RB_TREE_H */