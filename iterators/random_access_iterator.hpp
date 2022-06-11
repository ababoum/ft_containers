/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 22:02:28 by mababou           #+#    #+#             */
/*   Updated: 2022/06/11 18:17:03 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include <iostream>
# include <string>


namespace ft {

	template< typename Iter, typename Container >
	class random_access_iterator
	{
		private:
		
			typedef iterator_traits<Iter>	traits_type;
			Iter							_current;
		public:

			
			typedef	Iter				iterator_type;
			typedef Iter*				pointer;
			typedef Iter&				reference;
			typedef typename traits_type::iterator_category	iterator_category;
			typedef typename traits_type::value_type			value_type;
			typedef typename traits_type::difference_type	difference_type;


			/* CONSTRUCTORS */
			random_access_iterator();										/* 1 */
			explicit random_access_iterator( pointer x );					/* 2 */
			template< class U >
			random_access_iterator( const random_access_iterator<U, Container>& other );	/* 3 */

			/* MEMBER FUNCTIONS */
			template< class U >
			random_access_iterator& operator=( const random_access_iterator<U, Container>& other );
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
			
	};

	template< class T1, class T2, typename Container >
	bool operator==( const random_access_iterator<T1, Container>& lhs,
		const random_access_iterator<T2, Container>& rhs );
	template< class T1, class T2, typename Container >
	bool operator!=( const random_access_iterator<T1, Container>& lhs,
		const random_access_iterator<T2, Container>& rhs );
	template< class T1, class T2, typename Container >
	bool operator<( const random_access_iterator<T1, Container>& lhs,
		const random_access_iterator<T2, Container>& rhs );
	template< class T1, class T2, typename Container >
	bool operator<=( const random_access_iterator<T1, Container>& lhs,
		const random_access_iterator<T2, Container>& rhs );
	template< class T1, class T2, typename Container >
	bool operator>( const random_access_iterator<T1, Container>& lhs,
		const random_access_iterator<T2, Container>& rhs );
	template< class T1, class T2, typename Container >
	bool operator>=( const random_access_iterator<T1, Container>& lhs,
		const random_access_iterator<T2, Container>& rhs );

	template< class Iter, typename Container >
	random_access_iterator<Iter, Container> operator+( 
		typename random_access_iterator<Iter, Container>::difference_type n,
		const random_access_iterator<Iter, Container>& it );
	template< class Iter, typename Container >
	typename random_access_iterator<Iter, Container>::difference_type operator-(
		const random_access_iterator<Iter, Container>& lhs,
		const random_access_iterator<Iter, Container>& rhs );

} // namespace ft

# include "random_access_iterator.tpp"

#endif