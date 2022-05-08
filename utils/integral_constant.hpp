/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integral_constant.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 19:20:00 by mababou           #+#    #+#             */
/*   Updated: 2022/05/08 19:32:51 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTEGRAL_CONSTANT_HPP
# define INTEGRAL_CONSTANT_HPP

# include <iostream>
# include <string>

namespace ft {
	
	template< class T, T v >
	struct integral_constant
	{
		public:

			typedef T							value_type;
			typedef integral_constant<T,v>		type;

			const static T	value = v;

			operator T() const { return value; }
	};

	typedef integral_constant< bool, true >		true_type;
	typedef integral_constant< bool, false >	false_type;

} // namespace ft

#endif