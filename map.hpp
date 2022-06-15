/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 14:06:48 by mababou           #+#    #+#             */
/*   Updated: 2022/06/15 18:10:05 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include <string>

# include "iterators/iterators_traits.hpp"
# include "iterators/reverse_iterator.hpp"
# include "iterators/random_access_iterator.hpp"
# include "utils/equal.hpp"
# include "utils/lexicographical_compare.hpp"
# include "utils/is_integral.hpp"


namespace ft {

template<  >
class map
{
	public:

		typedef	T											value_type;
		
		/* CONSTRUCTORS */


		/* DESTRUCTOR */
		~map();
		
		/* GENERAL MEMBER FUNCTIONS */


		/* ELEMENT ACCESS  */
		
		/* ITERATORS */

		/* CAPACITY */

		/* MODIFIERS */
		
	private:

};

} // namespace ft

#include "map.tpp"

#endif /* ********************************************************** VECTOR_H */