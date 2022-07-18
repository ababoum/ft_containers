/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 14:39:41 by mababou           #+#    #+#             */
/*   Updated: 2022/07/18 19:47:29 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_UTILS_HPP
#define TREE_UTILS_HPP

#include "RBT.hpp"

namespace ft
{
	template <typename pair>
	struct select1st
		: public std::unary_function<pair, typename pair::first_type>
	{
		typename pair::first_type &
		operator()(pair &key_val) const
		{
			return key_val.first;
		}

		const typename pair::first_type &
		operator()(const pair &key_val) const
		{
			return key_val.first;
		}
	};
} // namespace ft

#endif /* ****************************************************** TREE_UTILS_H */