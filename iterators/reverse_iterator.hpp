/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:16:39 by mababou           #+#    #+#             */
/*   Updated: 2022/05/07 23:05:51 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include <iostream>
# include <string>

namespace ft {

	template< class T >
	class reverse_iterator
	{
		typedef	T													iterator_type;
		typedef	typename ft::iterator_traits<T>::iterator_category	iterator_category;
		typedef	typename ft::iterator_traits<T>::value_type			value_type;
		typedef	typename ft::iterator_traits<T>::difference_type	difference_type;
		typedef	typename ft::iterator_traits<T>::pointer			pointer;
		typedef	typename ft::iterator_traits<T>::reference			reference;
		
		public:
			/* CONSTRUCTORS */
			reverse_iterator();										/* 1 */
			explicit reverse_iterator( pointer x );					/* 2 */
			template< class U >
			reverse_iterator( const reverse_iterator<U>& other );	/* 3 */

			/* MEMBER FUNCTIONS */
			template< class U >
			reverse_iterator& operator=( const reverse_iterator<U>& other );
			pointer base() const;
			reference operator*() const;
			pointer operator->() const;
			value_type operator[]( difference_type n ) const;
			reverse_iterator& operator++();
			reverse_iterator& operator--();
			reverse_iterator operator++( int );
			reverse_iterator operator--( int );
			reverse_iterator operator+( difference_type n ) const;
			reverse_iterator operator-( difference_type n ) const;
			reverse_iterator& operator+=( difference_type n );
			reverse_iterator& operator-=( difference_type n );

			
		protected:
			pointer	current_;
	};

	template< class T1, class T2 >
	bool operator==( const ft::reverse_iterator<T1>& lhs,
		const ft::reverse_iterator<T2>& rhs );
	template< class T1, class T2 >
	bool operator!=( const ft::reverse_iterator<T1>& lhs,
		const ft::reverse_iterator<T2>& rhs );
	template< class T1, class T2 >
	bool operator<( const ft::reverse_iterator<T1>& lhs,
		const ft::reverse_iterator<T2>& rhs );
	template< class T1, class T2 >
	bool operator<=( const ft::reverse_iterator<T1>& lhs,
		const ft::reverse_iterator<T2>& rhs );
	template< class T1, class T2 >
	bool operator>( const ft::reverse_iterator<T1>& lhs,
		const ft::reverse_iterator<T2>& rhs );
	template< class T1, class T2 >
	bool operator>=( const ft::reverse_iterator<T1>& lhs,
		const ft::reverse_iterator<T2>& rhs );

	template< class T >
	reverse_iterator<T> operator+( 
		typename reverse_iterator<T>::difference_type n,
		const reverse_iterator<T>& it );
	template< class Iterator >
	typename reverse_iterator<Iterator>::difference_type operator-(
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs );
}

#include "reverse_iterator.tpp"

#endif