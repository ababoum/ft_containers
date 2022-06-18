/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 14:39:41 by mababou           #+#    #+#             */
/*   Updated: 2022/06/18 14:41:27 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_UTILS_HPP
#define TREE_UTILS_HPP

#include "rb_tree/rb_tree.hpp"

namespace ft
{
	template <typename pair>
	struct select1st
		: public unary_function<pair, typename pair::first_type>
	{
		typename pair::first_type &
		operator()(pair &__x) const
		{
			return __x.first;
		}

		const typename pair::first_type &
		operator()(const pair &__x) const
		{
			return __x.first;
		}
	}
} // namespace ft

#endif /* ****************************************************** TREE_UTILS_H */