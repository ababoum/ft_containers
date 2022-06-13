/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.tpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:49:07 by mababou           #+#    #+#             */
/*   Updated: 2022/06/13 18:07:39 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "random_access_iterator.hpp"

namespace ft {

/*
** ------------------------------- CONSTRUCTORS -------------------------------
*/

template< typename Iter, typename Container >					/* 1 */
random_access_iterator<Iter, Container>::random_access_iterator()
: _current(Iter()) {}

template< typename Iter, typename Container >					/* 2 */
random_access_iterator<Iter, Container>::random_access_iterator
(typename random_access_iterator<Iter, Container>::pointer x)
: _current(x) {}



template< typename Iter, typename Container >					/* 3 */
template< typename U >
random_access_iterator<Iter, Container>::random_access_iterator
(const random_access_iterator<U, Container>& other)
: _current(other.base()) {}

/*
** ----------------------------- MEMBER FUNCTIONS -----------------------------
*/


template< typename Iter, typename Container >	
template< typename U >
random_access_iterator<Iter, Container>&
random_access_iterator<Iter, Container>::operator=( const random_access_iterator<U, Container>& other )
{
	this->base() = other->base();
	return (*this);
}

template< typename Iter, typename Container >
typename random_access_iterator<Iter, Container>::pointer
random_access_iterator<Iter, Container>::base() const
{
	return (_current);
}

template< typename Iter, typename Container >
typename random_access_iterator<Iter, Container>::reference
random_access_iterator<Iter, Container>::operator*() const
{
	return (*_current);
}

template< typename Iter, typename Container >
typename random_access_iterator<Iter, Container>::pointer
random_access_iterator<Iter, Container>::operator->() const
{
	return (&(operator*()));
}

template< typename Iter, typename Container >
typename random_access_iterator<Iter, Container>::value_type
random_access_iterator<Iter, Container>::operator[]( difference_type n ) const
{
	return (_current[n]);
}

template< typename Iter, typename Container >
random_access_iterator<Iter, Container>&
random_access_iterator<Iter, Container>::operator++()
{
	++_current;
	return (*this);
}

template< typename Iter, typename Container >
random_access_iterator<Iter, Container>&
random_access_iterator<Iter, Container>::operator--()
{
	--_current;
	return (*this);
}

template< typename Iter, typename Container >
random_access_iterator<Iter, Container>
random_access_iterator<Iter, Container>::operator++(int)
{
	random_access_iterator<Iter, Container> tmp = *this;

	++_current;
	return (tmp);
}

template< typename Iter, typename Container >
random_access_iterator<Iter, Container>
random_access_iterator<Iter, Container>::operator--(int)
{
	random_access_iterator<Iter, Container> tmp = *this;

	--_current;
	return (tmp);
}

template< typename Iter, typename Container >
random_access_iterator<Iter, Container>
random_access_iterator<Iter, Container>::operator+( difference_type n ) const
{
	return (random_access_iterator(base() + n));
}

template< typename Iter, typename Container >
random_access_iterator<Iter, Container>
random_access_iterator<Iter, Container>::operator-( difference_type n ) const
{
	return (random_access_iterator(base() - n));
}

template< typename Iter, typename Container >
random_access_iterator<Iter, Container>&
random_access_iterator<Iter, Container>::operator+=( difference_type n )
{
	_current += n;
	return (*this);
}

template< typename Iter, typename Container >
random_access_iterator<Iter, Container>&
random_access_iterator<Iter, Container>::operator-=( difference_type n )
{
	_current -= n;
	return (*this);
}

/*
** ----------------------------- NON-MEMBER FUNCTIONS -----------------------------
*/

template< typename Iter1, typename Iter2, typename Container >
bool operator==( const random_access_iterator<Iter1, Container>& lhs,
	const random_access_iterator<Iter2, Container>& rhs )
{
	return (lhs.base() == rhs.base());
}

template< typename Iter1, typename Iter2, typename Container >
bool operator!=( const random_access_iterator<Iter1, Container>& lhs,
	const random_access_iterator<Iter2, Container>& rhs )
{
	return (lhs.base() != rhs.base());
}

template< typename Iter1, typename Iter2, typename Container >
bool operator<( const random_access_iterator<Iter1, Container>& lhs,
	const random_access_iterator<Iter2, Container>& rhs )
{
	return (lhs.base() < rhs.base());
}

template< typename Iter1, typename Iter2, typename Container >
bool operator<=( const random_access_iterator<Iter1, Container>& lhs,
	const random_access_iterator<Iter2, Container>& rhs )
{
	return (lhs.base() <= rhs.base());
}

template< typename Iter1, typename Iter2, typename Container >
bool operator>( const random_access_iterator<Iter1, Container>& lhs,
	const random_access_iterator<Iter2, Container>& rhs )
{
	return (lhs.base() > rhs.base());
}

template< typename Iter1, typename Iter2, typename Container >
bool operator>=( const random_access_iterator<Iter1, Container>& lhs,
	const random_access_iterator<Iter2, Container>& rhs )
{
	return (lhs.base() >= rhs.base());
}

template< typename Iter, typename Container >
random_access_iterator<Iter, Container> operator+( 
	typename random_access_iterator<Iter, Container>::difference_type n,
	const random_access_iterator<Iter, Container>& it )
{
	return (random_access_iterator<Iter, Container>(it.base() + n));
}

template< typename Iter, typename Container >
typename random_access_iterator<Iter, Container>::difference_type operator-(
	const random_access_iterator<Iter, Container>& lhs,
	const random_access_iterator<Iter, Container>& rhs )
{
	return (rhs.base() - lhs.base());
}

/* ************************************************************************** */
} // namespace ft
/* ************************************************************************** */