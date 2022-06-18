/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 20:27:11 by mababou           #+#    #+#             */
/*   Updated: 2022/06/18 18:19:03 by mababou          ###   ########.fr       */
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

	// structure of a node in the tree (without value)
	struct rb_tree_node_base
	{
		typedef rb_tree_node_base *base_ptr;
		typedef const rb_tree_node_base *const_base_ptr;

		rb_tree_color color;
		base_ptr parent;
		base_ptr left;
		base_ptr right;

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
	};

	// Helper to guarantee default value of nodes comparison
	template <typename key>
	struct rb_tree_key_compare
	{
		key key_compare;

		rb_tree_key_compare()
			: key_compare() {}

		rb_tree_key_compare(const key &comp)
			: key_compare(comp) {}
	};

	// Helper type to manage default initialization of node count and header
	struct rb_tree_header
	{
		rb_tree_node_base _M_header;
		size_t node_count;

		rb_tree_header()
		{
			_M_header.color = _S_red;
			_M_reset();
		}

		void
		_M_move_data(rb_tree_header &__from)
		{
			_M_header.color = __from._M_header.color;
			_M_header.parent = __from._M_header.parent;
			_M_header.left = __from._M_header.left;
			_M_header.right = __from._M_header.right;
			_M_header.parent->parent = &_M_header;
			node_count = __from.node_count;
			__from._M_reset();
		}
		void
		_M_reset()
		{
			_M_header.parent = 0;
			_M_header.left = &_M_header;
			_M_header.right = &_M_header;
			node_count = 0;
		}
	};

	// Node with value

	template <typename T>
	struct rb_tree_node : public rb_tree_node_base
	{
		typedef rb_tree_node<T> *link_type;

		T value;

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

	static rb_tree_node_base *
	local_rb_tree_increment(rb_tree_node_base *node_ptr) throw()
	{
		if (node_ptr->right != 0)
		{
			node_ptr = node_ptr->right;
			while (node_ptr->left != 0)
				node_ptr = node_ptr->left;
		}
		else
		{
			rb_tree_node_base *__y = node_ptr->parent;
			while (node_ptr == __y->right)
			{
				node_ptr = __y;
				__y = __y->parent;
			}
			if (node_ptr->right != __y)
				node_ptr = __y;
		}
		return node_ptr;
	}

	rb_tree_node_base *
	rb_tree_increment(rb_tree_node_base *node_ptr) throw()
	{
		return local_rb_tree_increment(node_ptr);
	}

	const rb_tree_node_base *
	rb_tree_increment(const rb_tree_node_base *node_ptr) throw()
	{
		return local_rb_tree_increment(const_cast<rb_tree_node_base *>(node_ptr));
	}

	static rb_tree_node_base *
	local_rb_tree_decrement(rb_tree_node_base *left) throw()
	{
		if (node_ptr->color == _S_red && node_ptr->parent->parent == node_ptr)
			node_ptr = node_ptr->right;
		else if (node_ptr->left != 0)
		{
			rb_tree_node_base *__y = node_ptr->left;
			while (__y->right != 0)
				__y = __y->right;
			node_ptr = __y;
		}
		else
		{
			rb_tree_node_base *__y = node_ptr->parent;
			while (node_ptr == __y->left)
			{
				node_ptr = __y;
				__y = __y->parent;
			}
			node_ptr = __y;
		}
		return node_ptr;
	}

	rb_tree_node_base *
	rb_tree_decrement(rb_tree_node_base *node_ptr) throw()
	{
		return local_rb_tree_decrement(node_ptr);
	}

	const rb_tree_node_base *
	rb_tree_decrement(const rb_tree_node_base *node_ptr) throw()
	{
		return local_rb_tree_decrement(const_cast<rb_tree_node_base *>(node_ptr));
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
		typedef rb_tree_node_base::base_ptr base_ptr;
		typedef rb_tree_node<T> *link_type;

		base_ptr node_ptr;

		rb_tree_iterator()
			: node_ptr() {}

		explicit rb_tree_iterator(base_ptr node_ptr_input)
			: node_ptr(node_ptr_input) {}

		reference
		operator*() const
		{
			return *static_cast<link_type>(node_ptr)->value_ptr();
		}

		pointer
		operator->() const
		{
			return static_cast<link_type>(node_ptr)->value_ptr();
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
		operator==(const iterator &node_ptr, const iterator &__y)
		{
			return node_ptr.node_ptr == __y.node_ptr;
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
		typedef rb_tree_node_base::const_base_ptr base_ptr;
		typedef const rb_tree_node<T> *link_type;

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
			return *static_cast<link_type>(node_ptr)->value_ptr();
		}

		pointer
		operator->() const
		{
			return static_cast<link_type>(node_ptr)->value_ptr();
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

	// tree rotations

	static void
	local_Rb_tree_rotate_left(_Rb_tree_node_base *const __x,
							  _Rb_tree_node_base *&__root)
	{
		_Rb_tree_node_base *const __y = __x->right;
		__x->right = __y->left;
		if (__y->left != 0)
			__y->left->parent = __x;
		__y->parent = __x->_M_parent;
		if (__x == __root)
			__root = __y;
		else if (__x == __x->parent->left)
			__x->parent->left = __y;
		else
			__x->parent->right = __y;
		__y->left = __x;
		__x->parent = __y;
	}

	static void
	local_Rb_tree_rotate_right(_Rb_tree_node_base *const __x,
							   _Rb_tree_node_base *&__root)
	{
		_Rb_tree_node_base *const __y = __x->left;
		__x->left = __y->right;
		if (__y->right != 0)
			__y->right->parent = __x;
		__y->parent = __x->_M_parent;
		if (__x == __root)
			__root = __y;
		else if (__x == __x->parent->right)
			__x->parent->right = __y;
		else
			__x->parent->left = __y;
		__y->right = __x;
		__x->parent = __y;
	}

	// insertion / deletion functions declaration

	void
	_Rb_tree_insert_and_rebalance(const bool __insert_left,
								  _Rb_tree_node_base *__x,
								  _Rb_tree_node_base *__p,
								  _Rb_tree_node_base &__header) throw()
	{
		_Rb_tree_node_base *&__root = __header.parent;
		// Initialize fields in new node to insert.
		__x->parent = __p;
		__x->left = 0;
		__x->right = 0;
		__x->color = _S_red;
		// Insert.
		// Make new node child of parent and maintain root, leftmost and
		// rightmost nodes.
		// N.B. First node is always inserted left.
		if (__insert_left)
		{
			__p->left = __x; // also makes leftmost = __x when __p == &__header
			if (__p == &__header)
			{
				__header.parent = __x;
				__header.right = __x;
			}
			else if (__p == __header.left)
				__header.left = __x; // maintain leftmost pointing to min node
		}
		else
		{
			__p->right = __x;
			if (__p == __header.right)
				__header.right = __x; // maintain rightmost pointing to max node
		}
		// Rebalance.
		while (__x != __root && __x->parent->color == _S_red)
		{
			_Rb_tree_node_base *const __xpp = __x->parent->parent;
			if (__x->parent == __xpp->left)
			{
				_Rb_tree_node_base *const __y = __xpp->right;
				if (__y && __y->color == _S_red)
				{
					__x->parent->color = _S_black;
					__y->color = _S_black;
					__xpp->color = _S_red;
					__x = __xpp;
				}
				else
				{
					if (__x == __x->parent->right)
					{
						__x = __x->parent;
						local_Rb_tree_rotate_left(__x, __root);
					}
					__x->parent->color = _S_black;
					__xpp->color = _S_red;
					local_Rb_tree_rotate_right(__xpp, __root);
				}
			}
			else
			{
				_Rb_tree_node_base *const __y = __xpp->left;
				if (__y && __y->color == _S_red)
				{
					__x->parent->color = _S_black;
					__y->color = _S_black;
					__xpp->color = _S_red;
					__x = __xpp;
				}
				else
				{
					if (__x == __x->parent->left)
					{
						__x = __x->parent;
						local_Rb_tree_rotate_right(__x, __root);
					}
					__x->parent->color = _S_black;
					__xpp->color = _S_red;
					local_Rb_tree_rotate_left(__xpp, __root);
				}
			}
		}
		__root->color = _S_black;
	}
	_Rb_tree_node_base *
	_Rb_tree_rebalance_for_erase(_Rb_tree_node_base *const __z,
								 _Rb_tree_node_base &__header) throw()
	{
		_Rb_tree_node_base *&__root = __header.parent;
		_Rb_tree_node_base *&__leftmost = __header.left;
		_Rb_tree_node_base *&__rightmost = __header.right;
		_Rb_tree_node_base *__y = __z;
		_Rb_tree_node_base *__x = 0;
		_Rb_tree_node_base *__x_parent = 0;
		if (__y->left == 0)		  // __z has at most one non-null child. y == z.
			__x = __y->right;	  // __x might be null.
		else if (__y->right == 0) // __z has exactly one non-null child. y == z.
			__x = __y->left;	  // __x is not null.
		else
		{
			// __z has two non-null children.  Set __y to
			__y = __y->right; //   __z's successor.  __x might be null.
			while (__y->left != 0)
				__y = __y->left;
			__x = __y->right;
		}
		if (__y != __z)
		{
			// relink y in place of z.  y is z's successor
			__z->left->parent = __y;
			__y->left = __z->left;
			if (__y != __z->right)
			{
				__x_parent = __y->parent;
				if (__x)
					__x->parent = __y->parent;
				__y->parent->left = __x; // __y must be a child of left
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
			if (__x)
				__x->parent = __y->parent;
			if (__root == __z)
				__root = __x;
			else if (__z->parent->left == __z)
				__z->parent->left = __x;
			else
				__z->parent->right = __x;
			if (__leftmost == __z)
			{
				if (__z->right == 0) // __z->left must be null also
					__leftmost = __z->parent;
				// makes __leftmost == _M_header if __z == __root
				else
					__leftmost = _Rb_tree_node_base::_S_minimum(__x);
			}
			if (__rightmost == __z)
			{
				if (__z->left == 0) // __z->right must be null also
					__rightmost = __z->parent;
				// makes __rightmost == _M_header if __z == __root
				else // __x == __z->left
					__rightmost = _Rb_tree_node_base::_S_maximum(__x);
			}
		}
		if (__y->color != _S_red)
		{
			while (__x != __root && (__x == 0 || __x->color == _S_black))
				if (__x == __x_parent->left)
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
						__x = __x_parent;
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
						__x = __x_parent;
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
			if (__x)
				__x->color = _S_black;
		}
		return __y;
	}

	// Red-black tree

	template <typename key, typename val, typename keyOfValue,
			  typename compare, typename alloc = std::allocator<val>>
	class rb_tree
	{
		typedef typename __gnu_cxx::__alloc_traits<alloc>::template rebind<rb_tree_node<val>>::other _Node_allocator;

		typedef __gnu_cxx::__alloc_traits<_Node_allocator> alloc_traits;

	protected:
		typedef rb_tree_node_base *base_ptr;
		typedef const rb_tree_node_base *const_base_ptr;
		typedef rb_tree_node<val> *link_type;
		typedef const rb_tree_node<val> *const_link_type;

	private:
		// Functor recycling a pool of nodes and using allocation once the pool
		// is empty.
		struct reuse_or_alloc_node
		{
			reuse_or_alloc_node(rb_tree &__t)
				: _M_root(__t._M_root()), _M_nodes(__t.rightmost()), _M_t(__t)
			{
				if (_M_root)
				{
					_M_root->parent = 0;

					if (_M_nodes->left)
						_M_nodes = _M_nodes->left;
				}
				else
					_M_nodes = 0;
			}

			~reuse_or_alloc_node()
			{
				_M_t._M_erase(static_cast<link_type>(_M_root));
			}

			template <typename _Arg>
			link_type
			operator()(const _Arg &__arg)
			{
				link_type __node = static_cast<link_type>(_M_extract());
				if (__node)
				{
					_M_t._M_destroy_node(__node);
					_M_t._M_construct_node(__node, _GLIBCXX_FORWARD(_Arg, __arg));
					return __node;
				}

				return _M_t._M_create_node(_GLIBCXX_FORWARD(_Arg, __arg));
			}

		private:
			base_ptr
			_M_extract()
			{
				if (!_M_nodes)
					return _M_nodes;

				base_ptr __node = _M_nodes;
				_M_nodes = _M_nodes->parent;
				if (_M_nodes)
				{
					if (_M_nodes->right == __node)
					{
						_M_nodes->right = 0;

						if (_M_nodes->left)
						{
							_M_nodes = _M_nodes->left;

							while (_M_nodes->right)
								_M_nodes = _M_nodes->right;

							if (_M_nodes->left)
								_M_nodes = _M_nodes->left;
						}
					}
					else // __node is on the left.
						_M_nodes->left = 0;
				}
				else
					_M_root = 0;

				return __node;
			}

			base_ptr _M_root;
			base_ptr _M_nodes;
			rb_tree &_M_t;
		};

		// Functor similar to the previous one but without any pool of nodes to
		// recycle.
		struct alloc_node
		{
			alloc_node(rb_tree &__t)
				: _M_t(__t) {}

			template <typename _Arg>
			link_type
			operator()(const _Arg &__arg) const
			{
				return _M_t._M_create_node(_GLIBCXX_FORWARD(_Arg, __arg));
			}

		private:
			rb_tree &_M_t;
		};

	public:
		typedef key key_type;
		typedef val value_type;
		typedef value_type *pointer;
		typedef const value_type *const_pointer;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef alloc allocator_type;

		_Node_allocator &
		_M_get_Node_allocator()
		{
			return this->_M_impl;
		}

		const _Node_allocator &
		_M_get_Node_allocator() const
		{
			return this->_M_impl;
		}

		allocator_type
		get_allocator() const
		{
			return allocator_type(_M_get_Node_allocator());
		}

	protected:
		link_type
		_M_get_node()
		{
			return alloc_traits::allocate(_M_get_Node_allocator(), 1);
		}

		void
		_M_put_node(link_type __p)
		{
			alloc_traits::deallocate(_M_get_Node_allocator(), __p, 1);
		}

		void
		_M_construct_node(link_type __node, const value_type &__x)
		{
			__try
			{
				get_allocator().construct(__node->value_ptr(), __x);
			}
			__catch(...)
			{
				_M_put_node(__node);
				__throw_exception_again;
			}
		}

		link_type
		_M_create_node(const value_type &__x)
		{
			link_type tmp = _M_get_node();
			_M_construct_node(tmp, __x);
			return tmp;
		}

		void
		_M_destroy_node(link_type __p)
		{
			get_allocator().destroy(__p->value_ptr());
		}

		void
		_M_drop_node(link_type __p)
		{
			_M_destroy_node(__p);
			_M_put_node(__p);
		}

		template <typename _NodeGen>
		link_type
		_M_clone_node(const_link_type __x, _NodeGen &__node_gen)
		{
			link_type tmp = __node_gen(*__x->value_ptr());
			tmp->color = __x->color;
			tmp->left = 0;
			tmp->right = 0;
			return tmp;
		}

	protected:
		template <typename key_compare>
		struct _Rb_tree_impl
			: public _Node_allocator,
			  public _Rb_tree_key_compare<key_compare>,
			  public rb_tree_header
		{
			typedef _Rb_tree_key_compare<key_compare> _Base_key_compare;

			_Rb_tree_impl()
				: _Node_allocator() {}

			_Rb_tree_impl(const _Rb_tree_impl &__x)
				: _Node_allocator(alloc_traits::_S_select_on_copy(__x)), _Base_key_compare(__x._M_key_compare) {}

			_Rb_tree_impl(const key_compare &__comp, const _Node_allocator &__a)
				: _Node_allocator(__a), _Base_key_compare(__comp) {}
		};

		_Rb_tree_impl<compare> _M_impl;

	protected:
		base_ptr &
		_M_root()
		{
			return this->_M_impl._M_header.parent;
		}

		const_base_ptr
		_M_root() const
		{
			return this->_M_impl._M_header.parent;
		}

		base_ptr &
		leftmost()
		{
			return this->_M_impl._M_header.left;
		}

		const_base_ptr
		leftmost() const
		{
			return this->_M_impl._M_header.left;
		}

		base_ptr &
		rightmost()
		{
			return this->_M_impl._M_header.right;
		}

		const_base_ptr
		rightmost() const
		{
			return this->_M_impl._M_header.right;
		}

		link_type
		_M_begin()
		{
			return static_cast<link_type>(this->_M_impl._M_header.parent);
		}

		const_link_type
		_M_begin() const
		{
			return static_cast<const_link_type>(this->_M_impl._M_header.parent);
		}

		base_ptr
		_M_end()
		{
			return &this->_M_impl._M_header;
		}

		const_base_ptr
		_M_end() const
		{
			return &this->_M_impl._M_header;
		}

		static const key &
		_S_key(const_link_type __x)
		{
			return keyOfValue()(*__x->value_ptr());
		}

		static link_type
		_S_left(base_ptr __x)
		{
			return static_cast<link_type>(__x->left);
		}

		static const_link_type
		_S_left(const_base_ptr __x)
		{
			return static_cast<const_link_type>(__x->left);
		}

		static link_type
		_S_right(base_ptr __x)
		{
			return static_cast<link_type>(__x->right);
		}

		static const_link_type
		_S_right(const_base_ptr __x)
		{
			return static_cast<const_link_type>(__x->right);
		}

		static const key &
		_S_key(const_base_ptr __x)
		{
			return _S_key(static_cast<const_link_type>(__x));
		}

		static base_ptr
		_S_minimum(base_ptr __x)
		{
			return rb_tree_node_base::_S_minimum(__x);
		}

		static const_base_ptr
		_S_minimum(const_base_ptr __x)
		{
			return rb_tree_node_base::_S_minimum(__x);
		}

		static base_ptr
		_S_maximum(base_ptr __x)
		{
			return rb_tree_node_base::_S_maximum(__x);
		}

		static const_base_ptr
		_S_maximum(const_base_ptr __x)
		{
			return rb_tree_node_base::_S_maximum(__x);
		}

	public:
		typedef rb_tree_iterator<value_type> iterator;
		typedef rb_tree_const_iterator<value_type> const_iterator;

		typedef reverse_iterator<iterator> reverse_iterator;
		typedef reverse_iterator<const_iterator> const_reverse_iterator;

		pair<base_ptr, base_ptr>
		_M_get_insert_unique_pos(const key_type &__k);

		pair<base_ptr, base_ptr>
		_M_get_insert_equal_pos(const key_type &__k);

		pair<base_ptr, base_ptr>
		_M_get_insert_hint_unique_pos(const_iterator __pos,
									  const key_type &__k);

		pair<base_ptr, base_ptr>
		_M_get_insert_hint_equal_pos(const_iterator __pos,
									 const key_type &__k);

	private:
		template <typename _NodeGen>
		iterator
		_M_insert_(base_ptr __x, base_ptr __y,
				   const value_type &__v, _NodeGen &);

		// _GLIBCXX_RESOLVE_LIB_DEFECTS
		// 233. Insertion hints in associative containers.
		iterator
		_M_insert_lower(base_ptr __y, const value_type &__v);

		iterator
		_M_insert_equal_lower(const value_type &__x);

		template <typename _NodeGen>
		link_type
		_M_copy(const_link_type __x, base_ptr __p, _NodeGen &);

		template <typename _NodeGen>
		link_type
		_M_copy(const rb_tree &__x, _NodeGen &__gen)
		{
			link_type __root = _M_copy(__x._M_begin(), _M_end(), __gen);
			leftmost() = _S_minimum(__root);
			rightmost() = _S_maximum(__root);
			_M_impl.node_count = __x._M_impl.node_count;
			return __root;
		}

		link_type
		_M_copy(const rb_tree &__x)
		{
			alloc_node __an(*this);
			return _M_copy(__x, __an);
		}

		void
		_M_erase(link_type __x);

		iterator
		_M_lower_bound(link_type __x, base_ptr __y,
					   const key &__k);

		const_iterator
		_M_lower_bound(const_link_type __x, const_base_ptr __y,
					   const key &__k) const;

		iterator
		_M_upper_bound(link_type __x, base_ptr __y,
					   const key &__k);

		const_iterator
		_M_upper_bound(const_link_type __x, const_base_ptr __y,
					   const key &__k) const;

	public:
		// allocation/deallocation
		rb_tree() {}

		rb_tree(const compare &__comp,
				const allocator_type &__a = allocator_type())
			: _M_impl(__comp, _Node_allocator(__a)) {}

		rb_tree(const rb_tree &__x)
			: _M_impl(__x._M_impl)
		{
			if (__x._M_root() != 0)
				_M_root() = _M_copy(__x);
		}

		~rb_tree()
		{
			_M_erase(_M_begin());
		}

		rb_tree &
		operator=(const rb_tree &__x);

		// Accessors.
		compare
		key_comp() const
		{
			return _M_impl._M_key_compare;
		}

		iterator
		begin()
		{
			return iterator(this->_M_impl._M_header.left);
		}

		const_iterator
		begin() const
		{
			return const_iterator(this->_M_impl._M_header.left);
		}

		iterator
		end()
		{
			return iterator(&this->_M_impl._M_header);
		}

		const_iterator
		end() const
		{
			return const_iterator(&this->_M_impl._M_header);
		}

		reverse_iterator
		rbegin()
		{
			return reverse_iterator(end());
		}

		const_reverse_iterator
		rbegin() const
		{
			return const_reverse_iterator(end());
		}

		reverse_iterator
		rend()
		{
			return reverse_iterator(begin());
		}

		const_reverse_iterator
		rend() const
		{
			return const_reverse_iterator(begin());
		}

		bool
		empty() const
		{
			return _M_impl.node_count == 0;
		}

		size_type
		size() const
		{
			return _M_impl.node_count;
		}

		size_type
		max_size() const
		{
			return alloc_traits::max_size(_M_get_Node_allocator());
		}

		void
		swap(rb_tree &__t)
			_IF(__is_nothrow_swappable<compare>::value);

		// Insert/erase.
		pair<iterator, bool>
		_M_insert_unique(const value_type &__x);

		iterator
		_M_insert_equal(const value_type &__x);

		template <typename _NodeGen>
		iterator
		_M_insert_unique_(const_iterator __pos, const value_type &__x,
						  _NodeGen &);

		iterator
		_M_insert_unique_(const_iterator __pos, const value_type &__x)
		{
			alloc_node __an(*this);
			return _M_insert_unique_(__pos, __x, __an);
		}

		template <typename _NodeGen>
		iterator
		_M_insert_equal_(const_iterator __pos, const value_type &__x,
						 _NodeGen &);
		iterator
		_M_insert_equal_(const_iterator __pos, const value_type &__x)
		{
			alloc_node __an(*this);
			return _M_insert_equal_(__pos, __x, __an);
		}

		template <typename _InputIterator>
		void
		_M_insert_range_unique(_InputIterator __first, _InputIterator __last)
		{
			alloc_node __an(*this);
			for (; __first != __last; ++__first)
				_M_insert_unique_(end(), *__first, __an);
		}

		template <typename _InputIterator>
		void
		_M_insert_range_equal(_InputIterator __first, _InputIterator __last)
		{
			alloc_node __an(*this);
			for (; __first != __last; ++__first)
				_M_insert_equal_(end(), *__first, __an);
		}

	private:
		void
		_M_erase_aux(const_iterator __position);

		void
		_M_erase_aux(const_iterator __first, const_iterator __last);

	public:
		void
		erase(iterator __position)
		{
			__glibcxx_assert(__position != end());
			_M_erase_aux(__position);
		}

		void
		erase(const_iterator __position)
		{
			__glibcxx_assert(__position != end());
			_M_erase_aux(__position);
		}

		size_type
		erase(const key_type &__x);

		void
		erase(iterator __first, iterator __last)
		{
			_M_erase_aux(__first, __last);
		}

		void
		erase(const_iterator __first, const_iterator __last)
		{
			_M_erase_aux(__first, __last);
		}

		void
		clear()
		{
			_M_erase(_M_begin());
			_M_impl._M_reset();
		}

		// Set operations.
		iterator
		find(const key_type &__k);

		const_iterator
		find(const key_type &__k) const;

		size_type
		count(const key_type &__k) const;

		iterator
		lower_bound(const key_type &__k)
		{
			return _M_lower_bound(_M_begin(), _M_end(), __k);
		}

		const_iterator
		lower_bound(const key_type &__k) const
		{
			return _M_lower_bound(_M_begin(), _M_end(), __k);
		}

		iterator
		upper_bound(const key_type &__k)
		{
			return _M_upper_bound(_M_begin(), _M_end(), __k);
		}

		const_iterator
		upper_bound(const key_type &__k) const
		{
			return _M_upper_bound(_M_begin(), _M_end(), __k);
		}

		pair<iterator, iterator>
		equal_range(const key_type &__k);

		pair<const_iterator, const_iterator>
		equal_range(const key_type &__k) const;

		// Debugging.
		bool
		__rb_verify() const;

		friend bool
		operator==(const rb_tree &__x, const rb_tree &__y)
		{
			return __x.size() == __y.size() && std::equal(__x.begin(), __x.end(), __y.begin());
		}

		friend bool
		operator<(const rb_tree &__x, const rb_tree &__y)
		{
			return std::lexicographical_compare(__x.begin(), __x.end(),
												__y.begin(), __y.end());
		}

		friend bool
		operator!=(const rb_tree &__x, const rb_tree &__y)
		{
			return !(__x == __y);
		}

		friend bool
		operator>(const rb_tree &__x, const rb_tree &__y)
		{
			return __y < __x;
		}

		friend bool
		operator<=(const rb_tree &__x, const rb_tree &__y)
		{
			return !(__y < __x);
		}

		friend bool
		operator>=(const rb_tree &__x, const rb_tree &__y)
		{
			return !(__x < __y);
		}
	};

	template <typename key, typename val, typename keyOfValue,
			  typename compare, typename alloc>
	inline void
	swap(rb_tree<key, val, keyOfValue, compare, alloc> &__x,
		 rb_tree<key, val, keyOfValue, compare, alloc> &__y)
	{
		__x.swap(__y);
	}

	template <typename key, typename val, typename keyOfValue,
			  typename compare, typename alloc>
	rb_tree<key, val, keyOfValue, compare, alloc> &
	rb_tree<key, val, keyOfValue, compare, alloc>::
	operator=(const rb_tree &__x)
	{
		if (this != &__x)
		{
			// Note that key may be a constant type.

			reuse_or_alloc_node __roan(*this);
			_M_impl._M_reset();
			_M_impl._M_key_compare = __x._M_impl._M_key_compare;
			if (__x._M_root() != 0)
				_M_root() = _M_copy(__x, __roan);
		}

		return *this;
	}

	template <typename key, typename val, typename keyOfValue,
			  typename compare, typename alloc>
	template <typename _NodeGen>
	typename rb_tree<key, val, keyOfValue, compare, alloc>::iterator
	rb_tree<key, val, keyOfValue, compare, alloc>::
		_M_insert_(base_ptr __x, base_ptr __p,
				   const val &__v,
				   _NodeGen &__node_gen)
	{
		bool __insert_left = (__x != 0 || __p == _M_end() || _M_impl._M_key_compare(keyOfValue()(__v), _S_key(__p)));

		link_type __z = __node_gen(_GLIBCXX_FORWARD(_Arg, __v));

		_Rb_tree_insert_and_rebalance(__insert_left, __z, __p,
									  this->_M_impl._M_header);
		++_M_impl.node_count;
		return iterator(__z);
	}

	template <typename key, typename val, typename keyOfValue,
			  typename compare, typename alloc>
	typename rb_tree<key, val, keyOfValue, compare, alloc>::iterator
	rb_tree<key, val, keyOfValue, compare, alloc>::
		_M_insert_lower(base_ptr __p, const val &__v)
	{
		bool __insert_left = (__p == _M_end() || !_M_impl._M_key_compare(_S_key(__p),
																		 keyOfValue()(__v)));

		link_type __z = _M_create_node(_GLIBCXX_FORWARD(_Arg, __v));

		_Rb_tree_insert_and_rebalance(__insert_left, __z, __p,
									  this->_M_impl._M_header);
		++_M_impl.node_count;
		return iterator(__z);
	}

	template <typename key, typename val, typename keyOfValue,
			  typename compare, typename alloc>
	typename rb_tree<key, val, keyOfValue, compare, alloc>::iterator
	rb_tree<key, val, keyOfValue, compare, alloc>::
		_M_insert_equal_lower(const val &__v)
	{
		link_type __x = _M_begin();
		base_ptr __y = _M_end();
		while (__x != 0)
		{
			__y = __x;
			__x = !_M_impl._M_key_compare(_S_key(__x), keyOfValue()(__v)) ? _S_left(__x) : _S_right(__x);
		}
		return _M_insert_lower(__y, _GLIBCXX_FORWARD(_Arg, __v));
	}

	template <typename key, typename val, typename _KoV,
			  typename compare, typename alloc>
	template <typename _NodeGen>
	typename rb_tree<key, val, _KoV, compare, alloc>::link_type
	rb_tree<key, val, _KoV, compare, alloc>::
		_M_copy(const_link_type __x, base_ptr __p, _NodeGen &__node_gen)
	{
		// Structural copy. __x and __p must be non-null.
		link_type __top = _M_clone_node(__x, __node_gen);
		__top->parent = __p;

		__try
		{
			if (__x->right)
				__top->right = _M_copy(_S_right(__x), __top, __node_gen);
			__p = __top;
			__x = _S_left(__x);

			while (__x != 0)
			{
				link_type __y = _M_clone_node(__x, __node_gen);
				__p->left = __y;
				__y->parent = __p;
				if (__x->right)
					__y->right = _M_copy(_S_right(__x), __y, __node_gen);
				__p = __y;
				__x = _S_left(__x);
			}
		}
		__catch(...)
		{
			_M_erase(__top);
			__throw_exception_again;
		}
		return __top;
	}

	template <typename key, typename val, typename keyOfValue,
			  typename compare, typename alloc>
	void
	rb_tree<key, val, keyOfValue, compare, alloc>::
		_M_erase(link_type __x)
	{
		// Erase without rebalancing.
		while (__x != 0)
		{
			_M_erase(_S_right(__x));
			link_type __y = _S_left(__x);
			_M_drop_node(__x);
			__x = __y;
		}
	}

	template <typename key, typename val, typename keyOfValue,
			  typename compare, typename alloc>
	typename rb_tree<key, val, keyOfValue,
					 compare, alloc>::iterator
	rb_tree<key, val, keyOfValue, compare, alloc>::
		_M_lower_bound(link_type __x, base_ptr __y,
					   const key &__k)
	{
		while (__x != 0)
			if (!_M_impl._M_key_compare(_S_key(__x), __k))
				__y = __x, __x = _S_left(__x);
			else
				__x = _S_right(__x);
		return iterator(__y);
	}

	template <typename key, typename val, typename keyOfValue,
			  typename compare, typename alloc>
	typename rb_tree<key, val, keyOfValue,
					 compare, alloc>::const_iterator
	rb_tree<key, val, keyOfValue, compare, alloc>::
		_M_lower_bound(const_link_type __x, const_base_ptr __y,
					   const key &__k) const
	{
		while (__x != 0)
			if (!_M_impl._M_key_compare(_S_key(__x), __k))
				__y = __x, __x = _S_left(__x);
			else
				__x = _S_right(__x);
		return const_iterator(__y);
	}

	template <typename key, typename val, typename keyOfValue,
			  typename compare, typename alloc>
	typename rb_tree<key, val, keyOfValue,
					 compare, alloc>::iterator
	rb_tree<key, val, keyOfValue, compare, alloc>::
		_M_upper_bound(link_type __x, base_ptr __y,
					   const key &__k)
	{
		while (__x != 0)
			if (_M_impl._M_key_compare(__k, _S_key(__x)))
				__y = __x, __x = _S_left(__x);
			else
				__x = _S_right(__x);
		return iterator(__y);
	}

	template <typename key, typename val, typename keyOfValue,
			  typename compare, typename alloc>
	typename rb_tree<key, val, keyOfValue,
					 compare, alloc>::const_iterator
	rb_tree<key, val, keyOfValue, compare, alloc>::
		_M_upper_bound(const_link_type __x, const_base_ptr __y,
					   const key &__k) const
	{
		while (__x != 0)
			if (_M_impl._M_key_compare(__k, _S_key(__x)))
				__y = __x, __x = _S_left(__x);
			else
				__x = _S_right(__x);
		return const_iterator(__y);
	}

	template <typename key, typename val, typename keyOfValue,
			  typename compare, typename alloc>
	pair<typename rb_tree<key, val, keyOfValue,
						  compare, alloc>::iterator,
		 typename rb_tree<key, val, keyOfValue,
						  compare, alloc>::iterator>
	rb_tree<key, val, keyOfValue, compare, alloc>::
		equal_range(const key &__k)
	{
		link_type __x = _M_begin();
		base_ptr __y = _M_end();
		while (__x != 0)
		{
			if (_M_impl._M_key_compare(_S_key(__x), __k))
				__x = _S_right(__x);
			else if (_M_impl._M_key_compare(__k, _S_key(__x)))
				__y = __x, __x = _S_left(__x);
			else
			{
				link_type __xu(__x);
				base_ptr __yu(__y);
				__y = __x, __x = _S_left(__x);
				__xu = _S_right(__xu);
				return pair<iterator,
							iterator>(_M_lower_bound(__x, __y, __k),
									  _M_upper_bound(__xu, __yu, __k));
			}
		}
		return pair<iterator, iterator>(iterator(__y),
										iterator(__y));
	}

	template <typename key, typename val, typename keyOfValue,
			  typename compare, typename alloc>
	pair<typename rb_tree<key, val, keyOfValue,
						  compare, alloc>::const_iterator,
		 typename rb_tree<key, val, keyOfValue,
						  compare, alloc>::const_iterator>
	rb_tree<key, val, keyOfValue, compare, alloc>::
		equal_range(const key &__k) const
	{
		const_link_type __x = _M_begin();
		const_base_ptr __y = _M_end();
		while (__x != 0)
		{
			if (_M_impl._M_key_compare(_S_key(__x), __k))
				__x = _S_right(__x);
			else if (_M_impl._M_key_compare(__k, _S_key(__x)))
				__y = __x, __x = _S_left(__x);
			else
			{
				const_link_type __xu(__x);
				const_base_ptr __yu(__y);
				__y = __x, __x = _S_left(__x);
				__xu = _S_right(__xu);
				return pair<const_iterator,
							const_iterator>(_M_lower_bound(__x, __y, __k),
											_M_upper_bound(__xu, __yu, __k));
			}
		}
		return pair<const_iterator, const_iterator>(const_iterator(__y),
													const_iterator(__y));
	}

	template <typename key, typename val, typename keyOfValue,
			  typename compare, typename alloc>
	void
	rb_tree<key, val, keyOfValue, compare, alloc>::
		swap(rb_tree &__t)
			_IF(__is_nothrow_swappable<compare>::value)
	{
		if (_M_root() == 0)
		{
			if (__t._M_root() != 0)
				_M_impl._M_move_data(__t._M_impl);
		}
		else if (__t._M_root() == 0)
			__t._M_impl._M_move_data(_M_impl);
		else
		{
			std::swap(_M_root(), __t._M_root());
			std::swap(leftmost(), __t._M_leftmost());
			std::swap(rightmost(), __t._M_rightmost());

			_M_root()->parent = _M_end();
			__t._M_root()->parent = __t._M_end();
			std::swap(this->_M_impl.node_count, __t._M_impl.node_count);
		}
		// No need to swap header's color as it does not change.
		std::swap(this->_M_impl._M_key_compare, __t._M_impl._M_key_compare);

		alloc_traits::_S_on_swap(_M_get_Node_allocator(),
								 __t._M_get_Node_allocator());
	}

	template <typename key, typename val, typename keyOfValue,
			  typename compare, typename alloc>
	pair<typename rb_tree<key, val, keyOfValue,
						  compare, alloc>::base_ptr,
		 typename rb_tree<key, val, keyOfValue,
						  compare, alloc>::base_ptr>
	rb_tree<key, val, keyOfValue, compare, alloc>::
		_M_get_insert_unique_pos(const key_type &__k)
	{
		typedef pair<base_ptr, base_ptr> _Res;
		link_type __x = _M_begin();
		base_ptr __y = _M_end();
		bool __comp = true;
		while (__x != 0)
		{
			__y = __x;
			__comp = _M_impl._M_key_compare(__k, _S_key(__x));
			__x = __comp ? _S_left(__x) : _S_right(__x);
		}
		iterator __j = iterator(__y);
		if (__comp)
		{
			if (__j == begin())
				return _Res(__x, __y);
			else
				--__j;
		}
		if (_M_impl._M_key_compare(_S_key(__j._M_node), __k))
			return _Res(__x, __y);
		return _Res(__j._M_node, 0);
	}

	template <typename key, typename val, typename keyOfValue,
			  typename compare, typename alloc>
	pair<typename rb_tree<key, val, keyOfValue,
						  compare, alloc>::base_ptr,
		 typename rb_tree<key, val, keyOfValue,
						  compare, alloc>::base_ptr>
	rb_tree<key, val, keyOfValue, compare, alloc>::
		_M_get_insert_equal_pos(const key_type &__k)
	{
		typedef pair<base_ptr, base_ptr> _Res;
		link_type __x = _M_begin();
		base_ptr __y = _M_end();
		while (__x != 0)
		{
			__y = __x;
			__x = _M_impl._M_key_compare(__k, _S_key(__x)) ? _S_left(__x) : _S_right(__x);
		}
		return _Res(__x, __y);
	}

	template <typename key, typename val, typename keyOfValue,
			  typename compare, typename alloc>
	pair<typename rb_tree<key, val, keyOfValue,
						  compare, alloc>::iterator,
		 bool>
	rb_tree<key, val, keyOfValue, compare, alloc>::
		_M_insert_unique(const val &__v)
	{
		typedef pair<iterator, bool> _Res;
		pair<base_ptr, base_ptr> __res = _M_get_insert_unique_pos(keyOfValue()(__v));

		if (__res.second)
		{
			alloc_node __an(*this);
			return _Res(_M_insert_(__res.first, __res.second,
								   _GLIBCXX_FORWARD(_Arg, __v), __an),
						true);
		}

		return _Res(iterator(__res.first), false);
	}

	template <typename key, typename val, typename keyOfValue,
			  typename compare, typename alloc>
	typename rb_tree<key, val, keyOfValue, compare, alloc>::iterator
	rb_tree<key, val, keyOfValue, compare, alloc>::
		_M_insert_equal(const val &__v)
	{
		pair<base_ptr, base_ptr> __res = _M_get_insert_equal_pos(keyOfValue()(__v));
		alloc_node __an(*this);
		return _M_insert_(__res.first, __res.second,
						  _GLIBCXX_FORWARD(_Arg, __v), __an);
	}

	template <typename key, typename val, typename keyOfValue,
			  typename compare, typename alloc>
	pair<typename rb_tree<key, val, keyOfValue,
						  compare, alloc>::base_ptr,
		 typename rb_tree<key, val, keyOfValue,
						  compare, alloc>::base_ptr>
	rb_tree<key, val, keyOfValue, compare, alloc>::
		_M_get_insert_hint_unique_pos(const_iterator __position,
									  const key_type &__k)
	{
		iterator __pos = __position._M_const_cast();
		typedef pair<base_ptr, base_ptr> _Res;

		// end()
		if (__pos._M_node == _M_end())
		{
			if (size() > 0 && _M_impl._M_key_compare(_S_key(rightmost()), __k))
				return _Res(0, rightmost());
			else
				return _M_get_insert_unique_pos(__k);
		}
		else if (_M_impl._M_key_compare(__k, _S_key(__pos._M_node)))
		{
			// First, try before...
			iterator __before = __pos;
			if (__pos._M_node == leftmost()) // begin()
				return _Res(leftmost(), _M_leftmost());
			else if (_M_impl._M_key_compare(_S_key((--__before)._M_node), __k))
			{
				if (_S_right(__before._M_node) == 0)
					return _Res(0, __before._M_node);
				else
					return _Res(__pos._M_node, __pos._M_node);
			}
			else
				return _M_get_insert_unique_pos(__k);
		}
		else if (_M_impl._M_key_compare(_S_key(__pos._M_node), __k))
		{
			// ... then try after.
			iterator __after = __pos;
			if (__pos._M_node == rightmost())
				return _Res(0, rightmost());
			else if (_M_impl._M_key_compare(__k, _S_key((++__after)._M_node)))
			{
				if (_S_right(__pos._M_node) == 0)
					return _Res(0, __pos._M_node);
				else
					return _Res(__after._M_node, __after._M_node);
			}
			else
				return _M_get_insert_unique_pos(__k);
		}
		else
			// Equivalent keys.
			return _Res(__pos._M_node, 0);
	}

	template <typename key, typename val, typename keyOfValue,
			  typename compare, typename alloc>
	template <typename _NodeGen>
	typename rb_tree<key, val, keyOfValue, compare, alloc>::iterator
	rb_tree<key, val, keyOfValue, compare, alloc>::
		_M_insert_unique_(const_iterator __position,
						  const val &__v,
						  _NodeGen &__node_gen)
	{
		pair<base_ptr, base_ptr> __res = _M_get_insert_hint_unique_pos(__position, keyOfValue()(__v));

		if (__res.second)
			return _M_insert_(__res.first, __res.second,
							  _GLIBCXX_FORWARD(_Arg, __v),
							  __node_gen);
		return iterator(__res.first);
	}

	template <typename key, typename val, typename keyOfValue,
			  typename compare, typename alloc>
	pair<typename rb_tree<key, val, keyOfValue,
						  compare, alloc>::base_ptr,
		 typename rb_tree<key, val, keyOfValue,
						  compare, alloc>::base_ptr>
	rb_tree<key, val, keyOfValue, compare, alloc>::
		_M_get_insert_hint_equal_pos(const_iterator __position, const key_type &__k)
	{
		iterator __pos = __position._M_const_cast();
		typedef pair<base_ptr, base_ptr> _Res;

		// end()
		if (__pos._M_node == _M_end())
		{
			if (size() > 0 && !_M_impl._M_key_compare(__k, _S_key(rightmost())))
				return _Res(0, rightmost());
			else
				return _M_get_insert_equal_pos(__k);
		}
		else if (!_M_impl._M_key_compare(_S_key(__pos._M_node), __k))
		{
			// First, try before...
			iterator __before = __pos;
			if (__pos._M_node == leftmost()) // begin()
				return _Res(leftmost(), _M_leftmost());
			else if (!_M_impl._M_key_compare(__k, _S_key((--__before)._M_node)))
			{
				if (_S_right(__before._M_node) == 0)
					return _Res(0, __before._M_node);
				else
					return _Res(__pos._M_node, __pos._M_node);
			}
			else
				return _M_get_insert_equal_pos(__k);
		}
		else
		{
			// ... then try after.
			iterator __after = __pos;
			if (__pos._M_node == rightmost())
				return _Res(0, rightmost());
			else if (!_M_impl._M_key_compare(_S_key((++__after)._M_node), __k))
			{
				if (_S_right(__pos._M_node) == 0)
					return _Res(0, __pos._M_node);
				else
					return _Res(__after._M_node, __after._M_node);
			}
			else
				return _Res(0, 0);
		}
	}

	template <typename key, typename val, typename keyOfValue,
			  typename compare, typename alloc>
	template <typename _NodeGen>
	typename rb_tree<key, val, keyOfValue, compare, alloc>::iterator
	rb_tree<key, val, keyOfValue, compare, alloc>::
		_M_insert_equal_(const_iterator __position,
						 const val &__v,
						 _NodeGen &__node_gen)
	{
		pair<base_ptr, base_ptr> __res = _M_get_insert_hint_equal_pos(__position, keyOfValue()(__v));

		if (__res.second)
			return _M_insert_(__res.first, __res.second,
							  _GLIBCXX_FORWARD(_Arg, __v),
							  __node_gen);

		return _M_insert_equal_lower(_GLIBCXX_FORWARD(_Arg, __v));
	}

	template <typename key, typename val, typename keyOfValue,
			  typename compare, typename alloc>
	void
	rb_tree<key, val, keyOfValue, compare, alloc>::
		_M_erase_aux(const_iterator __position)
	{
		link_type __y =
			static_cast<link_type>(_Rb_tree_rebalance_for_erase(const_cast<base_ptr>(__position._M_node),
																this->_M_impl._M_header));
		_M_drop_node(__y);
		--_M_impl.node_count;
	}

	template <typename key, typename val, typename keyOfValue,
			  typename compare, typename alloc>
	void
	rb_tree<key, val, keyOfValue, compare, alloc>::
		_M_erase_aux(const_iterator __first, const_iterator __last)
	{
		if (__first == begin() && __last == end())
			clear();
		else
			while (__first != __last)
				_M_erase_aux(__first++);
	}

	template <typename key, typename val, typename keyOfValue,
			  typename compare, typename alloc>
	typename rb_tree<key, val, keyOfValue, compare, alloc>::size_type
	rb_tree<key, val, keyOfValue, compare, alloc>::
		erase(const key &__x)
	{
		pair<iterator, iterator> __p = equal_range(__x);
		const size_type __old_size = size();
		_M_erase_aux(__p.first, __p.second);
		return __old_size - size();
	}

	template <typename key, typename val, typename keyOfValue,
			  typename compare, typename alloc>
	typename rb_tree<key, val, keyOfValue,
					 compare, alloc>::iterator
	rb_tree<key, val, keyOfValue, compare, alloc>::
		find(const key &__k)
	{
		iterator __j = _M_lower_bound(_M_begin(), _M_end(), __k);
		return (__j == end() || _M_impl._M_key_compare(__k,
													   _S_key(__j._M_node)))
				   ? end()
				   : __j;
	}

	template <typename key, typename val, typename keyOfValue,
			  typename compare, typename alloc>
	typename rb_tree<key, val, keyOfValue,
					 compare, alloc>::const_iterator
	rb_tree<key, val, keyOfValue, compare, alloc>::
		find(const key &__k) const
	{
		const_iterator __j = _M_lower_bound(_M_begin(), _M_end(), __k);
		return (__j == end() || _M_impl._M_key_compare(__k,
													   _S_key(__j._M_node)))
				   ? end()
				   : __j;
	}

	template <typename key, typename val, typename keyOfValue,
			  typename compare, typename alloc>
	typename rb_tree<key, val, keyOfValue, compare, alloc>::size_type
	rb_tree<key, val, keyOfValue, compare, alloc>::
		count(const key &__k) const
	{
		pair<const_iterator, const_iterator> __p = equal_range(__k);
		const size_type __n = std::distance(__p.first, __p.second);
		return __n;
	}

	_GLIBCXX_PURE unsigned int
	_Rb_tree_black_count(const rb_tree_node_base *__node,
						 const rb_tree_node_base *__root) throw();

	template <typename key, typename val, typename keyOfValue,
			  typename compare, typename alloc>
	bool
	rb_tree<key, val, keyOfValue, compare, alloc>::__rb_verify() const
	{
		if (_M_impl.node_count == 0 || begin() == end())
			return _M_impl.node_count == 0 && begin() == end() && this->_M_impl._M_header.left == _M_end() && this->_M_impl._M_header.right == _M_end();

		unsigned int __len = _Rb_tree_black_count(leftmost(), _M_root());
		for (const_iterator __it = begin(); __it != end(); ++__it)
		{
			const_link_type __x = static_cast<const_link_type>(__it._M_node);
			const_link_type __L = _S_left(__x);
			const_link_type __R = _S_right(__x);

			if (__x->color == _S_red)
				if ((__L && __L->color == _S_red) || (__R && __R->color == _S_red))
					return false;

			if (__L && _M_impl._M_key_compare(_S_key(__x), _S_key(__L)))
				return false;
			if (__R && _M_impl._M_key_compare(_S_key(__R), _S_key(__x)))
				return false;

			if (!__L && !__R && _Rb_tree_black_count(__x, _M_root()) != __len)
				return false;
		}

		if (leftmost() != rb_tree_node_base::_S_minimum(_M_root()))
			return false;
		if (rightmost() != rb_tree_node_base::_S_maximum(_M_root()))
			return false;
		return true;
	}

} // namespace ft

#endif /* ********************************************************* RB_TREE_H */