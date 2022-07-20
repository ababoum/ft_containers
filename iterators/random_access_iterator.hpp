/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 22:02:28 by mababou           #+#    #+#             */
/*   Updated: 2022/07/20 19:24:22 by mababou          ###   ########.fr       */
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
			random_access_iterator()
			{
				_current(pointer());
			}
			
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
	template< class Iter >
	typename random_access_iterator<Iter>::difference_type operator-(
		const random_access_iterator<Iter>& lhs,
		const random_access_iterator<Iter>& rhs )
		{
			return (rhs.base() - lhs.base());
		}

	template< typename Iter >
	class const_random_access_iterator
	{
		
		public:
			typedef iterator_traits<Iter>				traits_type;
			typedef	Iter									iterator_type;
			typedef typename traits_type::pointer			pointer;
			typedef typename traits_type::reference			reference;
			typedef typename traits_type::iterator_category	iterator_category;
			typedef typename traits_type::value_type		value_type;
			typedef typename traits_type::difference_type	difference_type;
			typedef const_random_access_iterator<Iter>		const_iterator;

		private:
			pointer							_current;
		
		public:
			/* CONSTRUCTORS */

			/* 1 */
			const_random_access_iterator()
			{
				_current(pointer());
			}
			
			/* 2 */
			explicit const_random_access_iterator( pointer x )
			{
				_current = x;
			}
			
			template< class U >
			const_random_access_iterator( const const_random_access_iterator<U>& other )
			{
				_current = other.base();
			}

			/* MEMBER FUNCTIONS */
			
			template< class U >
			const_iterator & operator=( const const_random_access_iterator<U>& other )
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
				return (const_random_access_iterator<Iter>(base() + n));
			}

			const_iterator operator-( difference_type n ) const
			{
				return (const_random_access_iterator<Iter>(base() - n));
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
	
	template< class T1, class T2 >
	bool operator==( const const_random_access_iterator<T1>& lhs,
		const const_random_access_iterator<T2>& rhs )
		{
			return lhs.base() == rhs.base();
		}
	template< class T1, class T2 >
	bool operator!=( const const_random_access_iterator<T1>& lhs,
		const const_random_access_iterator<T2>& rhs )
		{
			return lhs.base() != rhs.base();
		}
	template< class T1, class T2 >
	bool operator<( const const_random_access_iterator<T1>& lhs,
		const const_random_access_iterator<T2>& rhs )
		{
			return lhs.base() < rhs.base();
		}
	template< class T1, class T2 >
	bool operator<=( const const_random_access_iterator<T1>& lhs,
		const const_random_access_iterator<T2>& rhs )
		{
			return lhs.base() <= rhs.base();
		}
	template< class T1, class T2 >
	bool operator>( const const_random_access_iterator<T1>& lhs,
		const const_random_access_iterator<T2>& rhs )
		{
			return lhs.base() > rhs.base();
		}
	template< class T1, class T2 >
	bool operator>=( const const_random_access_iterator<T1>& lhs,
		const const_random_access_iterator<T2>& rhs )
		{
			return lhs.base() >= rhs.base();
		}

	template< class Iter >
	const_random_access_iterator<Iter> operator+( 
		typename const_random_access_iterator<Iter>::difference_type n,
		const const_random_access_iterator<Iter>& it )
		{
			return (const_random_access_iterator<Iter>(it.base() + n));
		}
	template< class Iter >
	typename const_random_access_iterator<Iter>::difference_type operator-(
		const const_random_access_iterator<Iter>& lhs,
		const const_random_access_iterator<Iter>& rhs )
		{
			return (rhs.base() - lhs.base());
		}

} // namespace ft


#endif