/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 14:06:48 by mababou           #+#    #+#             */
/*   Updated: 2022/07/11 20:13:42 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include "rb_tree/RBT.hpp"
#include "rb_tree/tree_utils.hpp"

namespace ft

	template <
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<pair<const Key, T>>>
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
		typedef Allocator::pointer pointer;
		typedef Allocator::const_pointer const_pointer;
		typedef RBT_iterator<T> iterator;
		typedef RBT_const_iterator<T> const_iterator;
		typedef reverse_iterator<iterator> reverse_iterator;
		typedef reverse_iterator<const_iterator> const_reverse_iterator;

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
			const Allocator &alloc = Allocator())
			: _storage()
		{
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

		/* ELEMENT ACCESS */

		T &at(const Key &key) /* 1 */
		{
			iterator it = begin();

			while (it != end())
			{
				if (key == (*it).first)
					return (*it).second;
				++it;
			}
			if (it == end())
				throw std::out_of_range("Specified key is out of range");
		}

		const T &at(const Key &key) const /* 2 */
		{
			const_iterator it = begin();

			while (it != end())
			{
				if (key == (*it).first)
					return (*it).second;
				++it;
			}
			if (it == end())
				throw std::out_of_range("Specified key is out of range");
		}

		T &operator[](const Key &key)
		{
			iterator it = begin();

			while (it != end())
			{
				if (key == (*it).first)
					return (*it).second;
				++it;
			}
			if (it == end())
				return insert(make_pair(key, T())).first->second;
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
			iterator	searched_key;

			searched_key = find(value.first);

			// key found -> no duplicate allowed
			if (find(value.second) != end())
			{
				ret.first = searched_key;
				ret.second = false;
			}
			else
			{
				ret.first = 
			}
		}

		iterator insert(iterator hint, const value_type &value) /* 2 */
		{
		}

		template <class InputIt>
		void insert(InputIt first, InputIt last) /* 3 */
		{
		}

		void erase(iterator pos) /* 1 */
		{
		}

		void erase(iterator first, iterator last) /* 2 */
		{
		}

		size_type erase(const Key &key) /* 3 */
		{
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
			iterator it = begin();

			while (it != end())
			{
				if (key == (*it).first)
					break;
				++it;
			}
			return it;
		}

		pair<iterator, iterator> equal_range(const Key &key)
		{
			return make_pair<iterator, iteraotr>(lower_bound(), upper_bound());
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

		const_iterator upper_bound(const Key &key)
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
	bool operator==(const std::map<Key, T, Compare, Alloc> &lhs,
					const std::map<Key, T, Compare, Alloc> &rhs);

	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const std::map<Key, T, Compare, Alloc> &lhs,
					const std::map<Key, T, Compare, Alloc> &rhs);

	template <class Key, class T, class Compare, class Alloc>
	bool operator<(const std::map<Key, T, Compare, Alloc> &lhs,
				   const std::map<Key, T, Compare, Alloc> &rhs);

	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const std::map<Key, T, Compare, Alloc> &lhs,
					const std::map<Key, T, Compare, Alloc> &rhs);

	template <class Key, class T, class Compare, class Alloc>
	bool operator>(const std::map<Key, T, Compare, Alloc> &lhs,
				   const std::map<Key, T, Compare, Alloc> &rhs);

	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const std::map<Key, T, Compare, Alloc> &lhs,
					const std::map<Key, T, Compare, Alloc> &rhs);

	template <class Key, class T, class Compare, class Alloc>
	void swap(std::map<Key, T, Compare, Alloc> &lhs,
			  std::map<Key, T, Compare, Alloc> &rhs)
	{
		lhs.swap(rhs);
	}
} // namespace ft
