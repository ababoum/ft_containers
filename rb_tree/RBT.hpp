/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 20:27:11 by mababou           #+#    #+#             */
/*   Updated: 2022/07/27 13:39:42 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_HPP
#define RBT_HPP

#include <iostream>
#include "../pairs/pair.hpp"
#include "../iterators/reverse_iterator.hpp"

namespace ft
{
	template <class Key, class T>
	struct RBT_iterator;
	
	template <class Key, class T>
	struct RBT_const_iterator;

	// definition of red and black colors
	enum rb_tree_color
	{
		_S_red = false,
		_S_black = true
	};

	// structure of a node in the tree
	template <class Key, class T>
	struct RBT_node
	{
		typedef pair<const Key, T> value_type;

		rb_tree_color color;
		RBT_node *parent;
		RBT_node *left;
		RBT_node *right;
		value_type pair_data;
		bool is_nil;

		RBT_node(): pair_data(Key(), T()) {}
		
		RBT_node(value_type pair_init):pair_data(pair_init) {}
		
		value_type *value_ptr()
		{
			return &(pair_data);
		}

		const value_type *value_ptr() const
		{
			return &(pair_data);
		}
	};

	// iterator increment/decrement

	template <class Key, class T>
	static RBT_node<Key, T> *
	local_rb_tree_increment(RBT_node<Key, T> *node_ptr) throw()
	{
		RBT_node<Key, T> *initial_node = node_ptr;
		
		// do nothing if a leaf is atteigned
		if (node_ptr->is_nil)
		{
			if (node_ptr->parent)
				return node_ptr->parent;
			return node_ptr;
		}
		
		if (!node_ptr->right->is_nil)
		{
			node_ptr = node_ptr->right;
			while (!node_ptr->left->is_nil)
				node_ptr = node_ptr->left;
			return node_ptr;
		}
		else
		{
			RBT_node<Key, T> *tmp_node = node_ptr->parent;
			while (tmp_node &&
				!tmp_node->is_nil && 
				node_ptr == tmp_node->right)
			{
				node_ptr = tmp_node;
				tmp_node = tmp_node->parent;
			}
			if (tmp_node == NULL)
				return initial_node->right;
			return tmp_node;
		}
	}

	template <class Key, class T>
	RBT_node<Key, T> *
	rb_tree_increment(RBT_node<Key, T> *node_ptr) throw()
	{
		return local_rb_tree_increment(node_ptr);
	}

	template <class Key, class T>
	const RBT_node<Key, T> *
	rb_tree_increment(const RBT_node<Key, T> *node_ptr) throw()
	{
		return local_rb_tree_increment(const_cast<RBT_node<Key, T> *>(node_ptr));
	}

	template <class Key, class T>
	static RBT_node<Key, T> *
	local_rb_tree_decrement(RBT_node<Key, T> *node_ptr) throw()
	{
		RBT_node<Key, T> *initial_node = node_ptr;

		// do nothing if a leaf is atteigned, except for end
		if (node_ptr->is_nil)
		{
			if (node_ptr->parent)
				return node_ptr->parent;
			return node_ptr;
		}
		
		if (!node_ptr->left->is_nil)
		{
			node_ptr = node_ptr->left;
			while (!node_ptr->right->is_nil)
				node_ptr = node_ptr->right;
			return node_ptr;
		}
		else
		{
			RBT_node<Key, T> *tmp_node = node_ptr->parent;
			while (tmp_node && !tmp_node->is_nil && node_ptr == tmp_node->left)
			{
				node_ptr = tmp_node;
				tmp_node = tmp_node->parent;
			}
			if (tmp_node == NULL)
				return initial_node->left;
			return tmp_node;
		}
	}

	template <class Key, class T>
	RBT_node<Key, T> *
	rb_tree_decrement(RBT_node<Key, T> *node_ptr) throw()
	{
		return local_rb_tree_decrement(node_ptr);
	}

	template <class Key, class T>
	const RBT_node<Key, T> *
	rb_tree_decrement(const RBT_node<Key, T> *node_ptr) throw()
	{
		return local_rb_tree_decrement(const_cast<RBT_node<Key, T> *>(node_ptr));
	}

	// red-black tree iterator
	template <class Key, class T>
	struct RBT_iterator
	{
		typedef pair<const Key, T> value_type;
		typedef value_type &reference;
		typedef value_type *pointer;

		typedef std::bidirectional_iterator_tag iterator_category;
		typedef std::ptrdiff_t difference_type;

		typedef RBT_iterator<Key, T> iterator;
		typedef RBT_node<Key, T> *base_ptr;
		typedef const base_ptr	const_base_ptr;
		typedef RBT_const_iterator<Key, T> const_iterator;

		base_ptr node_ptr;

		RBT_iterator()
			: node_ptr() {}

		RBT_iterator(base_ptr node_ptr_input)
			: node_ptr(node_ptr_input) {}

		RBT_iterator(const RBT_iterator & other)
		{
			node_ptr = other.base();
		}

		RBT_iterator & operator=( const RBT_iterator & other )
		{
			node_ptr = other.base();
			return *this;
		}

		base_ptr
		base() const
		{
			return node_ptr;
		}

		reference
		operator*() const
		{
			return *static_cast<base_ptr>(node_ptr)->value_ptr();
		}

		pointer
		operator->() const
		{
			return static_cast<base_ptr>(node_ptr)->value_ptr();
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

		iterator operator+( difference_type n ) const
		{
			iterator tmp(base());

			for (difference_type i = 0; i != n; ++i)
				++tmp;
				
			return (tmp);
		}

		iterator operator-( difference_type n ) const
		{
			iterator tmp(base());

			for (difference_type i = 0; i != n; ++i)
				--tmp;
				
			return (tmp);
		}

		friend bool
		operator==(const iterator &lhs, const iterator &rhs)
		{
			if (lhs.base()->is_nil && rhs.base()->is_nil)
				return true;
			return lhs.node_ptr == rhs.node_ptr;
		}

		friend bool
		operator==(const iterator &lhs, const const_iterator &rhs)
		{
			if (lhs.base()->is_nil && rhs.base()->is_nil)
				return true;
			return lhs.node_ptr == rhs.node_ptr;
		}

		friend bool
		operator!=(const iterator &lhs, const iterator &rhs)
		{
			return !(lhs == rhs);
		}

		friend bool
		operator!=(const iterator &lhs, const const_iterator &rhs)
		{
			return !(lhs == rhs);
		}
	};

	// red-black tree const iterator

	template <class Key, class T>
	struct RBT_const_iterator
	{
		typedef pair<const Key, T> value_type;
		typedef const value_type &reference;
		typedef const value_type *pointer;

		typedef RBT_iterator<Key, T> iterator;

		typedef std::bidirectional_iterator_tag iterator_category;
		typedef std::ptrdiff_t difference_type;

		typedef RBT_const_iterator<Key, T> const_iterator;
		typedef const RBT_node<Key, T> *base_ptr;

		base_ptr node_ptr;

		RBT_const_iterator()
			: node_ptr() {}

		RBT_const_iterator(base_ptr node_ptr_input)
			: node_ptr(node_ptr_input) {}

		RBT_const_iterator(const RBT_const_iterator & other)
			: node_ptr(other.node_ptr) {}

		const_iterator & operator=( const const_iterator & other )
		{
			node_ptr = other.base();
			return *this;
		}

		RBT_const_iterator(const iterator & other)
			: node_ptr(other.node_ptr) {}

		const_iterator & operator=( const iterator & other )
		{
			node_ptr = other.base();
			return *this;
		}

		base_ptr
		base() const
		{
			return node_ptr;
		}

		reference
		operator*() const
		{
			return *static_cast<base_ptr>(node_ptr)->value_ptr();
		}

		pointer
		operator->() const
		{
			return static_cast<base_ptr>(node_ptr)->value_ptr();
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

		const_iterator operator+( difference_type n ) const
		{
			const_iterator tmp(base());

			for (difference_type i = 0; i != n; ++i)
				++tmp;
				
			return (tmp);
		}

		const_iterator operator-( difference_type n ) const
		{
			const_iterator tmp(base());

			for (difference_type i = 0; i != n; ++i)
				--tmp;
				
			return (tmp);
		}

		friend bool
		operator==(const const_iterator &lhs, const const_iterator &rhs)
		{
			if (lhs.base()->is_nil && rhs.base()->is_nil)
				return true;
			return lhs.node_ptr == rhs.node_ptr;
		}

		friend bool
		operator==(const const_iterator &lhs, const iterator &rhs)
		{
			if (lhs.base()->is_nil && rhs.base()->is_nil)
				return true;
			return lhs.node_ptr == rhs.node_ptr;
		}

		friend bool
		operator!=(const const_iterator &lhs, const const_iterator &rhs)
		{
			return !(lhs == rhs);
		}

		friend bool
		operator!=(const const_iterator &lhs, const iterator &rhs)
		{
			return !(lhs == rhs);
		}

		
	};

	// RBT reference: https://www.programiz.com/dsa/red-black-tree

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
		typedef typename Allocator::template rebind<RBT_node<Key, T> >::other node_allocator;
		typedef Key key_type;
		typedef T mapped_type;
		typedef pair<const key_type, mapped_type> value_type;
		typedef	RBT_node<Key, T> node_type;
		typedef RBT_node<Key, T> *base_ptr;
		typedef const base_ptr	const_base_ptr;

		typedef RBT_iterator<Key, T> iterator;
		typedef RBT_const_iterator<Key, T> const_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;

	private:
		base_ptr _root;
		base_ptr _null_node;
		base_ptr _null_begin;
		base_ptr _null_end;
		size_type _node_count;
		pair_allocator _pair_alloc;
		node_allocator _node_alloc;
		key_compare _comp;

		// helper functions

		base_ptr _treeExplorer(base_ptr node, Key key)
		{
			if (node->is_nil || key == node->pair_data.first)
			{
				return node;
			}

			if (_comp(key, node->pair_data.first))
			{
				return _treeExplorer(node->left, key);
			}
			return _treeExplorer(node->right, key);
		}

		const_base_ptr _treeExplorer(base_ptr node, Key key) const
		{
			if (node->is_nil || key == node->pair_data.first)
			{
				return node;
			}

			if (key < node->pair_data.first)
			{
				return _treeExplorer(node->left, key);
			}
			return _treeExplorer(node->right, key);
		}

		// For balancing the tree after deletion
		void _rebalance_postDelete(base_ptr x)
		{
			base_ptr s;

			while (x != _root && x->color == _S_black)
			{
				if (x == x->parent->left)
				{
					s = x->parent->right;
					if (s->color == _S_red)
					{
						s->color = _S_black;
						x->parent->color = _S_red;
						_leftRotate(x->parent);
						s = x->parent->right;
					}

					if (s->left->color == _S_black && s->right->color == _S_black)
					{
						s->color = _S_red;
						x = x->parent;
					}
					else
					{
						if (s->right->color == _S_black)
						{
							s->left->color = _S_black;
							s->color = _S_red;
							_rightRotate(s);
							s = x->parent->right;
						}

						s->color = x->parent->color;
						x->parent->color = _S_black;
						s->right->color = _S_black;
						_leftRotate(x->parent);
						x = _root;
					}
				}
				else
				{
					s = x->parent->left;
					if (s->color == _S_red)
					{
						s->color = _S_black;
						x->parent->color = _S_red;
						_rightRotate(x->parent);
						s = x->parent->left;
					}

					if (s->right->color == _S_black && s->right->color == _S_black)
					{
						s->color = _S_red;
						x = x->parent;
					}
					else
					{
						if (s->left->color == _S_black)
						{
							s->right->color = _S_black;
							s->color = _S_red;
							_leftRotate(s);
							s = x->parent->left;
						}

						s->color = x->parent->color;
						x->parent->color = _S_black;
						s->left->color = _S_black;
						_rightRotate(x->parent);
						x = _root;
					}
				}
			}
			x->color = _S_black;
		}

		void _subTreeReplace(base_ptr u, base_ptr v)
		{
			if (u->parent == NULL)
				_root = v;
			else if (u == u->parent->left)
				u->parent->left = v;
			else
				u->parent->right = v;
			v->parent = u->parent;
		}

		void _nodeDeleter(base_ptr node, Key key)
		{
			base_ptr z = _null_node;
			base_ptr x;
			base_ptr y;

			while (!node->is_nil)
			{
				if (node->pair_data.first == key)
					z = node;

				if (node->pair_data.first <= key)
					node = node->right;
				else
					node = node->left;
			}

			if (z->is_nil)
			{
				return;
			}

			y = z;
			bool y_original_color = y->color;

			if (z->left->is_nil)
			{
				x = z->right;
				_subTreeReplace(z, z->right);
			}
			else if (z->right->is_nil)
			{
				x = z->left;
				_subTreeReplace(z, z->left);
			}
			else
			{
				y = _minimum(z->right);
				y_original_color = y->color;
				x = y->right;
				if (y->parent == z)
					x->parent = y;
				else
				{
					_subTreeReplace(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}

				_subTreeReplace(z, y);
				y->left = z->left;
				y->left->parent = y;
				y->color = z->color;
			}

			_node_alloc.deallocate(z, sizeof(z));
			
			if (y_original_color == _S_black)
				_rebalance_postDelete(x);
		}

		// For balancing the tree after insertion
		void _rebalance_postInsert(base_ptr k)
		{
			base_ptr u;

			while (k->parent->color == _S_red)
			{
				if (k->parent == k->parent->parent->right)
				{
					u = k->parent->parent->left;
					if (u->color == _S_red)
					{
						u->color = _S_black;
						k->parent->color = _S_black;
						k->parent->parent->color = _S_red;
						k = k->parent->parent;
					}
					else
					{
						if (k == k->parent->left)
						{
							k = k->parent;
							_rightRotate(k);
						}
						k->parent->color = _S_black;
						k->parent->parent->color = _S_red;
						_leftRotate(k->parent->parent);
					}
				}
				else
				{
					u = k->parent->parent->right;

					if (u->color == _S_red)
					{
						u->color = _S_black;
						k->parent->color = _S_black;
						k->parent->parent->color = _S_red;
						k = k->parent->parent;
					}
					else
					{
						if (k == k->parent->right)
						{
							k = k->parent;
							_leftRotate(k);
						}
						k->parent->color = _S_black;
						k->parent->parent->color = _S_red;
						_rightRotate(k->parent->parent);
					}
				}
				if (k == _root)
				{
					break;
				}
			}
			_root->color = _S_black;
		}

		void _replaceBeginEnd(void)
		{
			base_ptr tmp = _minimum(_root);
			
			if (_null_begin->parent)
			{
				if (_null_begin->parent->left == _null_begin)
					_null_begin->parent->left = _null_node;
				tmp->left = _null_begin;
				_null_begin->parent = tmp;
			}
			else
			{
				tmp->left = _null_begin;
				_null_begin->parent = tmp;
			}

			tmp = _maximum(_root);
			
			if (_null_end->parent)
			{
				if (_null_end->parent->right == _null_end)
					_null_end->parent->right = _null_node;
				tmp->right = _null_end;
				_null_end->parent = tmp;
			}
			else
			{
				tmp->right = _null_end;
				_null_end->parent = tmp;
			}
			
		}

		base_ptr _minimum(base_ptr node)
		{
			if (node->is_nil)
				return node;
			while (!node->left->is_nil)
				node = node->left;
			return node;
		}

		base_ptr _maximum(base_ptr node)
		{
			if (node->is_nil)
				return node;
			while (!node->right->is_nil)
				node = node->right;
			return node;
		}

		void _leftRotate(base_ptr x)
		{
			base_ptr y = x->right;
			x->right = y->left;
			if (!y->left->is_nil)
				y->left->parent = x;
			y->parent = x->parent;
			if (x->parent == NULL)
				this->_root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->left = x;
			x->parent = y;
		}

		void _rightRotate(base_ptr x)
		{
			base_ptr y = x->left;
			x->left = y->right;
			if (!y->right->is_nil)
				y->right->parent = x;
			y->parent = x->parent;
			if (x->parent == NULL)
				this->_root = y;
			else if (x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;
			y->right = x;
			x->parent = y;
		}

		void _clearSubTree(base_ptr similiRoot)
		{
			if (similiRoot->is_nil)
				return ;

			base_ptr rightRoot = similiRoot->right;
			base_ptr leftRoot = similiRoot->left;

			_clearSubTree(rightRoot);
			_clearSubTree(leftRoot);

			_node_alloc.destroy(similiRoot);
			_node_alloc.deallocate(similiRoot, sizeof(node_type));
			
		}

	public:
		RBT()
		{
			_null_node = _node_alloc.allocate(sizeof(node_type));
			_null_begin = _node_alloc.allocate(sizeof(node_type));
			_null_end = _node_alloc.allocate(sizeof(node_type));

			_node_count = 0;
			_pair_alloc = pair_allocator();
			_node_alloc = node_allocator();
			_comp = key_compare();
			_root = _null_node;

			// null node initialization
			_null_node->color = _S_black;
			_null_node->left = NULL;
			_null_node->right = NULL;
			_null_node->is_nil = true;
			_null_node->parent = NULL;

			// null node for before-begin initialization
			_null_begin->color = _S_black;
			_null_begin->left = NULL;
			_null_begin->right = NULL;
			_null_begin->is_nil = true;
			_null_begin->parent = NULL;

			// null node for after-end initialization
			_null_end->color = _S_black;
			_null_end->left = NULL;
			_null_end->right = NULL;
			_null_end->is_nil = true;
			_null_end->parent = NULL;
		}

		~RBT()
		{
			_node_alloc.deallocate(_null_node, sizeof(_null_node));
			_node_alloc.deallocate(_null_begin, sizeof(_null_node));
			_node_alloc.deallocate(_null_end, sizeof(_null_node));
		}

		// Inserting a node
		base_ptr insert(value_type pair_to_add)
		{
			base_ptr node = _node_alloc.allocate(sizeof(node_type));
			
			_node_alloc.construct(node, pair_to_add);
			node->parent = NULL;
			node->left = _null_node;
			node->right = _null_node;
			node->color = _S_red;
			node->is_nil = false;

			base_ptr y = NULL;
			base_ptr x = this->_root;

			++_node_count;
			while (!x->is_nil)
			{
				y = x;
				if (_comp(node->pair_data.first, x->pair_data.first))
					x = x->left;
				else
					x = x->right;
			}

			node->parent = y;
			if (y == NULL)
				_root = node;
			else if (_comp(node->pair_data.first, y->pair_data.first))
				y->left = node;
			else
				y->right = node;

			if (node->parent == NULL)
			{
				node->color = _S_black;
				_replaceBeginEnd();
				return node;
			}

			if (node->parent->parent == NULL)
			{
				_replaceBeginEnd();
				return node;
			}

			_rebalance_postInsert(node);
			_replaceBeginEnd();

			return node;
		}

		base_ptr insert_hint(value_type pair_to_add, iterator hint)
		{
			base_ptr node = _node_alloc.allocate(sizeof(node_type));
			
			_node_alloc.construct(node, pair_to_add);
			node->parent = NULL;
			node->left = _null_node;
			node->right = _null_node;
			node->color = _S_red;
			node->is_nil = false;

			// arrange hint
			iterator tmp = hint + 1;
			while (!tmp.base()->is_nil && tmp.base()->pair_data.first < pair_to_add.first)
			{
				++hint;
				++tmp;
			}

			if (_comp(hint.base()->pair_data.first, pair_to_add.first))
				hint = iterator(_root);

			base_ptr y = NULL;
			base_ptr x = hint.base();

			++_node_count;
			while (!x->is_nil)
			{
				y = x;
				if (_comp(node->pair_data.first, x->pair_data.first))
					x = x->left;
				else
					x = x->right;
			}

			node->parent = y;
			if (y == NULL)
				_root = node;
			else if (_comp(node->pair_data.first, y->pair_data.first))
				y->left = node;
			else
				y->right = node;

			if (node->parent == NULL)
			{
				node->color = _S_black;
				_replaceBeginEnd();
				return node;
			}

			if (node->parent->parent == NULL)
			{
				_replaceBeginEnd();
				return node;
			}

			_rebalance_postInsert(node);
			_replaceBeginEnd();

			return node;
		}

		void deleteNode(Key key)
		{
			_nodeDeleter(this->_root, key);
		}

		/* ACCESSORS */
		void setAllocator(Allocator alloc)
		{
			_pair_alloc = alloc;
		}

		void getAllocator(void)
		{
			return _pair_alloc;
		}

		void setComp(Compare comp)
		{
			_comp = comp;
		}

		/* ELEMENT ACCESS */

		base_ptr searchTree(Key k)
		{
			return _treeExplorer(_root, k);
		}

		const_base_ptr searchTree(Key k) const
		{
			const_base_ptr ret = _treeExplorer(_root, k);
			return ret;
		}

		mapped_type &at(const key_type &key)
		{
			base_ptr searched_node = searchTree(key);

			if (searched_node->is_nil)
				throw std::out_of_range("Specified key is out of range");
			else
				return searched_node->pair_data.second;
		}

		const mapped_type &at(const key_type &key) const
		{
			base_ptr searched_node = searchTree(key);

			if (searched_node->is_nil)
				throw std::out_of_range("Specified key is out of range");
			else
				return searched_node->pair_data.second;
		}

		mapped_type &getRef_or_insert(const key_type &key)
		{
			base_ptr searched_node = searchTree(key);

			if (searched_node->is_nil)
			{
				value_type pair_to_insert(key, mapped_type());
				searched_node = insert(pair_to_insert);
			}
				return searched_node->pair_data.second;
		}

		/* MODIFIERS */

		// Is called only after checking if key doesn't exist already
		iterator insert_node(const value_type &value)
		{
			base_ptr node_inserted;

			node_inserted = insert(value);
			iterator ret(node_inserted);

			return ret;
		}

		iterator insert_node_loc(iterator pos_to_attach, const value_type &value)
		{
			base_ptr node_inserted;

			node_inserted = insert_hint(value, pos_to_attach);
			iterator ret(node_inserted);

			return ret;
		}

		void erase_node(iterator pos)
		{
			base_ptr node_to_be_deleted = pos.node_ptr;

			if (node_to_be_deleted->left == _null_begin)
				_null_begin->parent = NULL;
			if (node_to_be_deleted->right == _null_end)
				_null_end->parent = NULL;

			deleteNode(node_to_be_deleted->pair_data.first);
			
			_replaceBeginEnd();

			--_node_count;
		}

		void swap(RBT & other)
		{
			std::swap(_root, other._root);
			std::swap(_null_node, other._null_node);
			std::swap(_null_begin, other._null_begin);
			std::swap(_null_end, other._null_end);
			std::swap(_node_count, other._node_count);
			std::swap(_pair_alloc, other._pair_alloc);
			std::swap(_node_alloc, other._node_alloc);
			std::swap(_comp, other._comp);
		}

		void clear(void)
		{
			_clearSubTree(_root);
			
			_root = _null_node;
			_null_begin->parent = NULL;
			_null_end->parent = NULL;
			_node_count = 0;
		}

		key_compare key_comp() const
		{
			return _comp;
		}

		/* ITERATORS */
		iterator begin(void)
		{
			base_ptr node;
			
			if (empty())
				node = _null_begin;
			else
				node = _null_begin->parent;
		
			iterator ret(node);
			
			return ret;
		}

		const_iterator begin() const
		{
			base_ptr node;
			
			if (empty())
				node = _null_begin;
			else
				node = _null_begin->parent;
				
			const_iterator ret(node);
			
			return ret;
		}

		iterator end()
		{
			base_ptr node;
			
			node = _null_end;
			iterator ret(node);
			
			return ret;
		}

		const_iterator end() const
		{
			base_ptr node;
			
			node = _null_end;
			const_iterator ret(node);
			
			return ret;
		}

		reverse_iterator rbegin(void)
		{
			reverse_iterator ret(end());
			
			return ret;
		}

		const_reverse_iterator rbegin() const
		{
			const_reverse_iterator ret(end());
			
			return ret;
		}

		reverse_iterator rend()
		{
			reverse_iterator ret(begin());
			
			return ret;
		}

		const_reverse_iterator rend() const
		{
			const_reverse_iterator ret(begin());
			
			return ret;
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

		size_type max_size() const
		{
			return _node_alloc.max_size();
		}
		/* LOOKUP */

		iterator find(const Key &key)
		{
			base_ptr node_to_find = searchTree(key);

			if (node_to_find->is_nil)
				return end();
	
			iterator ret(node_to_find);

			return (ret);
		}

		const_iterator find(const Key &key) const
		{
			base_ptr node_to_find = searchTree(key);

			if (node_to_find->is_nil)
				return end();

			const_iterator ret(node_to_find);

			return (ret);
		}

		iterator lower_bound(const Key &key)
		{
			iterator it = begin();

			if (key < it.base()->pair_data.first)
				return it;

			while (it != end())
			{
				if (key <= (*it).first)
					break;
				++it;
			}
			return it;
		}

		const_iterator lower_bound(const Key &key) const
		{
			const_iterator it = begin();

			if (key < it.base()->pair_data.first)
				return it;

			while (it != end())
			{
				if (key <= (*it).first)
					break;
				++it;
			}
			return it;
		}

		iterator upper_bound(const Key &key)
		{
			iterator it = begin();

			if (key < it.base()->pair_data.first)
				return it;

			while (it != end())
			{
				if (key < (*it).first)
				{
					break;
				}
				++it;
			}
			return it;
		}

		const_iterator upper_bound(const Key &key) const
		{
			const_iterator it = begin();

			if (_comp(key, it.base()->pair_data.first))
				return it;

			while (it != end())
			{
				if (key < (*it).first)
				{
					break;
				}
				++it;
			}
			return it;
		}
	};

} // namespace ft

#endif /* ********************************************************* RB_TREE_H */