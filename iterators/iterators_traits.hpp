/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators_traits.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:16:39 by mababou           #+#    #+#             */
/*   Updated: 2022/05/09 17:08:07 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATORS_TRAITS_HPP
# define ITERATORS_TRAITS_HPP

# include <iostream>
# include <string>

namespace ft {

	template< class T >
	struct iterator_traits
	{
		typedef	std::ptrdiff_t					difference_type;
		typedef	T								value_type;
		typedef	T*								pointer;
		typedef	T&								reference;
		typedef	std::random_access_iterator_tag	iterator_category;
	};
	
}

#endif