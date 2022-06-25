/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 14:06:48 by mababou           #+#    #+#             */
/*   Updated: 2022/06/25 17:33:08 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include "rb_tree/rb_tree.hpp"
#include "rb_tree/tree_utils.hpp"
#include "pairs/pair.hpp"

namespace ft
{

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
		typedef Key value_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef Compare key_compare;
		typedef Allocator allocator_type;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef Allocator::pointer pointer;
		typedef Allocator::const_pointer const_pointer;
		typedef rb_tree_iterator<T> iterator;
		typedef rb_tree_const_iterator<T> const_iterator;
		typedef reverse_iterator<iterator> typedef reverse_iterator<const_iterator> const_reverse_iterator;

	private:
		rb_tree storage;

	public:
		typedef typename struct_type::iterator iterator;
		typedef typename struct_type::const_iterator const_iterator;
		typedef typename struct_type::reverse_iterator reverse_iterator;
		typedef typename struct_type::const_reverse_iterator const_reverse_iterator;

		/* MEMBER CLASSES */

		class value_compare : public std::binary_function<value_type, value_type, bool>
		{
			friend class map;

		protected:
			Compare comp;

			/* Construtor */
			value_compare(Compare _c)
				: comp(_c) {}

		public:
			bool operator()(const value_type &lhs, const value_type &rhs) const
			{
				return comp(lhs.first, rhs.first);
			}
		};

		/* CONSTRUCTORS */

		map() /* 1 */
			: map(Compare())
		{
		}
		explicit map(const Compare &comp,
					 const Allocator &alloc = Allocator()) /* 1 bis */
		{
		}
		template <class InputIt> /* 2 */
		map(InputIt first, InputIt last,
			const Compare &comp = Compare(),
			const Allocator &alloc = Allocator())
		{
		}
		map(const map &other)
		{
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
		}

		const_iterator begin() const
		{
		}

		iterator end()
		{
		}

		const_iterator end() const
		{
		}

		iterator rbegin()
		{
		}

		const_iterator rbegin() const
		{
		}

		iterator rend()
		{
		}

		const_iterator rend() const
		{
		}

		/* CAPACITY */

		bool empty() const
		{
			return storage.empty();
		}

		size_type size() const
		{
			return std::distance(begin(), end());
		}

		size_type max_size() const
		{
			return storage.max_size();
		}

		/* MODIFIERS */

		void clear()
		{
			storage.clear();
		}

		pair<iterator, bool> insert( const value_type& value )		/* 1 */
		{
			
		}

		iterator insert( iterator hint, const value_type& value )	/* 2 */
		{
			
		}

		template< class InputIt >
		void insert( InputIt first, InputIt last )					/* 3 */
		{
			
		}

		void erase( iterator pos )						/* 1 */
		{
			
		}

		void erase( iterator first, iterator last )		/* 2 */
		{
			
		}

		size_type erase( const Key& key )				/* 3 */
		{
			
		}

		void swap( map& other )
		{
			
		}

		/* LOOKUP */

		size_type count( const Key& key ) const
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

		iterator find( const Key& key )
		{
			iterator it = begin();

			while (it != end())
			{
				if (key == (*it).first)
					break ;
				++it;
			}
			return it;
		}

		pair<iterator,iterator> equal_range( const Key& key )
		{
			return make_pair<iterator, iteraotr>(lower_bound(), upper_bound());
		}

		iterator lower_bound( const Key& key )
		{
			iterator it = begin();

			while (it != end())
			{
				if (key == (*it).first)
					break ;
				++it;
			}
			return it;
		}

		const_iterator lower_bound( const Key& key ) const
		{
			const_iterator it = begin();

			while (it != end())
			{
				if (key == (*it).first)
					break ;
				++it;
			}
			return it;
		}

		iterator upper_bound( const Key& key )
		{
			iterator it = begin();

			while (it != end())
			{
				if (key == (*it).first)
				{
					++it;
					break ;
				}
				++it;
			}
			return it;
		}

		const_iterator upper_bound( const Key& key )
		{
			const_iterator it = begin();

			while (it != end())
			{
				if (key == (*it).first)
				{
					++it;
					break ;
				}
				++it;
			}
			return it;
		}
		
		/* OBSERVERS */
		
		key_compare key_comp() const
		{
			return storage.key_comp();
		}

		value_compare value_comp() const
		{
			return value_compare(storage.key_comp());
		}
	};

	template< class Key, class T, class Compare, class Alloc >
bool operator==( const std::map<Key,T,Compare,Alloc>& lhs,
                 const std::map<Key,T,Compare,Alloc>& rhs );

				 template< class Key, class T, class Compare, class Alloc >
bool operator!=( const std::map<Key,T,Compare,Alloc>& lhs,
                 const std::map<Key,T,Compare,Alloc>& rhs );

template< class Key, class T, class Compare, class Alloc >
bool operator<( const std::map<Key,T,Compare,Alloc>& lhs,
                const std::map<Key,T,Compare,Alloc>& rhs );

template< class Key, class T, class Compare, class Alloc >
bool operator<=( const std::map<Key,T,Compare,Alloc>& lhs,
                 const std::map<Key,T,Compare,Alloc>& rhs );

template< class Key, class T, class Compare, class Alloc >
bool operator>( const std::map<Key,T,Compare,Alloc>& lhs,
                const std::map<Key,T,Compare,Alloc>& rhs );

template< class Key, class T, class Compare, class Alloc >
bool operator>=( const std::map<Key,T,Compare,Alloc>& lhs,
                 const std::map<Key,T,Compare,Alloc>& rhs );				
				 

template< class Key, class T, class Compare, class Alloc >
void swap( std::map<Key,T,Compare,Alloc>& lhs,
           std::map<Key,T,Compare,Alloc>& rhs )
		   {
			lhs.swap(rhs);
		   }
} // namespace ft
