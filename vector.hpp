/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 14:06:48 by mababou           #+#    #+#             */
/*   Updated: 2022/07/13 16:06:43 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>

# include "iterators/iterators_traits.hpp"
# include "iterators/reverse_iterator.hpp"
# include "iterators/random_access_iterator.hpp"
# include "utils/equal.hpp"
# include "utils/lexicographical_compare.hpp"
# include "utils/is_integral.hpp"


namespace ft {

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
		typedef random_access_iterator<pointer, vector>			iterator;
		typedef random_access_iterator<const_pointer, vector>	const_iterator;
		typedef	reverse_iterator<const_iterator>				const_reverse_iterator;
		typedef reverse_iterator<iterator>						reverse_iterator;
		
		/* CONSTRUCTORS */
		vector(); 									/* 1 */
		explicit vector( const Allocator& alloc );	/* 2 */
		explicit vector( size_type count,
			const T& value = T(),
			const Allocator& alloc = Allocator());	/* 3 */
		template< class InputIt >					/* 5 */
		vector( InputIt first, InputIt last,
        	const Allocator& alloc = Allocator(),
				typename enable_if<!ft::is_integral< InputIt >::value, void* >::type* = NULL)
				{
					_size = 0;
					_capacity = 0;
					_allocator = alloc;
					_array = NULL;
					for (InputIt it = first; it != last; ++it)
						push_back(*it);
				}
		vector( const vector& other );				/* 6 */

		/* DESTRUCTOR */
		~vector();
		
		/* GENERAL MEMBER FUNCTIONS */
		vector& operator=( const vector& other );
		void assign( size_type count, const T& value );	/* 1 */
		template< class InputIt >						/* 2 */
		void assign( InputIt first, InputIt last,
			typename enable_if<!ft::is_integral< InputIt >::value, void* >::type* = NULL)
			{
				if (_array)
					delete [] _array;

				_size = 0;
				_capacity = 0;
				_array = NULL;
				for (InputIt it = first; it != last; ++it)
					push_back(*it);
			}
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
		iterator	insert( iterator pos, const T& value );						/* 1 */
		void		insert( iterator pos, size_type count, const T& value );	/* 3 */
		template< class InputIt >
		void		insert( iterator pos, InputIt first, InputIt last );		/* 4 */
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
bool operator!=( const vector<T,Alloc>& lhs,
	const vector<T,Alloc>& rhs );

template< class T, class Alloc >
bool operator<( const vector<T,Alloc>& lhs,
	const vector<T,Alloc>& rhs );

template< class T, class Alloc >
bool operator<=( const vector<T,Alloc>& lhs,
	const vector<T,Alloc>& rhs );

template< class T, class Alloc >
bool operator>( const vector<T,Alloc>& lhs,
	const vector<T,Alloc>& rhs );

template< class T, class Alloc >
bool operator>=( const vector<T,Alloc>& lhs,
	const vector<T,Alloc>& rhs );

template<class T, class Alloc>
void swap(vector<T, Alloc>& lhs, vector<T, Alloc>& rhs);

} // namespace ft

#include "vector.tpp"

#endif /* ********************************************************** VECTOR_H */