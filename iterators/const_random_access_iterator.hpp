/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const_random_access_iterator.hpp                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 22:02:28 by mababou           #+#    #+#             */
/*   Updated: 2022/05/09 17:25:17 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONST_RANDOM_ACCESS_ITERATOR_HPP
# define CONST_RANDOM_ACCESS_ITERATOR_HPP

# include <iostream>
# include <string>

namespace ft {

	template< class T >
	class const_random_access_iterator: public std::iterator < std::random_access_iterator_tag, T >
	{
		public:
			
			typedef	T				iterator_type;
			typedef T*				pointer;
			typedef T&				reference;
			typedef typename std::iterator<std::random_access_iterator_tag, T>::iterator_category     iterator_category;
			typedef typename std::iterator<std::random_access_iterator_tag, T>::value_type            value_type;
			typedef typename std::iterator<std::random_access_iterator_tag, T>::difference_type       difference_type;



			/* CONSTRUCTORS */
			const_random_access_iterator();										/* 1 */
			explicit const_random_access_iterator( pointer x );					/* 2 */
			template< class U >
			const_random_access_iterator( const random_access_iterator<U>& other );	/* 3 */

			/* MEMBER FUNCTIONS */
			template< class U >
			const_random_access_iterator& operator=( const random_access_iterator<U>& other );
			pointer base() const;
			reference operator*() const;
			pointer operator->() const;
			value_type operator[]( difference_type n ) const;
			const_random_access_iterator& operator++();
			const_random_access_iterator& operator--();
			const_random_access_iterator operator++( int );
			const_random_access_iterator operator--( int );
			const_random_access_iterator operator+( difference_type n ) const;
			const_random_access_iterator operator-( difference_type n ) const;
			const_random_access_iterator& operator+=( difference_type n );
			const_random_access_iterator& operator-=( difference_type n );

		private:
			pointer	_current;
			
	};

	template< class T1, class T2 >
	bool operator==( const const_random_access_iterator<T1>& lhs,
		const const_random_access_iterator<T2>& rhs );
	template< class T1, class T2 >
	bool operator!=( const const_random_access_iterator<T1>& lhs,
		const const_random_access_iterator<T2>& rhs );
	template< class T1, class T2 >
	bool operator<( const const_random_access_iterator<T1>& lhs,
		const const_random_access_iterator<T2>& rhs );
	template< class T1, class T2 >
	bool operator<=( const const_random_access_iterator<T1>& lhs,
		const const_random_access_iterator<T2>& rhs );
	template< class T1, class T2 >
	bool operator>( const const_random_access_iterator<T1>& lhs,
		const const_random_access_iterator<T2>& rhs );
	template< class T1, class T2 >
	bool operator>=( const const_random_access_iterator<T1>& lhs,
		const const_random_access_iterator<T2>& rhs );

	template< class T >
	const_random_access_iterator<T> operator+( 
		typename const_random_access_iterator<T>::difference_type n,
		const const_random_access_iterator<T>& it );
	template< class T >
	typename const_random_access_iterator<T>::difference_type operator-(
		const const_random_access_iterator<T>& lhs,
		const const_random_access_iterator<T>& rhs );

} // namespace ft

# include "const_random_access_iterator.tpp"

#endif