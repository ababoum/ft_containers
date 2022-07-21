/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:16:39 by mababou           #+#    #+#             */
/*   Updated: 2022/07/21 17:00:58 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include <iostream>
# include <string>
# include "iterators_traits.hpp"

namespace ft {

	template< class Iter >
	class reverse_iterator
	{
		public:
			typedef ft::iterator_traits<Iter>		traits_type;
			
			typedef	Iter										iterator_type;
			typedef	typename traits_type::iterator_category		iterator_category;
			typedef	typename traits_type::value_type			value_type;
			typedef	typename traits_type::difference_type		difference_type;
			typedef	typename traits_type::pointer				pointer;
			typedef	typename traits_type::reference				reference;
		
		private:
			iterator_type	_current;
		
		public:
			/* CONSTRUCTORS */

			/* 1 */
			reverse_iterator(): _current() {}

			/* 2 */
			explicit reverse_iterator( iterator_type x ): _current(x.base()) {}
			
			template< class U >
			reverse_iterator( const reverse_iterator<U>& other ): _current(other.base()) {}

			/* 3 */
			explicit reverse_iterator( pointer ptr ): _current(ptr) {}

			/* MEMBER FUNCTIONS */
			
			template< class U >
			reverse_iterator&	operator=( const reverse_iterator<U>& other )
			{
				_current = other.base();
				return (*this);
			}
			
			iterator_type		base() const
			{
				return _current;
			}
			
			reference			operator*() const
			{
				return *(_current - 1);
			}
			
			pointer				operator->() const
			{
				return &(operator*());
			}
			
			reference			operator[]( difference_type n )
			{
				return *(_current - 1 - n);
			}
			
			reverse_iterator&	operator++()
			{
				--_current;
				return (*this);
			}
			
			reverse_iterator&	operator--()
			{
				++_current;
				return (*this);
			}
			
			reverse_iterator	operator++( int )
			{
				reverse_iterator tmp = *this;

				--_current;
				return (tmp);
			}
			
			reverse_iterator	operator--( int )
			{
				reverse_iterator tmp = *this;

				++_current;
				return (tmp);
			}
			
			reverse_iterator	operator+( difference_type n ) const
			{
				reverse_iterator tmp(_current - n);
				
				return (tmp);
			}
			
			reverse_iterator	operator-( difference_type n ) const
			{
				reverse_iterator tmp(_current + n);
				
				return (tmp);
			}
			
			reverse_iterator&	operator+=( difference_type n )
			{
				_current -= n;
				return (*this);
			}
			
			reverse_iterator&	operator-=( difference_type n )
			{
				_current += n;
				return (*this);
			}

	};

	template< class Iterator1, class Iterator2 >
	bool operator==( const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs )
		{
			return (lhs.base() == rhs.base());
		}
	template< class Iterator1, class Iterator2 >
	bool operator!=( const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs )
		{
			return (lhs.base() != rhs.base());
		}
	template< class Iterator1, class Iterator2 >
	bool operator<( const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs )
		{
			return (lhs.base() < rhs.base());
		}
	template< class Iterator1, class Iterator2 >
	bool operator<=( const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs )
		{
			return (lhs.base() <= rhs.base());
		}
	template< class Iterator1, class Iterator2 >
	bool operator>( const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs )
		{
			return (lhs.base() > rhs.base());
		}
	template< class Iterator1, class Iterator2 >
	bool operator>=( const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs )
		{
			return (lhs.base() >= rhs.base());
		}

	template< class Iter >
	reverse_iterator<Iter> operator+( 
		typename reverse_iterator<Iter>::difference_type n,
		const reverse_iterator<Iter>& it )
		{
			return (reverse_iterator<Iter>(it.base() - n));
		}
	template< class Iterator, class Iterator2 >
	typename reverse_iterator<Iterator>::difference_type operator-(
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator2>& rhs )
		{
			return (rhs.base() - lhs.base());
		}
}

#endif