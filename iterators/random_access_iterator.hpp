/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 22:02:28 by mababou           #+#    #+#             */
/*   Updated: 2022/05/07 22:50:55 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include <iostream>
# include <string>

namespace ft {

	template< class T >
	class random_access_iterator: public std::iterator < std::random_access_iterator_tag, T >
	{
		public:
			
			typedef	T				iterator_type;
			typedef T*				pointer;
			typedef T&				reference;
			typedef typename std::iterator<std::random_access_iterator_tag, T>::iterator_category     iterator_category;
			typedef typename std::iterator<std::random_access_iterator_tag, T>::value_type            value_type;
			typedef typename std::iterator<std::random_access_iterator_tag, T>::difference_type       difference_type;



			/* CONSTRUCTORS */
			random_access_iterator();										/* 1 */
			explicit random_access_iterator( pointer x );					/* 2 */
			template< class U >
			random_access_iterator( const random_access_iterator<U>& other );	/* 3 */

			/* MEMBER FUNCTIONS */
			template< class U >
			random_access_iterator& operator=( const random_access_iterator<U>& other );
			pointer base() const;
			reference operator*() const;
			pointer operator->() const;
			value_type operator[]( difference_type n ) const;
			random_access_iterator& operator++();
			random_access_iterator& operator--();
			random_access_iterator operator++( int );
			random_access_iterator operator--( int );
			random_access_iterator operator+( difference_type n ) const;
			random_access_iterator operator-( difference_type n ) const;
			random_access_iterator& operator+=( difference_type n );
			random_access_iterator& operator-=( difference_type n );

		private:
			pointer	_current;
			
	};

	template< class T1, class T2 >
	bool operator==( const ft::random_access_iterator<T1>& lhs,
		const ft::random_access_iterator<T2>& rhs );
	template< class T1, class T2 >
	bool operator!=( const ft::random_access_iterator<T1>& lhs,
		const ft::random_access_iterator<T2>& rhs );
	template< class T1, class T2 >
	bool operator<( const ft::random_access_iterator<T1>& lhs,
		const ft::random_access_iterator<T2>& rhs );
	template< class T1, class T2 >
	bool operator<=( const ft::random_access_iterator<T1>& lhs,
		const ft::random_access_iterator<T2>& rhs );
	template< class T1, class T2 >
	bool operator>( const ft::random_access_iterator<T1>& lhs,
		const ft::random_access_iterator<T2>& rhs );
	template< class T1, class T2 >
	bool operator>=( const ft::random_access_iterator<T1>& lhs,
		const ft::random_access_iterator<T2>& rhs );

	template< class T >
	random_access_iterator<T> operator+( 
		typename random_access_iterator<T>::difference_type n,
		const random_access_iterator<T>& it );
	template< class T >
	typename random_access_iterator<T>::difference_type operator-(
		const random_access_iterator<T>& lhs,
		const random_access_iterator<T>& rhs );

} // namespace ft

# include "random_access_iterator.tpp"

#endif