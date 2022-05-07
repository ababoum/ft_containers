/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 23:16:43 by mababou           #+#    #+#             */
/*   Updated: 2022/05/07 23:27:00 by mababou          ###   ########.fr       */
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
		pair();									/* 1 */
		pair( const T1& x, const T2& y );		/* 2 */

		/* MEMBER FUNCTIONS */
		pair& operator=( const pair& other );

		private:
			first_type		first;
			second_type		second;
	}

	template< class T1, class T2 >
	std::pair<T1,T2> make_pair( T1 t, T2 u );

	template< class T1, class T2 >
	bool operator==( const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs );
	template< class T1, class T2 >
	bool operator!=( const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs );
	template< class T1, class T2 >
	bool operator<( const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs );
	template< class T1, class T2 >
	bool operator<=( const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs );
	template< class T1, class T2 >
	bool operator>( const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs );
	template< class T1, class T2 >
	bool operator>=( const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs );

} // namespace ft

# include "pair.tpp"

#endif