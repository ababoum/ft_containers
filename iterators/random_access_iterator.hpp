/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 22:02:28 by mababou           #+#    #+#             */
/*   Updated: 2022/07/21 16:51:23 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include <iostream>
# include <string>
# include "../utils/enable_if.hpp"

namespace ft {

	template< typename Iter >
	class random_access_iterator
	: public std::iterator<typename iterator_traits<Iter>::iterator_category,
		typename iterator_traits<Iter>::value_type,
		typename iterator_traits<Iter>::difference_type,
		typename iterator_traits<Iter>::pointer,
		typename iterator_traits<Iter>::reference>
	{
		
		public:
			typedef iterator_traits<Iter>					traits_type;
			typedef	Iter									iterator_type;
			typedef typename traits_type::pointer			pointer;
			typedef typename traits_type::reference			reference;
			typedef typename traits_type::iterator_category	iterator_category;
			typedef typename traits_type::value_type		value_type;
			typedef typename traits_type::difference_type	difference_type;
			typedef random_access_iterator<Iter>			iterator;

		private:
			pointer							_current;
		
		public:
			/* CONSTRUCTORS */

			/* 1 */
			random_access_iterator(): _current(pointer()) {}
			
			/* 2 */
			explicit random_access_iterator( pointer x )
			{
				_current = x;
			}
			
			template< class U >
			random_access_iterator( const random_access_iterator<U>& other )
			{
				_current = other.base();
			}

			/* MEMBER FUNCTIONS */
			
			template< class U >
			random_access_iterator& operator=( const random_access_iterator<U>& other )
			{
				_current = other.base();
				return (*this);
			}
			
			pointer base() const
			{
				return (_current);
			}
			
			reference operator*() const
			{
				return (*_current);
			}
			
			pointer operator->() const
			{
				return (&(operator*()));
			}
			
			reference operator[]( difference_type n )
			{
				return (_current[n]);
			}
			
			random_access_iterator& operator++()
			{
				++_current;
				return (*this);
			}
			
			random_access_iterator& operator--()
			{
				--_current;
				return (*this);
			}
			
			random_access_iterator operator++( int )
			{
				iterator tmp = *this;

				++_current;
				return (tmp);
			}

			random_access_iterator operator--( int )
			{
				iterator tmp = *this;

				--_current;
				return (tmp);
			}
			
			random_access_iterator operator+( difference_type n ) const
			{
				return (random_access_iterator<Iter>(base() + n));
			}

			random_access_iterator operator-( difference_type n ) const
			{
				return (random_access_iterator<Iter>(base() - n));
			}
			
			random_access_iterator& operator+=( difference_type n )
			{
				_current += n;
				return (*this);
			}
			
			random_access_iterator& operator-=( difference_type n )
			{
				_current -= n;
				return (*this);
			}
			
	};

	
	template< class T1, class T2 >
	bool operator==( const random_access_iterator<T1>& lhs,
		const random_access_iterator<T2>& rhs )
		{
			return lhs.base() == rhs.base();
		}
	
	template< class T1, class Iter >
	bool operator==( const random_access_iterator<T1>& lhs,
		const Iter & rhs )
		{
			return lhs.base() == rhs;
		}
	
	template< class T1, class Iter >
	bool operator==( const Iter & rhs,
		const random_access_iterator<T1>& lhs )
		{
			return lhs.base() == rhs;
		}
	
	template< class T1, class T2 >
	bool operator!=( const random_access_iterator<T1>& lhs,
		const random_access_iterator<T2>& rhs )
		{
			return lhs.base() != rhs.base();
		}
	template< class T1, class T2 >
	bool operator<( const random_access_iterator<T1>& lhs,
		const random_access_iterator<T2>& rhs )
		{
			return lhs.base() < rhs.base();
		}
	template< class T1, class T2 >
	bool operator<=( const random_access_iterator<T1>& lhs,
		const random_access_iterator<T2>& rhs )
		{
			return lhs.base() <= rhs.base();
		}
	template< class T1, class T2 >
	bool operator>( const random_access_iterator<T1>& lhs,
		const random_access_iterator<T2>& rhs )
		{
			return lhs.base() > rhs.base();
		}
	template< class T1, class T2 >
	bool operator>=( const random_access_iterator<T1>& lhs,
		const random_access_iterator<T2>& rhs )
		{
			return lhs.base() >= rhs.base();
		}

	template< class Iter >
	random_access_iterator<Iter> operator+( 
		typename random_access_iterator<Iter>::difference_type n,
		const random_access_iterator<Iter>& it )
		{
			return (random_access_iterator<Iter>(it.base() + n));
		}
		
	template< class Iter, class Iter2 >
	typename random_access_iterator<Iter>::difference_type operator-(
		const random_access_iterator<Iter>& lhs,
		const random_access_iterator<Iter2>& rhs )
		{
			return (lhs.base() - rhs.base());
		}


	template< typename Iter >
	class random_access_iterator <const Iter>
	: public std::iterator<typename iterator_traits<const Iter>::iterator_category,
		typename iterator_traits<const Iter>::value_type,
		typename iterator_traits<const Iter>::difference_type,
		typename iterator_traits<const Iter>::pointer,
		typename iterator_traits<const Iter>::reference>
	{
		
		public:
			typedef iterator_traits<const Iter>				traits_type;
			typedef	Iter									iterator_type;
			typedef typename traits_type::pointer			pointer;
			typedef typename traits_type::reference			reference;
			typedef typename traits_type::iterator_category	iterator_category;
			typedef typename traits_type::value_type		value_type;
			typedef typename traits_type::difference_type	difference_type;
			typedef random_access_iterator<const Iter>		const_iterator;

		private:
			pointer							_current;
		
		public:
			/* CONSTRUCTORS */

			/* 1 */
			random_access_iterator(): _current(pointer()) {}
			
			/* 2 */
			explicit random_access_iterator( pointer x )
			{
				_current = x;
			}
			
			template< class U >
			random_access_iterator( const random_access_iterator<U>& other )
			{
				_current = other.base();
			}

			/* MEMBER FUNCTIONS */
			
			template< class U >
			const_iterator & operator=( const random_access_iterator<U>& other )
			{
				this->base() = other->base();
				return (*this);
			}
			
			pointer base() const
			{
				return (_current);
			}
			
			reference operator*() const
			{
				return (*_current);
			}
			
			pointer operator->() const
			{
				return (&(operator*()));
			}
			
			value_type operator[]( difference_type n ) const
			{
				return (_current[n]);
			}
			
			const_iterator & operator++()
			{
				++_current;
				return (*this);
			}
			
			const_iterator & operator--()
			{
				--_current;
				return (*this);
			}
			
			const_iterator operator++( int )
			{
				const_iterator tmp = *this;

				++_current;
				return (tmp);
			}

			const_iterator operator--( int )
			{
				const_iterator tmp = *this;

				--_current;
				return (tmp);
			}
			
			const_iterator operator+( difference_type n ) const
			{
				return (random_access_iterator<const Iter>(base() + n));
			}

			const_iterator operator-( difference_type n ) const
			{
				return (random_access_iterator<const Iter>(base() - n));
			}
			
			const_iterator & operator+=( difference_type n )
			{
				_current += n;
				return (*this);
			}
			
			const_iterator & operator-=( difference_type n )
			{
				_current -= n;
				return (*this);
			}
	
	};		

} // namespace ft


#endif