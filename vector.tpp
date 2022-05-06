/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:58:01 by mababou           #+#    #+#             */
/*   Updated: 2022/05/06 17:34:39 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"

namespace ft {

typedef std::size_t		size_type;

/*
** ------------------------------- CONSTRUCTORS -------------------------------
*/

template< class T, class Allocator >					/* 1 */
ft::vector<T, Allocator>::vector()
{
	_size = 0;
	_capacity = 0;
	_array = NULL;
}

template< class T, class Allocator >					/* 2 */
ft::vector<T, Allocator>::vector( const Allocator& alloc )
{
	_size = 0;
	_capacity = 0;
	_array = NULL;
	_allocator = alloc;
}

template< class T, class Allocator >					/* 3 */
ft::vector<T, Allocator>::vector( size_type count,
			const T& value,
			const Allocator& alloc)
{
	_size = count;
	_capacity = count;
	_allocator = alloc;
	_array = _allocator.allocate(count);
	for (size_type i = 0; i < _size; i++) {
		_array[i] = value;
	}
}

template< class T, class Allocator >					/* 4 */
ft::vector<T, Allocator>::vector( size_type count )
{
	_size = count;
	_capacity = count;
	_array = _allocator.allocate(count);
}

template< class T, class Allocator >					/* 5 */
template< class InputIt >
ft::vector<T, Allocator>::vector( InputIt first, InputIt last,
        	const Allocator& alloc)
{
	size_type	count = 0;
	
	for (InputIt it = first; it != last; ++it)
		count++;
	_size = count;
	_capacity = 0;
	_allocator = alloc;
	_array = _allocator.allocate(_capacity);

	count = 0;
	for (InputIt it = first; it != last; ++it)
		_array[count++] = *it;
}

template< class T, class Allocator >					/* 6 */
ft::vector<T, Allocator>::vector( const vector& other )
{
	*this = other;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

template< class T, class Allocator >
ft::vector<T, Allocator>::~vector()
{
	if (_array)
		delete [] _array;
}


/*
** ------------------------- GENERAL MEMBER FUNCTIONS -------------------------
*/

template< class T, class Allocator >
ft::vector<T, Allocator> &	ft::vector<T, Allocator>::operator=( const vector& other )
{
	if (*this != other) {
		if (_array)
			delete [] _array;
		_size = other.size();
		_capacity = other.capacity();
		_allocator = other.get_allocator();
		_array = _allocator.allocate(_size);
		for (size_type i = 0; i < _size; i++)
			_array[i] = other[i];
	}	
	return (*this);
}

template< class T, class Allocator >
void ft::vector<T, Allocator>::assign( size_type count, const T& value )
{
	if (_array)
		delete [] _array;
	_size = count;
	_array = _allocator.allocate(_size);
	for (size_type i = 0; i < _size; i++)
		_array[i] = value;
}

template< class T, class Allocator >
template< class InputIt>
void ft::vector<T, Allocator>::assign( InputIt first, InputIt last )
{
	if (_array)
		delete [] _array;

	size_type	count = 0;
	
	for (InputIt it = first; it != last; ++it)
		count++;
	_size = count;
	_array = _allocator.allocate(_size);
	count = 0;
	for (InputIt it = first; it != last; ++it)
		_array[count++] = *it;
}

template< class T, class Allocator >
Allocator ft::vector<T, Allocator>::get_allocator() const
{
	return (_allocator);
}

/*
** -------------------------------- ELEMENT ACCESS ----------------------------
*/

template< class T, class Allocator >
T&	ft::vector<T, Allocator>::at( size_type pos )
{
	if (!(pos < size()))
		throw std::out_of_range("Specified position is out of range");
	return ((*this)[pos]);
}

template< class T, class Allocator >
const T&	ft::vector<T, Allocator>::at( size_type pos ) const
{
	if (!(pos < size()))
		throw std::out_of_range("Specified position is out of range");
	return ((*this)[pos]);
}

template< class T, class Allocator >
T&	ft::vector<T, Allocator>::operator[]( size_type pos )
{
	return (_array[pos]);
}

template< class T, class Allocator >
const T&	ft::vector<T, Allocator>::operator[]( size_type pos ) const
{
	return (_array[pos]);
}

template< class T, class Allocator >
T&	ft::vector<T, Allocator>::front()
{
	return ((*this)[0]);
}

template< class T, class Allocator >
const T&	ft::vector<T, Allocator>::front() const
{
	return ((*this)[0]);
}

template< class T, class Allocator >
T&	ft::vector<T, Allocator>::back()
{
	return ((*this)[this->size() - 1]);
}

template< class T, class Allocator >
const T&	ft::vector<T, Allocator>::back() const
{
	return ((*this)[this->size() - 1]);
}

template< class T, class Allocator >
T*	ft::vector<T, Allocator>::data()
{
	return (_array);
}

template< class T, class Allocator >
const T*	ft::vector<T, Allocator>::data() const
{
	return (_array);
}


/*
** --------------------------------- CAPACITY ---------------------------------
*/

template< class T, class Allocator >
bool ft::vector<T, Allocator>::empty() const
{
	return (_size == 0);
}

template< class T, class Allocator >
size_type ft::vector<T, Allocator>::size() const
{
	return (_size);
}

template< class T, class Allocator >
size_type ft::vector<T, Allocator>::max_size() const
{
	return (std::distance(begin(), end()));
}

template< class T, class Allocator >
void ft::vector<T, Allocator>::reserve( size_type new_cap )
{
	if (new_cap <= capacity())
		return ;
	if (new_cap > max_size())
		throw std::length_error("Maximum possible size is exceeded");
	
	T*	tmp_array;
	tmp_array = _allocator.allocate(_size);
	for (size_type i = 0; i < _size; i++)
		tmp_array[i] = _array[i];
	
	if (_array)
		delete [] _array;
	
	_capacity = new_cap;
	_array = _allocator.allocate(_capacity);
	for (size_type i = 0; i < _size; i++)
		_array[i] = tmp_array[i];
}

template< class T, class Allocator >
size_type ft::vector<T, Allocator>::capacity() const
{
	return (_capacity);
}


/* ************************************************************************** */
} // namespace ft
/* ************************************************************************** */