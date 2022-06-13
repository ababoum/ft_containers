/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 17:30:30 by mababou           #+#    #+#             */
/*   Updated: 2022/06/13 17:33:16 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP

# include <iostream>
# include <string>

namespace ft {

	template< bool, typename >
	struct enable_if 
	{ };

	template< typename T >
	struct enable_if< true, T >
	{ typedef T type; };

} // namespace ft

#endif