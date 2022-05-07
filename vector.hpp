/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 14:06:48 by mababou           #+#    #+#             */
/*   Updated: 2022/05/07 16:35:06 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <string>

# include "iterators/iterators_traits.hpp"

namespace ft {

template<class T, class Allocator = std::allocator<T> > class vector;

template<class T, class Allocator>
bool operator==(const vector<T, Allocator>& x,
	const vector<T, Allocator>& y);

template<class T, class Allocator>
void swap(vector<T, Allocator>& x, vector<T, Allocator>& y);

template< class T, class Allocator>
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
		typedef typename ft::iterator_traits<T*>::value_type			iterator;
		typedef const typename ft::iterator_traits<T*>::value_type	const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef	ft::reverse_iterator<const_iterator>		const_reverse_iterator;
		
		/* CONSTRUCTORS */
		vector(); 									/* 1 */
		explicit vector( const Allocator& alloc );	/* 2 */
		explicit vector( size_type count,
			const T& value,
			const Allocator& alloc);	/* 3 */
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
		reference operator[]( size_type pos );
		const_reference operator[]( size_type pos ) const;
		reference 		front();
		const_reference front() const;
		reference 		back();
		const_reference back() const;
		T* data();
		const T* data() const;
		
		/* ITERATORS */
		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		reverse_iterator rend();
		const_reverse_iterator rend() const;

		/* CAPACITY */
		bool empty() const;
		size_type size() const;
		size_type max_size() const;
		void reserve( size_type new_cap );
		size_type capacity() const;

	private:
		size_type			_size;
		value_type*			_array;
		
		allocator_type		_allocator;
		size_type			_capacity;
};

} // namespace ft

#include "vector.tpp"

#endif /* ********************************************************** VECTOR_H */