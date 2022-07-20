/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 23:16:43 by mababou           #+#    #+#             */
/*   Updated: 2022/07/20 17:43:55 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

# include <iostream>
# include <string>

namespace ft {

	template< class T1, class T2 >
	struct pair
	{
		public:
			typedef	T1		first_type;
			typedef	T2		second_type;

			/* CONSTRUCTORS */
			pair(): first(first_type()), second(second_type()) {}
			
			pair( const T1& x, const T2& y ): first(x), second(y) {}

			/* MEMBER FUNCTIONS */
			pair& operator=( const pair& other )
			{
				first = other.first;
				second = other.second;

				return (*this);
			}
		
			/* MEMBER OBJECTS */
			first_type		first;
			second_type		second;
	};

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
		return !(lhs == rhs);
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

} // namespace ft

#endif