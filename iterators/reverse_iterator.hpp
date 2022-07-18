/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:16:39 by mababou           #+#    #+#             */
/*   Updated: 2022/07/18 19:09:11 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include <iostream>
# include <string>
# include "iterators_traits.hpp"

namespace ft {

	template< class Iter >
	class reverse_iterator
	: public std::iterator<typename iterator_traits<Iter>::iterator_category,
		typename iterator_traits<Iter>::value_type,
		typename iterator_traits<Iter>::difference_type,
		typename iterator_traits<Iter>::pointer,
		typename iterator_traits<Iter>::reference>
	{
		public:
			typedef iterator_traits<Iter>		traits_type;
			
			typedef	Iter												iterator_type;
			typedef	typename traits_type::iterator_category		iterator_category;
			typedef	typename traits_type::value_type			value_type;
			typedef	typename traits_type::difference_type		difference_type;
			typedef	typename traits_type::pointer				pointer;
			typedef	typename traits_type::reference				reference;
		
			/* CONSTRUCTORS */
			reverse_iterator();										/* 1 */
			explicit reverse_iterator( iterator_type x );			/* 2 */
			template< class U >
			reverse_iterator( const reverse_iterator<U>& other );	/* 3 */

			/* MEMBER FUNCTIONS */
			template< class U >
			reverse_iterator&	operator=( const reverse_iterator<U>& other );
			iterator_type		base() const;
			reference			operator*() const;
			pointer				operator->() const;
			void*				operator[]( difference_type n ) const;
			reverse_iterator&	operator++();
			reverse_iterator&	operator--();
			reverse_iterator	operator++( int );
			reverse_iterator	operator--( int );
			reverse_iterator	operator+( difference_type n ) const;
			reverse_iterator	operator-( difference_type n ) const;
			reverse_iterator&	operator+=( difference_type n );
			reverse_iterator&	operator-=( difference_type n );

		protected:
			iterator_type	current_;
	};

	template< class Iterator1, class Iterator2 >
	bool operator==( const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs );
	template< class Iterator1, class Iterator2 >
	bool operator!=( const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs );
	template< class Iterator1, class Iterator2 >
	bool operator<( const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs );
	template< class Iterator1, class Iterator2 >
	bool operator<=( const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs );
	template< class Iterator1, class Iterator2 >
	bool operator>( const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs );
	template< class Iterator1, class Iterator2 >
	bool operator>=( const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs );

	template< class Iter >
	reverse_iterator<Iter> operator+( 
		typename reverse_iterator<Iter>::difference_type n,
		const reverse_iterator<Iter>& it );
	template< class Iterator >
	typename reverse_iterator<Iterator>::difference_type operator-(
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs );
}

#include "reverse_iterator.tpp"

#endif