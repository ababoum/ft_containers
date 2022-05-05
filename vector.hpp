/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 14:06:48 by mababou           #+#    #+#             */
/*   Updated: 2022/05/05 18:01:04 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <string>

namespace ft {
template<
    class T,
    class Allocator = std::allocator<T>
>
class vector
{
	public:

		typedef	T			value_type;
		typedef	Allocator	allocator_type;
		typedef size_type	std::size_t;


		
		vector();
		explicit vector( const Allocator& alloc );
		explicit vector( size_type count,
			const T& value = T(),
			const Allocator& alloc = Allocator());
		explicit vector( size_type count );



		/* CAPACITY */
		size_type size() const;
		

	private:
		T*			_array;
		size_type	_size;
};

std::ostream &			operator<<( std::ostream & o, vector const & i );
}

#include "vector.tpp"

#endif /* ********************************************************** VECTOR_H */