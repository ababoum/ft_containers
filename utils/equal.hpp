/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:00:34 by mababou           #+#    #+#             */
/*   Updated: 2022/05/09 15:22:26 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EQUAL_HPP
# define EQUAL_HPP

# include <iostream>
# include <string>

namespace ft {

template< class InputIt1, class InputIt2 >
bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2 )
{
	for ( ; first1 != last1; ++first1, ++first2 ) {
        if (!(*first1 == *first2)) {
            return false;
        }
    }
    return true;
}

template< class InputIt1, class InputIt2, class BinaryPredicate >
bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p )
{
	for ( ; first1 != last1; ++first1, ++first2 ) {
        if (!p(*first1, *first2)) {
            return false;
        }
    }
    return true;
}

} // namespace ft

#endif