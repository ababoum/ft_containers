/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 17:30:30 by mababou           #+#    #+#             */
/*   Updated: 2022/05/08 18:34:01 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP

# include <iostream>
# include <string>

namespace ft {

template< bool B, class T = void >
struct enable_if {
	
	public:
		if (B)
			typedef T	type;
}

} // namespace ft

#endif