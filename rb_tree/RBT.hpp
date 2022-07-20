/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 20:27:11 by mababou           #+#    #+#             */
/*   Updated: 2022/07/20 16:33:39 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_HPP
#define RBT_HPP

#include <iostream>
#include "../pairs/pair.hpp"
#include "../iterators/reverse_iterator.hpp"

namespace ft
{

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
		value_type pair;
		bool is_nil;

		RBT_node(value_type pair_init)
		{
			pair = pair_init;
		}
		
		value_type *value_ptr()
		{
			return &(pair);
		}

		const value_type *value_ptr() const
		{
			return &(pair);
		}
	};

	// iterator increment/decrement

	template <class Key, class T>
	static RBT_node<Key, T> *
	local_rb_tree_increment(RBT_node<Key, T> *node_ptr) throw()
	{
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
			while (!tmp_node->is_nil && node_ptr == tmp_node->right)
			{
				node_ptr = tmp_node;
				tmp_node = tmp_node->parent;
			}
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
			while (!tmp_node->is_nil && node_ptr == tmp_node->left)
			{
				node_ptr = tmp_node;
				tmp_node = tmp_node->parent;
			}
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

		base_ptr node_ptr;

		RBT_iterator()
			: node_ptr() {}

		explicit RBT_iterator(base_ptr node_ptr_input)
			: node_ptr(node_ptr_input) {}

		base_ptr
		base()
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

		friend bool
		operator==(const iterator &lhs, const iterator &rhs)
		{
			return lhs.node_ptr == rhs.node_ptr;
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

		explicit RBT_const_iterator(base_ptr node_ptr_input)
			: node_ptr(node_ptr_input) {}

		RBT_const_iterator(const iterator &it)
			: node_ptr(it.node_ptr) {}

		base_ptr
		base()
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

		friend bool
		operator==(const const_iterator &lhs, const const_iterator &rhs)
		{
			return lhs.node_ptr == rhs.node_ptr;
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
		typedef RBT_node<Key, T> *base_ptr;

		typedef RBT_iterator<Key, T> iterator;
		typedef RBT_const_iterator<Key, T> const_iterator;
		typedef reverse_iterator<const_iterator> const_reverse_iterator;
		typedef reverse_iterator<iterator> reverse_iterator;

	private:
		base_ptr _root;
		base_ptr _null_node;
		size_type _node_count;
		pair_allocator _pair_alloc;
		node_allocator _node_alloc;
		key_compare _comp;

		void _initializeNULLNode(base_ptr node, base_ptr parent)
		{
			_pair_alloc.construct(&node->pair, value_type());
			node->parent = parent;
			node->left = NULL;
			node->right = NULL;
			node->color = _S_black;
			node->is_nil = true;
		}

		// helper functions

		base_ptr _searchTreeHelper(base_ptr node, Key key)
		{
			if (node == _null_node || key == node->pair.first)
			{
				return node;
			}

			if (key < node->pair.first)
			{
				return _searchTreeHelper(node->left, key);
			}
			return _searchTreeHelper(node->right, key);
		}

		// For balancing the tree after deletion
		void _deleteRebalance(base_ptr x)
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

		void _rbTransplant(base_ptr u, base_ptr v)
		{
			if (u->parent == NULL)
				_root = v;
			else if (u == u->parent->left)
				u->parent->left = v;
			else
				u->parent->right = v;
			v->parent = u->parent;
		}

		void _deleteNodeHelper(base_ptr node, Key key)
		{
			base_ptr z = _null_node;
			base_ptr x;
			base_ptr y;

			while (node != _null_node)
			{
				if (node->pair.first == key)
					z = node;

				if (node->pair.first <= key)
					node = node->right;
				else
					node = node->left;
			}

			if (z == _null_node)
			{
				return;
			}

			y = z;
			bool y_original_color = y->color;

			if (z->left == _null_node)
			{
				x = z->right;
				_rbTransplant(z, z->right);
			}
			else if (z->right == _null_node)
			{
				x = z->left;
				_rbTransplant(z, z->left);
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
					_rbTransplant(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}

				_rbTransplant(z, y);
				y->left = z->left;
				y->left->parent = y;
				y->color = z->color;
			}

			delete z;
			if (y_original_color == _S_black)
				_deleteRebalance(x);
		}

		// For balancing the tree after insertion
		void _insertRebalance(base_ptr k)
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

		base_ptr _minimum(base_ptr node)
		{
			while (node->left != _null_node)
				node = node->left;
			return node;
		}

		base_ptr _maximum(base_ptr node)
		{
			while (node->right != _null_node)
				node = node->right;
			return node;
		}

		void _leftRotate(base_ptr x)
		{
			base_ptr y = x->right;
			x->right = y->left;
			if (y->left != _null_node)
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
			if (y->right != _null_node)
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

	public:
		RBT()
		{
			_null_node = _node_alloc.allocate(sizeof(RBT_node<Key, T>));

			_node_count = 0;
			_pair_alloc = pair_allocator();
			_node_alloc = node_allocator();
			_comp = key_compare();
			_root = _null_node;

			// null node initialization
			_null_node->color = _S_black;
			_null_node->left = NULL;
			_null_node->right = NULL;
		}

		// Inserting a node
		base_ptr insert(value_type pair_to_add)
		{
			base_ptr node = _node_alloc.allocate(sizeof(RBT_node<Key, T>));
			_node_alloc.construct(node, 0);
			node->parent = NULL;
			node->pair.first = pair_to_add.first;
			node->left = _null_node;
			node->right = _null_node;
			node->color = _S_red;
			node->is_nil = false;

			base_ptr y = NULL;
			base_ptr x = this->_root;

			while (x != _null_node)
			{
				y = x;
				if (node->pair.first < x->pair.first)
					x = x->left;
				else
					x = x->right;
			}

			node->parent = y;
			if (y == NULL)
				_root = node;
			else if (node->pair.first < y->pair.first)
				y->left = node;
			else
				y->right = node;

			if (node->parent == NULL)
			{
				node->color = 0;
				return;
			}

			if (node->parent->parent == NULL)
				return;

			_insertRebalance(node);
			++_node_count;

			return node;
		}

		base_ptr insert_hint(value_type pair_to_add, iterator hint)
		{
			base_ptr node = _node_alloc.allocate(sizeof(RBT_node<Key, T>));
			_node_alloc.construct(node, 0);
			node->parent = NULL;
			node->pair.first = pair_to_add.first;
			node->left = _null_node;
			node->right = _null_node;
			node->color = _S_red;
			node->is_nil = false;

			base_ptr y = NULL;
			base_ptr x = hint.base();

			while (x != _null_node)
			{
				y = x;
				if (node->pair.first < x->pair.first)
					x = x->left;
				else
					x = x->right;
			}

			node->parent = y;
			if (y == NULL)
				_root = node;
			else if (node->pair.first < y->pair.first)
				y->left = node;
			else
				y->right = node;

			if (node->parent == NULL)
			{
				node->color = 0;
				return;
			}

			if (node->parent->parent == NULL)
				return;

			_insertRebalance(node);
			++_node_count;

			return node;
		}

		void deleteNode(Key key)
		{
			_deleteNodeHelper(this->_root, key);
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
			return _searchTreeHelper(_root, k);
		}

		mapped_type &at(const key_type &key)
		{
			base_ptr searched_node = searchTree(key);

			if (searched_node == _null_node)
				throw std::out_of_range("Specified key is out of range");
			else
				return searched_node->pair.second;
		}

		const mapped_type &at(const key_type &key) const
		{
			base_ptr searched_node = searchTree(key);

			if (searched_node == _null_node)
				throw std::out_of_range("Specified key is out of range");
			else
				return searched_node->pair.second;
		}

		mapped_type &getRef_or_insert(const key_type &key)
		{
			base_ptr searched_node = searchTree(key);

			if (searched_node == _null_node)
				searched_node = insert(make_pair(key, mapped_type()));
			else
				return searched_node->pair.second;
		}

		/* MODIFIERS */

		// Is called only after checking if key doesn't exist already
		iterator insert_node(const value_type &value)
		{
			base_ptr *node_inserted;

			node_inserted = insert(value);
			iterator ret(node_inserted);

			return ret;
		}

		iterator insert_node_loc(iterator pos_to_attach, const value_type &value)
		{
			base_ptr *node_inserted;

			node_inserted = insert_hint(value, pos_to_attach);
			iterator ret(node_inserted);

			return ret;
		}

		void erase_node(iterator pos)
		{
			base_ptr node_to_be_deleted = pos.node_ptr;

			node_to_be_deleted =
				Rb_tree_rebalance_for_erase(node_to_be_deleted, _root);
			_node_alloc.destroy(node_to_be_deleted);

			--_node_count;
		}

		void clear(void)
		{
			iterator tmp = begin();
			iterator tmp_next = tmp + 1;

			while (!tmp->is_nil)
			{
				base_ptr node_to_destroy = tmp.base();

				_node_alloc.destroy(node_to_destroy);
				_node_alloc.deallocate(node_to_destroy);

				tmp = tmp_next;
				++tmp_next;
			}
		}

		void swap(RBT &other)
		{
			std::swap(_root, other._root);
			std::swap(_node_count, other._node_count);
			std::swap(_pair_alloc, other._pair_alloc);
			std::swap(_node_alloc, other._node_alloc);
			std::swap(_comp, other._comp);
		}

		/* ITERATORS */
		iterator begin(void)
		{
			base_ptr node = _minimum(_root);
			return RBT_iterator<Key, T>(node);
		}

		const_iterator begin() const
		{
			base_ptr node = _minimum(_root);
			return RBT_const_iterator<Key, T>(node);
		}

		iterator end()
		{
			return RBT_iterator<Key, T>(_null_node);
		}

		const_iterator end() const
		{
			return RBT_const_iterator<Key, T>(_null_node);
		}

		reverse_iterator rbegin(void)
		{
			base_ptr node = _maximum(_root);
			return RBT_iterator<Key, T>(node);
		}

		const_reverse_iterator rbegin() const
		{
			base_ptr node = _maximum(_root);
			return RBT_const_iterator<Key, T>(node);
		}

		reverse_iterator rend()
		{
			return RBT_iterator<Key, T>(_null_node);
		}

		const_reverse_iterator rend() const
		{
			return RBT_const_iterator<Key, T>(_null_node);
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

			iterator ret(node_to_find);

			return (ret);
		}

		const_iterator find(const Key &key) const
		{
			base_ptr node_to_find = searchTree(key);

			const_iterator ret(node_to_find);

			return (ret);
		}

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

		const_iterator upper_bound(const Key &key) const
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
	};

} // namespace ft

#endif /* ********************************************************* RB_TREE_H */