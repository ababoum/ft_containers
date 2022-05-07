/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.tpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:49:07 by mababou           #+#    #+#             */
/*   Updated: 2022/05/07 23:05:31 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse_iterator.hpp"

namespace ft {

/*
** ------------------------------- CONSTRUCTORS -------------------------------
*/

template< class T >					/* 1 */
ft::reverse_iterator<T>::reverse_iterator()
{
	current_ = 0;
}

template< class T >					/* 2 */
ft::reverse_iterator<T>::reverse_iterator(ft::reverse_iterator<T>::pointer x)
{
	current_ = x;
}

template< class T >					/* 3 */
template< class U >
ft::reverse_iterator<T>::reverse_iterator( const ft::reverse_iterator<U>& other )
{
	*this = other;
}

/*
** ----------------------------- MEMBER FUNCTIONS -----------------------------
*/

template< class T >	
template< class U >
ft::reverse_iterator<T>& ft::reverse_iterator<T>::operator=( const reverse_iterator<U>& other )
{
	this->base() = other->base();
	return (*this);
}

template< class T >
typename ft::reverse_iterator<T>::pointer ft::reverse_iterator<T>::base() const
{
	return (current_);
}

template< class T >
typename ft::iterator_traits<T>::reference ft::reverse_iterator<T>::operator*() const
{
	T	tmp = current_;

	return (*--tmp);
}

template< class T >
typename ft::iterator_traits<T>::pointer ft::reverse_iterator<T>::operator->() const
{
	return (&(operator*()));
}

template< class T >
typename ft::iterator_traits<T>::value_type ft::reverse_iterator<T>::operator[]( difference_type n ) const
{
	return (base()[-n - 1]);
}

template< class T >
ft::reverse_iterator<T>& ft::reverse_iterator<T>::operator++()
{
	--current_;
	return (*this);
}

template< class T >
ft::reverse_iterator<T>& ft::reverse_iterator<T>::operator--()
{
	++current_;
	return (*this);
}

template< class T >
ft::reverse_iterator<T> ft::reverse_iterator<T>::operator++(int)
{
	ft::reverse_iterator<T> tmp = *this;

	--current_;
	return (tmp);
}

template< class T >
ft::reverse_iterator<T> ft::reverse_iterator<T>::operator--(int)
{
	ft::reverse_iterator<T> tmp = *this;

	++current_;
	return (tmp);
}

template< class T >
ft::reverse_iterator<T> ft::reverse_iterator<T>::operator+( difference_type n ) const
{
	return (reverse_iterator(base() - n));
}

template< class T >
ft::reverse_iterator<T> ft::reverse_iterator<T>::operator-( difference_type n ) const
{
	return (reverse_iterator(base() + n));
}

template< class T >
ft::reverse_iterator<T>& ft::reverse_iterator<T>::operator+=( difference_type n )
{
	current_ -= n;
	return (*this);
}

template< class T >
ft::reverse_iterator<T>& ft::reverse_iterator<T>::operator-=( difference_type n )
{
	current_ += n;
	return (*this);
}

/*
** ----------------------------- NON-MEMBER FUNCTIONS -----------------------------
*/

template< class T1, class T2 >
bool operator==( const std::reverse_iterator<T1>& lhs,
	const std::reverse_iterator<T2>& rhs )
{
	return (lhs.base() == rhs.base());
}

template< class T1, class T2 >
bool operator!=( const std::reverse_iterator<T1>& lhs,
	const std::reverse_iterator<T2>& rhs )
{
	return (lhs.base() != rhs.base());
}

template< class T1, class T2 >
bool operator<( const std::reverse_iterator<T1>& lhs,
	const std::reverse_iterator<T2>& rhs )
{
	return (lhs.base() < rhs.base());
}

template< class T1, class T2 >
bool operator<=( const std::reverse_iterator<T1>& lhs,
	const std::reverse_iterator<T2>& rhs )
{
	return (lhs.base() <= rhs.base());
}

template< class T1, class T2 >
bool operator>( const std::reverse_iterator<T1>& lhs,
	const std::reverse_iterator<T2>& rhs )
{
	return (lhs.base() > rhs.base());
}

template< class T1, class T2 >
bool operator>=( const std::reverse_iterator<T1>& lhs,
	const std::reverse_iterator<T2>& rhs )
{
	return (lhs.base() >= rhs.base());
}

template< class T >
reverse_iterator<T> operator+( 
	typename reverse_iterator<T>::difference_type n,
	const reverse_iterator<T>& it )
{
	return (reverse_iterator<T>(it.base() - n));
}

template< class T >
typename reverse_iterator<T>::difference_type operator-(
	const reverse_iterator<T>& lhs,
	const reverse_iterator<T>& rhs )
{
	return (rhs.base() - lhs.base());
}

/* ************************************************************************** */
} // namespace ft
/* ************************************************************************** */