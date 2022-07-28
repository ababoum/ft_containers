/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 14:06:48 by mababou           #+#    #+#             */
/*   Updated: 2022/07/28 15:30:56 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include "rb_tree/RBT.hpp"
#include "utils/enable_if.hpp"
#include "utils/is_integral.hpp"
#include "utils/equal.hpp"
#include "utils/lexicographical_compare.hpp"

namespace ft
{
	template <
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<pair<const Key, T> > >
	class map
	{
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef pair<const key_type, mapped_type> value_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef Compare key_compare;
		typedef Allocator allocator_type;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::const_pointer const_pointer;
		typedef RBT_iterator<Key, T> iterator;
		typedef RBT_const_iterator<Key, T> const_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;

	private:
		typedef RBT<Key, T, key_compare, allocator_type> _RBT_map;
		typedef pair<key_type, mapped_type> _muggle_pair;

		_RBT_map _storage;


		pair<iterator, bool> _insertPair(const _muggle_pair & item)
		{
			pair<iterator, bool> ret;
			iterator searched_key = find(item.first);

			value_type item_to_insert(item.first, item.second);

			// if map is empty, insert the node
			if (empty())
			{
				ret.first = _storage.insert_node(item_to_insert);
				ret.second = true;
			}
			// key found -> no duplicate allowed
			else if (!searched_key.base()->is_nil)
			{
				ret.first = searched_key;
				ret.second = false;
			}
			// no key found, proceed with inserting the node
			else
			{
				ret.first = _storage.insert_node(item_to_insert);
				ret.second = true;
			}
			return ret;
		}

		pair<iterator, bool> _insertPair(const value_type & item)
		{
			pair<iterator, bool> ret;
			iterator searched_key = find(item.first);

			// if map is empty, insert the node
			if (empty())
			{
				ret.first = _storage.insert_node(item);
				ret.second = true;
			}
			// key found -> no duplicate allowed
			else if (!searched_key.base()->is_nil)
			{
				ret.first = searched_key;
				ret.second = false;
			}
			// no key found, proceed with inserting the node
			else
			{
				ret.first = _storage.insert_node(item);
				ret.second = true;
			}
			return ret;
		}

		iterator _insertPair_hint(iterator hint, const _muggle_pair & item)
		{
			iterator searched_key = find(item.first);
			value_type item_to_insert(item.first, item.second);

			// is map is empty, insert the node
			if (empty())
			{
				return _storage.insert_node(item_to_insert);
			}
			// key found -> no duplicate allowed
			else if (!searched_key.base()->is_nil)
			{
				return searched_key;
			}
			// no key found, proceed with inserting the node
			else
			{
				return _storage.insert_node_loc(hint, item_to_insert);
			}
		}

		iterator _insertPair_hint(iterator hint, const value_type & item)
		{
			iterator searched_key = find(item.first);

			// is map is empty, insert the node
			if (empty())
			{
				return _storage.insert_node(item);
			}
			// key found -> no duplicate allowed
			else if (!searched_key.base()->is_nil)
			{
				return searched_key;
			}
			// no key found, proceed with inserting the node
			else
			{
				return _storage.insert_node_loc(hint, item);
			}
		}
		
	public:
		/* MEMBER CLASSES */

		class value_compare : public std::binary_function<value_type, value_type, bool>
		{
			friend class map;

		protected:
			Compare comp;

			value_compare(Compare _c)
				: comp(_c) {}

		public:
			bool operator()(const value_type &lhs, const value_type &rhs) const
			{
				return comp(lhs.first, rhs.first);
			}
		};

		/* CONSTRUCTORS */

		/* 1 */
		map()
			: _storage() {}

		/* 1 bis */
		explicit map(const Compare &comp,
			const Allocator &alloc = Allocator())
			: _storage()
		{
			_storage.setAllocator(alloc);
			_storage.setComp(comp);
		}

		/* 2 */
		template <class InputIt>
		map(InputIt first, InputIt last,
			const Compare &comp = Compare(),
			const Allocator &alloc = Allocator(),
			typename enable_if<!ft::is_integral< InputIt >::value, void* >::type* = NULL)
			: _storage()
		{
			_storage.setAllocator(alloc);
			_storage.setComp(comp);
			for (InputIt it = first; it != last; ++it) {
				_insertPair(*it);
			}			
		}

		/* 3 */
		map(const map &other)
		{
			for (const_iterator it = other.begin(); it != other.end(); ++it) {
				_insertPair(*it);
			}
		}

		/* DESTRUCTOR */

		~map()
		{
			clear();
		}

		/* MEMBER FUNCTIONS */

		map& operator=( const map& other )
		{
			clear();
			
			for (const_iterator it = other.begin(); it != other.end(); ++it) {
				insert(*it);
			}
			
			return (*this);
		}
		
		allocator_type get_allocator() const
		{
			return _storage.getAllocator();
		}

		/* ELEMENT ACCESS */

		T &at(const Key &key) /* 1 */
		{
			return _storage.at(key);
		}

		const T &at(const Key &key) const /* 2 */
		{
			return _storage.at(key);
		}

		T &operator[](const Key &key)
		{
			return _storage.getRef_or_insert(key);
		}

		/* ITERATORS */

		iterator begin()
		{
			return _storage.begin();
		}

		const_iterator begin() const
		{
			return _storage.begin();
		}

		iterator end()
		{
			return _storage.end();
		}

		const_iterator end() const
		{
			return _storage.end();
		}

		reverse_iterator rbegin()
		{
			return _storage.rbegin();
		}

		const_reverse_iterator rbegin() const
		{
			return _storage.rbegin();
		}

		reverse_iterator rend()
		{
			return _storage.rend();
		}

		const_reverse_iterator rend() const
		{
			return _storage.rend();
		}

		/* CAPACITY */

		bool empty() const
		{
			return _storage.empty();
		}

		size_type size() const
		{
			return _storage.size();
		}

		size_type max_size() const
		{
			return _storage.max_size();
		}
	
		/* MODIFIERS */

		void clear()
		{
			_storage.clear();
		}

		/* 1 */
		pair<iterator, bool> insert(const value_type &value)
		{
			pair<iterator, bool> ret;
			iterator searched_key = find(value.first);

			// if map is empty, insert the node
			if (empty())
			{
				ret.first = _storage.insert_node(value);
				ret.second = true;
			}
			// key found -> no duplicate allowed
			else if (!searched_key.base()->is_nil)
			{
				ret.first = searched_key;
				ret.second = false;
			}
			// no key found, proceed with inserting the node
			else
			{
				ret.first = _storage.insert_node(value);
				ret.second = true;
			}
			return ret;
		}

		/* 2 */
		iterator insert(iterator hint, const value_type &value)
		{
			iterator ret;

			ret = _insertPair_hint(hint, value);
			return ret;
		}

		/* 3 */
		template <class InputIt>
		void insert(InputIt first, InputIt last)
		{
			for (InputIt it = first; it != last; ++it) {
				_insertPair(*it);
			}
		}

		/* 1 */
		void erase(iterator pos)
		{
			_storage.erase_node(pos);
		}

		/* 2 */
		void erase(iterator first, iterator last)
		{
			iterator tmp;
			iterator it = first;
			
			while (it != last) {
				tmp = it + 1;
				erase(it);
				it = tmp;
			}
		}

		/* 3 */
		size_type erase(const Key &key)
		{
			iterator searched_key = find(key);

			// if map is empty, do nothing
			if (empty())
			{
				return 0;
			}
			// key is found
			else if (!searched_key.base()->is_nil)
			{
				erase(searched_key);
				return 1;
			}
			else
			{
				return 0;
			}
		}

		void swap(map &other)
		{
			_storage.swap(other._storage);
		}

		/* LOOKUP */

		size_type count(const Key &key) const
		{
			const_iterator it = begin();

			while (!it.base()->is_nil)
			{
				if (key == (*it).first)
					return 1;
				++it;
			}
			return 0;
		}

		iterator find(const Key &key)
		{
			return _storage.find(key);
		}

		const_iterator find( const Key& key ) const
		{
			return _storage.find(key);
		}

		pair<const_iterator,const_iterator> equal_range (const key_type& key) const
		{
			pair<const_iterator,const_iterator> ret(lower_bound(key), upper_bound(key));
			
			return ret;
		}
		
		pair<iterator, iterator> equal_range(const key_type &key)
		{
			pair<iterator, iterator> ret(lower_bound(key), upper_bound(key));
			
			return ret;
		}

		iterator lower_bound(const Key &key)
		{
			return _storage.lower_bound(key);
		}

		const_iterator lower_bound(const Key &key) const
		{
			return _storage.lower_bound(key);
		}

		iterator upper_bound(const Key &key)
		{
			return _storage.upper_bound(key);
		}

		const_iterator upper_bound(const Key &key) const
		{
			return _storage.upper_bound(key);
		}

		/* OBSERVERS */

		key_compare key_comp() const
		{
			return _storage.key_comp();
		}

		value_compare value_comp() const
		{
			return value_compare(_storage.key_comp());
		}
	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		else
		{
			return ft::equal(
				lhs.begin(), lhs.end(), rhs.begin());
		}
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<(const map<Key, T, Compare, Alloc> &lhs,
				   const map<Key, T, Compare, Alloc> &rhs)
	{
		return ft::lexicographical_compare(
			lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs)
	{
		return (lhs < rhs || lhs == rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>(const map<Key, T, Compare, Alloc> &lhs,
				   const map<Key, T, Compare, Alloc> &rhs)
	{
		return !(lhs <= rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs)
	{
		return !(lhs < rhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	void swap(map<Key, T, Compare, Alloc> &lhs,
			  map<Key, T, Compare, Alloc> &rhs)
	{
		lhs.swap(rhs);
	}

} // namespace ft

#endif /* ************************************************************* MAP_H */