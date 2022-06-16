/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 20:27:11 by mababou           #+#    #+#             */
/*   Updated: 2022/06/16 20:31:25 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_HPP
# define RB_TREE_HPP

# include <iostream>

namespace ft {

	enum rb_tree_color { _S_red = false, _S_black = true };

	struct rb_tree_node_base
	{
		typedef		rb_tree_node_base*			_Base_ptr;
		typedef		const rb_tree_node_base*	_Const_Base_ptr;

		rb_tree_color	_M_color;
		_Base_ptr		_M_parent;
		_Base_ptr		_M_left;
		_Base_ptr		_M_right;
	}

} // namespace ft


#endif /* ********************************************************* RB_TREE_H */