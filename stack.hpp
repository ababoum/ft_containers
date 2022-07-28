/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:26:06 by mababou           #+#    #+#             */
/*   Updated: 2022/07/28 15:54:15 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include <iostream>
# include <string>
# include <stack>

# include "vector.hpp"

namespace ft {

template< class T, class Container = ft::vector<T> >
class stack
{

	template<typename Tx, typename ContainerX>
	friend bool
	operator==(const stack<Tx, ContainerX>&, const stack<Tx, ContainerX>&);

	template<typename Tx, typename ContainerX>
	friend bool
	operator<(const stack<Tx, ContainerX>&, const stack<Tx, ContainerX>&);
	
	public:
		typedef Container							container_type;
		typedef	typename Container::value_type		value_type;
		typedef	typename Container::size_type		size_type;
		typedef	typename Container::reference		reference;
		typedef	typename Container::const_reference	const_reference;


		/* CONSTRUCTORS */

		/* 1 */
		explicit stack( const Container& cont = Container() )
		{
			c = cont;
		}

		/* 2 */
		stack( const stack& other )
		{
			c = other.c;
		}

		/* DESTRUCTOR */
		~stack() {};

		/* GENERAL MEMBER FUNCTIONS */
		stack& operator=( const stack& other )
		{
			c = other.c;
			return *this;
		}

		/* ELEMENT ACCESS  */
		reference 		top()
		{
			return c.back();
		}
		const_reference top() const
		{
			return c.back();
		}

		/* CAPACITY */
		bool empty() const
		{
			return c.empty();
		}
		
		size_type size() const
		{
			return c.size();
		}

		/* MODIFIERS */
		void push( const value_type& value )
		{
			c.push_back(value);
		}
		
		void pop()
		{
			c.pop_back();
		}
		
	protected:
		container_type	c;

};

template< class T, class Container >
inline bool operator==( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
{
	return lhs.c == rhs.c;
}

template< class T, class Container >
inline bool operator!=( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
{
	return !(lhs == rhs);
}

template< class T, class Container >
inline bool operator<( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
{
	return lhs.c < rhs.c;
}

template< class T, class Container >
inline bool operator<=( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
{
	return !(rhs < lhs);
}

template< class T, class Container >
inline bool operator>( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
{
	return rhs < lhs;
}

template< class T, class Container >
inline bool operator>=( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
{
	return !(lhs < rhs);
}

} // namespace ft

#endif /* *********************************************************** STACK_H */