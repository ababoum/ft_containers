/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 14:06:48 by mababou           #+#    #+#             */
/*   Updated: 2022/06/16 20:28:46 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include "rb_tree/rb_tree.hpp"

namespace ft {

template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<pair<const Key, T> >
>
class map
{
	public:

		typedef	Key											key_type;
		typedef	T											mapped_type;
		typedef	Key											value_type;
		typedef	std::size_t									size_type;
		typedef	std::ptrdiff_t								difference_type;
		typedef	Compare										key_compare;
		typedef	Allocator									allocator_type;
		typedef	value_type&									reference;
		typedef	const value_type&							const_reference;
		typedef	Allocator::pointer							pointer;
		typedef	Allocator::const_pointer					const_pointer;
		// typedef	Key										iterator;
		// typedef	Key										const_iterator;
		// typedef	Key										reverse_iterator;
		// typedef	Key										const_reverse_iterator;

	private:
		// This turns a red-black tree into a map

		// The actual tree structure
      	tree_type _tree;


		/* MEMBER CLASSES */

		class value_compare: public std::binary_function<value_type, value_type, bool>
		{
			friend class map;
			protected:
				Compare comp;

				/* Construtor */
				value_compare(Compare _c)
				: comp(_c) { }

			public:
				bool operator()(const value_type& lhs, const value_type& rhs) const
			{ return comp(lhs.first, rhs.first); }
		};

		/* CONSTRUCTORS */

		map() /* 1 */
		: map(Compare()) { }
		explicit map( const Compare& comp,
					const Allocator& alloc = Allocator() ) /* 1 bis */
		{
			
		}
		/* DESTRUCTOR */
		~map();
		
		/* GENERAL MEMBER FUNCTIONS */


		/* ELEMENT ACCESS  */
		
		/* ITERATORS */

		/* CAPACITY */

		/* MODIFIERS */
		
	private:

};

} // namespace ft


#endif /* ************************************************************* MAP_H */