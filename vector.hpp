/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 14:06:48 by mababou           #+#    #+#             */
/*   Updated: 2022/06/10 15:02:02 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <string>

# include "iterators/iterators_traits.hpp"
# include "iterators/reverse_iterator.hpp"
# include "iterators/random_access_iterator.hpp"
# include "iterators/const_random_access_iterator.hpp"

namespace ft {

template< std::iterator >
template< class T, class Allocator = std::allocator<T> >
class vector
{
	public:

		typedef	T											value_type;
		typedef	Allocator									allocator_type;
		typedef std::size_t									size_type;
		typedef std::ptrdiff_t								difference_type;
		typedef value_type&									reference;
		typedef const value_type&							const_reference;
		typedef typename Allocator::pointer					pointer;
		typedef typename Allocator::const_pointer			const_pointer;
		typedef ft::random_access_iterator<T>				iterator;
		typedef ft::random_access_iterator<const T>			const_iterator;
		typedef ft::reverse_iterator<T>						reverse_iterator;
		typedef	ft::reverse_iterator<const T>				const_reverse_iterator;
		
		/* CONSTRUCTORS */
		vector(); 									/* 1 */
		explicit vector( const Allocator& alloc );	/* 2 */
		explicit vector( size_type count,
			const T& value,
			const Allocator& alloc);				/* 3 */
		explicit vector( size_type count );			/* 4 */
		template< class InputIt >
		vector( InputIt first, InputIt last,
        	const Allocator& alloc = Allocator());	/* 5 */
		vector( const vector& other );				/* 6 */

		/* DESTRUCTOR */
		~vector();
		
		/* GENERAL MEMBER FUNCTIONS */
		vector& operator=( const vector& other );
		void assign( size_type count, const T& value );	/* 1 */
		template< class InputIt >
		void assign( InputIt first, InputIt last );		/* 2 */
		allocator_type get_allocator() const;

		/* ELEMENT ACCESS  */
		reference 		at( size_type pos );
		const_reference at( size_type pos ) const;
		reference 		operator[]( size_type pos );
		const_reference operator[]( size_type pos ) const;
		reference 		front();
		const_reference front() const;
		reference 		back();
		const_reference back() const;
		T* data();
		const T* data() const;
		
		/* ITERATORS */
		iterator 		begin();
		const_iterator	begin() const;
		iterator		end();
		const_iterator	end() const;
		reverse_iterator		rbegin();
		const_reverse_iterator	rbegin() const;
		reverse_iterator		rend();
		const_reverse_iterator	rend() const;

		/* CAPACITY */
		bool		empty() const;
		size_type	size() const;
		size_type	max_size() const;
		void		reserve( size_type new_cap );
		size_type	capacity() const;

		/* MODIFIERS */
		void		clear();
		iterator	insert( iterator pos, const T& value );
		void		insert( iterator pos, size_type count, const T& value );
		template< class InputIt >
		void		insert( iterator pos, InputIt first, InputIt last );
		iterator	erase( iterator pos );
		iterator	erase( iterator first, iterator last );
		void		push_back( const T& value );
		void		pop_back();
		void		resize( size_type count, T value = T() );
		void		swap( vector& other );
		
	private:
		size_type			_size;
		pointer				_array;
		
		allocator_type		_allocator;
		size_type			_capacity;
};

template<class T, class Alloc>
bool operator==(const vector<T, Alloc>& x,
	const vector<T, Alloc>& y);

template< class T, class Alloc >
bool operator!=( const ft::vector<T,Alloc>& lhs,
	const ft::vector<T,Alloc>& rhs );

template< class T, class Alloc >
bool operator<( const ft::vector<T,Alloc>& lhs,
	const ft::vector<T,Alloc>& rhs );

template< class T, class Alloc >
bool operator<=( const ft::vector<T,Alloc>& lhs,
	const ft::vector<T,Alloc>& rhs );

template< class T, class Alloc >
bool operator>( const ft::vector<T,Alloc>& lhs,
	const ft::vector<T,Alloc>& rhs );

template< class T, class Alloc >
bool operator>=( const ft::vector<T,Alloc>& lhs,
	const ft::vector<T,Alloc>& rhs );

template<class T, class Alloc>
void swap(vector<T, Alloc>& lhs, vector<T, Alloc>& rhs);

} // namespace ft

#include "vector.tpp"

#endif /* ********************************************************** VECTOR_H */