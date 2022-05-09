/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:26:06 by mababou           #+#    #+#             */
/*   Updated: 2022/05/09 16:01:32 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include <iostream>
# include <string>

# include "vector.hpp"

namespace ft {

template< class T, class Container = ft::vector<T> >
class stack
{
	public:
		typedef Container					container_type;
		typedef	Container::value_type		value_type;
		typedef	Container::size_type		size_type;
		typedef	Container::reference		reference;
		typedef	Container::const_reference	const_reference;

		/* CONSTRUCTORS */
		explicit stack( const Container& cont = Container() );	/* 1 */
		stack( const stack& other );							/* 2 */

		/* DESTRUCTOR */
		~stack();

		/* GENERAL MEMBER FUNCTIONS */
		stack& operator=( const stack& other );

		/* ELEMENT ACCESS  */
		reference 		top();
		const_reference top() const;

		/* CAPACITY */
		bool empty() const;
		size_type size() const;

		/* MODIFIERS */
		void push( const value_type& value );
		void pop();
		
	private:
		container_type	_c;

};

template< class T, class Container >
bool operator==( const stack<T,Container>& lhs, const stack<T,Container>& rhs );

template< class T, class Container >
bool operator!=( const stack<T,Container>& lhs, const stack<T,Container>& rhs );

template< class T, class Container >
bool operator<( const stack<T,Container>& lhs, const stack<T,Container>& rhs );

template< class T, class Container >
bool operator<=( const stack<T,Container>& lhs, const stack<T,Container>& rhs );

template< class T, class Container >
bool operator>( const stack<T,Container>& lhs, const stack<T,Container>& rhs );

template< class T, class Container >
bool operator>=( const stack<T,Container>& lhs, const stack<T,Container>& rhs );

} // namespace ft

#include "stack.tpp"

#endif /* *********************************************************** STACK_H */