/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.tpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:49:07 by mababou           #+#    #+#             */
/*   Updated: 2022/06/10 15:47:20 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "random_access_iterator.hpp"

namespace ft {

/*
** ------------------------------- CONSTRUCTORS -------------------------------
*/

template< class T >					/* 1 */
random_access_iterator<T>::random_access_iterator()
{
	_current = NULL;
}

template< class T >					/* 2 */
random_access_iterator<T>::random_access_iterator(typename random_access_iterator<T>::pointer x)
{
	_current = x;
}

template< class T >					/* 3 */
template< class U >
random_access_iterator<T>::random_access_iterator(const random_access_iterator<U>& other)
{
	*this = other;
}

/*
** ----------------------------- MEMBER FUNCTIONS -----------------------------
*/


template< class T >	
template< class U >
random_access_iterator<T>& random_access_iterator<T>::operator=( const random_access_iterator<U>& other )
{
	this->base() = other->base();
	return (*this);
}

template< class T >
typename random_access_iterator<T>::pointer random_access_iterator<T>::base() const
{
	return (_current);
}

template< class T >
typename random_access_iterator<T>::reference random_access_iterator<T>::operator*() const
{
	return (*_current);
}

template< class T >
typename random_access_iterator<T>::pointer random_access_iterator<T>::operator->() const
{
	return (&(operator*()));
}

template< class T >
typename random_access_iterator<T>::value_type random_access_iterator<T>::operator[]( difference_type n ) const
{
	return (base()[n]);
}

template< class T >
random_access_iterator<T>& random_access_iterator<T>::operator++()
{
	++_current;
	return (*this);
}

template< class T >
random_access_iterator<T>& random_access_iterator<T>::operator--()
{
	--_current;
	return (*this);
}

template< class T >
random_access_iterator<T> random_access_iterator<T>::operator++(int)
{
	random_access_iterator<T> tmp = *this;

	++_current;
	return (tmp);
}

template< class T >
random_access_iterator<T> random_access_iterator<T>::operator--(int)
{
	random_access_iterator<T> tmp = *this;

	--_current;
	return (tmp);
}

template< class T >
random_access_iterator<T> random_access_iterator<T>::operator+( difference_type n ) const
{
	return (random_access_iterator(base() + n));
}

template< class T >
random_access_iterator<T> random_access_iterator<T>::operator-( difference_type n ) const
{
	return (random_access_iterator(base() - n));
}

template< class T >
random_access_iterator<T>& random_access_iterator<T>::operator+=( difference_type n )
{
	_current += n;
	return (*this);
}

template< class T >
random_access_iterator<T>& random_access_iterator<T>::operator-=( difference_type n )
{
	_current -= n;
	return (*this);
}

/*
** ----------------------------- NON-MEMBER FUNCTIONS -----------------------------
*/

template< class T1, class T2 >
bool operator==( const random_access_iterator<T1>& lhs,
	const random_access_iterator<T2>& rhs )
{
	return (lhs.base() == rhs.base());
}

template< class T1, class T2 >
bool operator!=( const random_access_iterator<T1>& lhs,
	const random_access_iterator<T2>& rhs )
{
	return (lhs.base() != rhs.base());
}

template< class T1, class T2 >
bool operator<( const random_access_iterator<T1>& lhs,
	const random_access_iterator<T2>& rhs )
{
	return (lhs.base() < rhs.base());
}

template< class T1, class T2 >
bool operator<=( const random_access_iterator<T1>& lhs,
	const random_access_iterator<T2>& rhs )
{
	return (lhs.base() <= rhs.base());
}

template< class T1, class T2 >
bool operator>( const random_access_iterator<T1>& lhs,
	const random_access_iterator<T2>& rhs )
{
	return (lhs.base() > rhs.base());
}

template< class T1, class T2 >
bool operator>=( const random_access_iterator<T1>& lhs,
	const random_access_iterator<T2>& rhs )
{
	return (lhs.base() >= rhs.base());
}

template< class T >
random_access_iterator<T> operator+( 
	typename random_access_iterator<T>::difference_type n,
	const random_access_iterator<T>& it )
{
	return (random_access_iterator<T>(it.base() + n));
}

template< class T >
typename random_access_iterator<T>::difference_type operator-(
	const random_access_iterator<T>& lhs,
	const random_access_iterator<T>& rhs )
{
	return (rhs.base() - lhs.base());
}

/* ************************************************************************** */
} // namespace ft
/* ************************************************************************** */