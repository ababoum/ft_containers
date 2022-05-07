/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.tpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:49:07 by mababou           #+#    #+#             */
/*   Updated: 2022/05/07 19:15:27 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reverse_iterator.hpp"

namespace ft {

	typedef	Iter											iterator_type;
	typedef	ft::iterator_traits<Iter>::iterator_category	iterator_category;
	typedef	ft::iterator_traits<Iter>::value_type			value_type;
	typedef	ft::iterator_traits<Iter>::difference_type		difference_type;
	typedef	ft::iterator_traits<Iter>::pointer				current;
	typedef	ft::iterator_traits<Iter>::reference			reference;

/*
** ------------------------------- CONSTRUCTORS -------------------------------
*/

template< class Iter >					/* 1 */
ft::reverse_iterator<Iter>::reverse_iterator();
{
	current_ = 0;
}

/*
** ----------------------------- MEMBER FUNCTIONS -----------------------------
*/

template< class Iter >	
template< class U >
ft::reverse_iterator<Iter>& ft::reverse_iterator<Iter>::operator=( const reverse_iterator<U>& other )
{
	this->base() = other->base();
	return (*this);
}

template< class Iter >
iterator_type ft::reverse_iterator<Iter>::base() const
{
	return (current_);
}

template< class Iter >
reference ft::reverse_iterator<Iter>::operator*() const
{
	Iter	tmp = current_;

	return (*--tmp);
}

template< class Iter >
pointer ft::reverse_iterator<Iter>::operator->() const
{
	return (std::addressof(operator*()));
}

template< class Iter >
ft::reverse_iterator<Iter>::operator[]( difference_type n ) const
{
	return (base()[-n - 1]);
}

template< class Iter >
ft::reverse_iterator<Iter>& t::reverse_iterator<Iter>::operator++()
{
	--current_;
	return (*this);
}

template< class Iter >
ft::reverse_iterator<Iter>& t::reverse_iterator<Iter>::operator--()
{
	++current_;
	return (*this);
}

template< class Iter >
ft::reverse_iterator<Iter> t::reverse_iterator<Iter>::operator++(int)
{
	ft::reverse_iterator<Iter> tmp = *this;

	--current_;
	return (tmp);
}

template< class Iter >
ft::reverse_iterator<Iter> t::reverse_iterator<Iter>::operator--(int)
{
	ft::reverse_iterator<Iter> tmp = *this;

	++current_;
	return (tmp);
}

template< class Iter >
ft::reverse_iterator<Iter> t::reverse_iterator<Iter>::operator+( difference_type n ) const
{
	return (reverse_iterator(base() - n));
}

template< class Iter >
ft::reverse_iterator<Iter> t::reverse_iterator<Iter>::operator-( difference_type n ) const
{
	return (reverse_iterator(base() + n));
}

template< class Iter >
ft::reverse_iterator<Iter>& t::reverse_iterator<Iter>::operator+=( difference_type n )
{
	current_ -= n;
	return (*this);
}

template< class Iter >
ft::reverse_iterator<Iter>& t::reverse_iterator<Iter>::operator-=( difference_type n )
{
	current_ += n;
	return (*this);
}

/*
** ----------------------------- NON-MEMBER FUNCTIONS -----------------------------
*/

template< class Iter >
template< class Iterator1, class Iterator2 >
bool ft::reverse_iterator<Iter>::operator==( const std::reverse_iterator<Iterator1>& lhs,
	const std::reverse_iterator<Iterator2>& rhs )
{
	return (lhs.base() == rhs.base());
}

template< class Iter >
template< class Iterator1, class Iterator2 >
bool ft::reverse_iterator<Iter>::operator!=( const std::reverse_iterator<Iterator1>& lhs,
	const std::reverse_iterator<Iterator2>& rhs )
{
	return (lhs.base() != rhs.base());
}

template< class Iter >
template< class Iterator1, class Iterator2 >
bool ft::reverse_iterator<Iter>::operator<( const std::reverse_iterator<Iterator1>& lhs,
	const std::reverse_iterator<Iterator2>& rhs )
{
	return (lhs.base() < rhs.base());
}

template< class Iter >
template< class Iterator1, class Iterator2 >
bool ft::reverse_iterator<Iter>::operator<=( const std::reverse_iterator<Iterator1>& lhs,
	const std::reverse_iterator<Iterator2>& rhs )
{
	return (lhs.base() <= rhs.base());
}

template< class Iter >
template< class Iterator1, class Iterator2 >
bool ft::reverse_iterator<Iter>::operator>( const std::reverse_iterator<Iterator1>& lhs,
	const std::reverse_iterator<Iterator2>& rhs )
{
	return (lhs.base() > rhs.base());
}

template< class Iter >
template< class Iterator1, class Iterator2 >
bool ft::reverse_iterator<Iter>::operator>=( const std::reverse_iterator<Iterator1>& lhs,
	const std::reverse_iterator<Iterator2>& rhs )
{
	return (lhs.base() >= rhs.base());
}

template< class Iter >
reverse_iterator<Iter> operator+( 
	typename reverse_iterator<Iter>::difference_type n,
	const reverse_iterator<Iter>& it )
	{
		
	}

/* ************************************************************************** */
} // namespace ft
/* ************************************************************************** */