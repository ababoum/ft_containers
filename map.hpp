/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 14:06:48 by mababou           #+#    #+#             */
/*   Updated: 2022/06/18 16:53:47 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include "rb_tree/rb_tree.hpp"
#include "rb_tree/tree_utils.hpp"

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
		// typedef	Key										iterator;
		// typedef	Key										const_iterator;
		// typedef	Key										reverse_iterator;
		// typedef	Key										const_reverse_iterator;

	private:
		// This turns a red-black tree into a map
		typedef Allocator::value_type pair_alloc_type;
		typedef _Rb_tree<key_type, value_type, _Select1st<value_type>,
						 key_compare, _Pair_alloc_type>
			struct_type;
		// The actual tree structure
		struct_type _M_t;

	public:
		typedef typename struct_type::iterator iterator;
		typedef typename struct_type::const_iterator const_iterator;
		typedef typename struct_type::reverse_iterator	 reverse_iterator;
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
		/* DESTRUCTOR */
		~map();
	};

} // namespace ft
