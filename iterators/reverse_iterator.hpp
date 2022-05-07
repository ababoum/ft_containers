/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:16:39 by mababou           #+#    #+#             */
/*   Updated: 2022/05/07 18:14:05 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include <iostream>
# include <string>

namespace ft {

	// template< class Iter > struct iterator_traits;
	// template< class T > struct iterator_traits<T*>;
	// template< class T > struct iterator_traits<const T*>;

	template< class Iter >
	class reverse_iterator
	{
		typedef	Iter											iterator_type;
		typedef	ft::iterator_traits<Iter>::iterator_category	iterator_category;
		typedef	ft::iterator_traits<Iter>::value_type			value_type;
		typedef	ft::iterator_traits<Iter>::difference_type		difference_type;
		typedef	ft::iterator_traits<Iter>::pointer				current;
		typedef	ft::iterator_traits<Iter>::reference			reference;
		
		public:
			/* CONSTRUCTORS */
			reverse_iterator();										/* 1 */
			explicit reverse_iterator( iterator_type x );			/* 2 */
			template< class U >
			reverse_iterator( const reverse_iterator<U>& other );	/* 3 */

			/* MEMBER FUNCTIONS */
			template< class U >
			reverse_iterator& operator=( const reverse_iterator<U>& other );
			iterator_type base() const;
			reference operator*() const;
			pointer operator->() const;
			operator[]( difference_type n ) const;
			reverse_iterator& operator++();
			reverse_iterator& operator--();
			reverse_iterator operator++( int );
			reverse_iterator operator--( int );
			reverse_iterator operator+( difference_type n ) const;
			reverse_iterator operator-( difference_type n ) const;
			reverse_iterator& operator+=( difference_type n );
			reverse_iterator& operator-=( difference_type n );

			
		protected:
			iterator_type	current_;
	};

	template< class Iterator1, class Iterator2 >
	bool operator==( const std::reverse_iterator<Iterator1>& lhs,
    	const std::reverse_iterator<Iterator2>& rhs );
	
}

#include "reverse_iterator.tpp"
