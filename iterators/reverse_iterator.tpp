/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.tpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:49:07 by mababou           #+#    #+#             */
/*   Updated: 2022/06/13 18:36:15 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse_iterator.hpp"

namespace ft {

/*
** ------------------------------- CONSTRUCTORS -------------------------------
*/

template< class Iter >					/* 1 */
reverse_iterator<Iter>::reverse_iterator()
: current_() {}

template< class Iter >					/* 2 */
reverse_iterator<Iter>::reverse_iterator(reverse_iterator<Iter>::iterator_type	x)
: current_(x) {}

template< class Iter >					/* 3 */
template< class U >
reverse_iterator<Iter>::reverse_iterator( const reverse_iterator<U>& other )
: current_(other.current_) {}

/*
** ----------------------------- MEMBER FUNCTIONS -----------------------------
*/

template< class Iter >	
template< class U >
reverse_iterator<Iter>& reverse_iterator<Iter>::operator=( const reverse_iterator<U>& other )
{
	current_ = other.base();
	return (*this);
}

template< class Iter >
typename reverse_iterator<Iter>::iterator_type reverse_iterator<Iter>::base() const
{
	return (current_);
}

template< class Iter >
typename iterator_traits<Iter>::reference reverse_iterator<Iter>::operator*() const
{
	Iter	tmp = current_;

	return (*--tmp);
}

template< class Iter >
typename iterator_traits<Iter>::pointer reverse_iterator<Iter>::operator->() const
{
	return (&(operator*()));
}

template< class Iter >
void*	reverse_iterator<Iter>::operator[]( difference_type n ) const
{
	return (base()[-n - 1]);
}

template< class Iter >
reverse_iterator<Iter>& reverse_iterator<Iter>::operator++()
{
	--current_;
	return (*this);
}

template< class Iter >
reverse_iterator<Iter>& reverse_iterator<Iter>::operator--()
{
	++current_;
	return (*this);
}

template< class Iter >
reverse_iterator<Iter> reverse_iterator<Iter>::operator++(int)
{
	reverse_iterator<Iter> tmp = *this;

	--current_;
	return (tmp);
}

template< class Iter >
reverse_iterator<Iter> reverse_iterator<Iter>::operator--(int)
{
	reverse_iterator<Iter> tmp = *this;

	++current_;
	return (tmp);
}

template< class Iter >
reverse_iterator<Iter> reverse_iterator<Iter>::operator+( difference_type n ) const
{
	return (reverse_iterator(base() - n));
}

template< class Iter >
reverse_iterator<Iter> reverse_iterator<Iter>::operator-( difference_type n ) const
{
	return (reverse_iterator(base() + n));
}

template< class Iter >
reverse_iterator<Iter>& reverse_iterator<Iter>::operator+=( difference_type n )
{
	current_ -= n;
	return (*this);
}

template< class Iter >
reverse_iterator<Iter>& reverse_iterator<Iter>::operator-=( difference_type n )
{
	current_ += n;
	return (*this);
}

/*
** ----------------------------- NON-MEMBER FUNCTIONS -----------------------------
*/

template< class Iterator1, class Iterator2 >
bool operator==( const std::reverse_iterator<Iterator1>& lhs,
	const std::reverse_iterator<Iterator2>& rhs )
{
	return (lhs.base() == rhs.base());
}

template< class Iterator1, class Iterator2 >
bool operator!=( const std::reverse_iterator<Iterator1>& lhs,
	const std::reverse_iterator<Iterator2>& rhs )
{
	return (lhs.base() != rhs.base());
}

template< class Iterator1, class Iterator2 >
bool operator<( const std::reverse_iterator<Iterator1>& lhs,
	const std::reverse_iterator<Iterator2>& rhs )
{
	return (lhs.base() < rhs.base());
}

template< class Iterator1, class Iterator2 >
bool operator<=( const std::reverse_iterator<Iterator1>& lhs,
	const std::reverse_iterator<Iterator2>& rhs )
{
	return (lhs.base() <= rhs.base());
}

template< class Iterator1, class Iterator2 >
bool operator>( const std::reverse_iterator<Iterator1>& lhs,
	const std::reverse_iterator<Iterator2>& rhs )
{
	return (lhs.base() > rhs.base());
}

template< class Iterator1, class Iterator2 >
bool operator>=( const std::reverse_iterator<Iterator1>& lhs,
	const std::reverse_iterator<Iterator2>& rhs )
{
	return (lhs.base() >= rhs.base());
}

template< class Iter >
reverse_iterator<Iter> operator+( 
	typename reverse_iterator<Iter>::difference_type n,
	const reverse_iterator<Iter>& it )
{
	return (reverse_iterator<Iter>(it.base() - n));
}

template< class Iterator >
typename reverse_iterator<Iterator>::difference_type operator-(
	const reverse_iterator<Iterator>& lhs,
	const reverse_iterator<Iterator>& rhs )
{
	return (rhs.base() - lhs.base());
}

/* ************************************************************************** */
} // namespace ft
/* ************************************************************************** */