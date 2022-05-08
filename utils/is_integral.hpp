/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 18:35:07 by mababou           #+#    #+#             */
/*   Updated: 2022/05/08 19:38:13 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP

# include <iostream>
# include <string>

# include "integral_constant.hpp"

namespace ft {

	template< class T >
	struct is_integral: false_type {};

	template< class T >
	struct is_integral<const T>: is_integral<T> {};

	template <>
	struct is_integral<bool> : true_type {};

	template <>
	struct is_integral<char> : true_type {};
	
	template <>
	struct is_integral<wchar_t> : true_type {};
	
	template <>
	struct is_integral<signed char> : true_type {};

	template <>
	struct is_integral<short int> : true_type {};

	template <>
	struct is_integral<int> : true_type {};
	
	template <>
	struct is_integral<long int> : true_type {};
	
	template <>
	struct is_integral<long long int> : true_type {};

	template <>
	struct is_integral<unsigned char> : true_type {};
	
	template <>
	struct is_integral<unsigned short int> : true_type {};

	template <>
	struct is_integral<unsigned int> : true_type {};

	template <>
	struct is_integral<unsigned long int> : true_type {};
	
	template <>
	struct is_integral<unsigned long long int> : true_type {};

} // namespace ft

#endif