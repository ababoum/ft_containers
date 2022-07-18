/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 14:06:48 by mababou           #+#    #+#             */
/*   Updated: 2022/07/18 20:04:55 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include "rb_tree/RBT.hpp"
#include "rb_tree/tree_utils.hpp"
#include "utils/enable_if.hpp"
#include "utils/is_integral.hpp"

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
		typedef pair<const key_type,mapped_type> value_type;
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
		typedef reverse_iterator<const_iterator> const_reverse_iterator;
		typedef reverse_iterator<iterator> reverse_iterator;

	private:
		typedef RBT<Key, T, key_compare, allocator_type> RBT_map;

		RBT_map _storage;

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
				insert(*it);
			}			
		}

		/* 3 */
		map(const map &other)
		{
			for (iterator it = other.begin(); it != other.end(); ++it) {
				insert(*it);
			}
		}

		/* DESTRUCTOR */

		~map();

		/* MEMBER FUNCTIONS */

		map& operator=( const map& other )
		{
			clear();
			
			for (iterator it = other.begin(); it != other.end(); ++it) {
				insert(*it);
			}
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

		pair<iterator, bool> insert(const value_type &value) /* 1 */
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
			else if (searched_key != end())
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

		iterator insert(iterator hint, const value_type &value) /* 2 */
		{
			iterator searched_key = find(value.first);

			// is map is empty, insert the node
			if (empty())
			{
				return _storage.insert_node(value);
			}
			// key found -> no duplicate allowed
			else if (searched_key != end())
			{
				return searched_key;
			}
			// no key found, proceed with inserting the node
			else
			{
				return _storage.insert_node_loc(hint, value);
			}
		}

		template <class InputIt>
		void insert(InputIt first, InputIt last) /* 3 */
		{
			for (InputIt it = first; it != last; ++it) {
				insert(*it);
			}
		}

		void erase(iterator pos) /* 1 */
		{
			_storage.erase_node(pos);
		}

		void erase(iterator first, iterator last) /* 2 */
		{
			iterator tmp;
			iterator it = first;
			
			while(it != last) {
				tmp = ++it;
				erase(it);
				it = tmp;
			}
		}

		size_type erase(const Key &key) /* 3 */
		{
			iterator searched_key = find(key);

			// if map is empty, do nothing
			if (empty())
			{
				return 0;
			}
			// key is found
			else if (searched_key != end())
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
			iterator it = begin();

			while (it != end())
			{
				if (key == (*it).first)
					return 1;
				++it;
			}
			if (it == end())
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
		
		pair<iterator, iterator> equal_range(const Key &key)
		{
			return make_pair<iterator, iterator>(lower_bound(key), upper_bound(key));
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
			return equal(
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
		if (lhs.size() != rhs.size())
			return lhs.size() < rhs.size();
		else
		{
			return lexicographical_compare(
				lhs.begin(), lhs.end(), rhs.begin(), lhs.end());
		}
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