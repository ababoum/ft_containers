/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.tpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 23:18:01 by mababou           #+#    #+#             */
/*   Updated: 2022/07/18 15:24:51 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pair.hpp"

namespace ft {

	
/*
** ------------------------------- CONSTRUCTORS -------------------------------
*/

template< class T1, class T2 >
pair<T1, T2>::pair()
{
	first = first_type();
	second = second_type();
}

template< class T1, class T2 >
pair<T1, T2>::pair(const T1& x, const T2& y)
{
	first = x;
	second = y;
}

/*
** ----------------------------- MEMBER FUNCTIONS -----------------------------
*/

template< class T1, class T2 >
pair<T1, T2>& pair<T1, T2>::operator=( const pair<T1, T2>& other )
{
	first = other.first;
	second = other.second;

	return (*this);
}

/*
** ----------------------------- NON-MEMBER FUNCTIONS -----------------------------
*/

template< class T1, class T2 >
pair<T1,T2> make_pair( T1 t, T2 u )
{
	pair<T1, T2> new_pair(t, u);
	return (new_pair);
}

template< class T1, class T2 >
bool operator==( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
{
	return (lhs.first == rhs.first && lhs.second == rhs.second);
}

template< class T1, class T2 >
bool operator!=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
{
	return (!(lhs == rhs));
}

template< class T1, class T2 >
bool operator<( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
{
	if (lhs.first == rhs.first)
		return (lhs.second < rhs.second);
	else
		return (lhs.first < rhs.first);
}

template< class T1, class T2 >
bool operator<=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
{
	if (lhs.first == rhs.first)
		return (lhs.second <= rhs.second);
	else
		return (lhs.first <= rhs.first);
}

template< class T1, class T2 >
bool operator>( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
{
	if (lhs.first == rhs.first)
		return (lhs.second > rhs.second);
	else
		return (lhs.first > rhs.first);
}

template< class T1, class T2 >
bool operator>=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
{
	if (lhs.first == rhs.first)
		return (lhs.second >= rhs.second);
	else
		return (lhs.first >= rhs.first);
}

/* ************************************************************************** */
} // namespace ft
/* ************************************************************************** */