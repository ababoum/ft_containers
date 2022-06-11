/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators_traits.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:16:39 by mababou           #+#    #+#             */
/*   Updated: 2022/06/11 17:43:29 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATORS_TRAITS_HPP
# define ITERATORS_TRAITS_HPP

# include <iostream>
# include <string>

namespace ft {
	
	template< typename Iter >
	struct iterator_traits
	{
		typedef	typename Iter::difference_type		difference_type;
		typedef	typename Iter::value_type			value_type;
		typedef	typename Iter::pointer				pointer;
		typedef	typename Iter::reference			reference;
		typedef	typename Iter::iterator_category	iterator_category;
	};
	
	template< typename T >
	struct iterator_traits< T* >
	{
		typedef	std::ptrdiff_t					difference_type;
		typedef	T								value_type;
		typedef	T*								pointer;
		typedef	T&								reference;
		typedef	std::random_access_iterator_tag	iterator_category;
	};

	template< typename T >
	struct iterator_traits< const T*> 
	{
		typedef	std::ptrdiff_t					difference_type;
		typedef	T								value_type;
		typedef	const T*						pointer;
		typedef	const T&						reference;
		typedef	std::random_access_iterator_tag	iterator_category;
	};

}

#endif