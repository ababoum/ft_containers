/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:16:39 by mababou           #+#    #+#             */
/*   Updated: 2022/07/20 17:51:40 by mababou          ###   ########.fr       */
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
	: public std::iterator<typename iterator_traits<Iter>::iterator_category,
		typename iterator_traits<Iter>::value_type,
		typename iterator_traits<Iter>::difference_type,
		typename iterator_traits<Iter>::pointer,
		typename iterator_traits<Iter>::reference>
	{
		public:
			typedef iterator_traits<Iter>		traits_type;
			
			typedef	Iter										iterator_type;
			typedef	typename traits_type::iterator_category		iterator_category;
			typedef	typename traits_type::value_type			value_type;
			typedef	typename traits_type::difference_type		difference_type;
			typedef	typename traits_type::pointer				pointer;
			typedef	typename traits_type::reference				reference;
			typedef reverse_iterator<Iter>						rev_iterator;
		
			/* CONSTRUCTORS */

			/* 1 */
			reverse_iterator(): _current(pointer()) {}

			/* 2 */
			explicit reverse_iterator( iterator_type x ): _current(x.base()) {}
			
			template< class U >
			reverse_iterator( const reverse_iterator<U>& other ): _current(other.base()) {}

			/* MEMBER FUNCTIONS */
			
			template< class U >
			reverse_iterator&	operator=( const reverse_iterator<U>& other )
			{
				_current = other.base();
				return (*this);
			}
			
			pointer				base() const
			{
				return _current;
			}
			
			reference			operator*() const
			{
				return (*_current);
			}
			
			pointer				operator->() const
			{
				return &(operator*());
			}
			
			void*				operator[]( difference_type n ) const
			{
				return base()[-n - 1];
			}
			
			rev_iterator&	operator++()
			{
				--_current;
				return (*this);
			}
			
			rev_iterator&	operator--()
			{
				++_current;
				return (*this);
			}
			
			rev_iterator	operator++( int )
			{
				rev_iterator tmp = *this;

				--_current;
				return (tmp);
			}
			
			rev_iterator	operator--( int )
			{
				rev_iterator tmp = *this;

				++_current;
				return (tmp);
			}
			
			rev_iterator	operator+( difference_type n ) const
			{
				rev_iterator tmp(base() - n);

				return tmp;
			}
			
			rev_iterator	operator-( difference_type n ) const
			{
				rev_iterator tmp(base() + n);

				return tmp;
			}
			
			rev_iterator&	operator+=( difference_type n )
			{
				_current -= n;
				return (*this);
			}
			
			rev_iterator&	operator-=( difference_type n )
			{
				_current += n;
				return (*this);
			}

		private:
			pointer	_current;
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
	template< class Iterator >
	typename reverse_iterator<Iterator>::difference_type operator-(
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs )
		{
			return (rhs.base() - lhs.base());
		}
}

#endif