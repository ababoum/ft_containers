/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:58:01 by mababou           #+#    #+#             */
/*   Updated: 2022/05/09 17:03:55 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"

namespace ft {

typedef std::size_t		size_type;

/*
** ------------------------------- CONSTRUCTORS -------------------------------
*/

template< class T, class Allocator >					/* 1 */
vector<T, Allocator>::vector()
{
	_size = 0;
	_capacity = 0;
	_array = NULL;
}

template< class T, class Allocator >					/* 2 */
vector<T, Allocator>::vector( const Allocator& alloc )
{
	_size = 0;
	_capacity = 0;
	_array = NULL;
	_allocator = alloc;
}

template< class T, class Allocator >					/* 3 */
vector<T, Allocator>::vector( size_type count,
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
vector<T, Allocator>::vector( size_type count )
{
	_size = count;
	_capacity = count;
	_array = _allocator.allocate(count);
}

template< class T, class Allocator >					/* 5 */
template< class InputIt >
vector<T, Allocator>::vector( InputIt first, InputIt last,
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
vector<T, Allocator>::vector( const vector<T, Allocator>& other )
{
	*this = other;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

template< class T, class Allocator >
vector<T, Allocator>::~vector()
{
	if (_array)
		delete [] _array;
}


/*
** ------------------------- GENERAL MEMBER FUNCTIONS -------------------------
*/

template< class T, class Allocator >
vector<T, Allocator> &	vector<T, Allocator>::operator=( const vector& other )
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
void vector<T, Allocator>::assign( size_type count, const T& value )
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
void vector<T, Allocator>::assign( InputIt first, InputIt last )
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
Allocator vector<T, Allocator>::get_allocator() const
{
	return (_allocator);
}

/*
** -------------------------------- ELEMENT ACCESS ----------------------------
*/

template< class T, class Allocator >
T&	vector<T, Allocator>::at( size_type pos )
{
	if (!(pos < size()))
		throw std::out_of_range("Specified position is out of range");
	return ((*this)[pos]);
}

template< class T, class Allocator >
const T&	vector<T, Allocator>::at( size_type pos ) const
{
	if (!(pos < size()))
		throw std::out_of_range("Specified position is out of range");
	return ((*this)[pos]);
}

template< class T, class Allocator >
T&	vector<T, Allocator>::operator[]( size_type pos )
{
	return (_array[pos]);
}

template< class T, class Allocator >
const T&	vector<T, Allocator>::operator[]( size_type pos ) const
{
	return (_array[pos]);
}

template< class T, class Allocator >
T&	vector<T, Allocator>::front()
{
	return ((*this)[0]);
}

template< class T, class Allocator >
const T&	vector<T, Allocator>::front() const
{
	return ((*this)[0]);
}

template< class T, class Allocator >
T&	vector<T, Allocator>::back()
{
	return ((*this)[this->size() - 1]);
}

template< class T, class Allocator >
const T&	vector<T, Allocator>::back() const
{
	return ((*this)[this->size() - 1]);
}

template< class T, class Allocator >
T*	vector<T, Allocator>::data()
{
	return (_array);
}

template< class T, class Allocator >
const T*	vector<T, Allocator>::data() const
{
	return (_array);
}

/*
** -------------------------------- ITERATORS ---------------------------------
*/

template< class T, class Allocator >
typename vector<T, Allocator>::iterator vector<T, Allocator>::begin()
{
	typename vector<T, Allocator>::iterator it(_array);

	return (it);
}

template< class T, class Allocator >
typename vector<T, Allocator>::const_iterator vector<T, Allocator>::begin() const
{
	typename vector<T, Allocator>::const_iterator it(_array);

	return (it);
}

template< class T, class Allocator >
typename vector<T, Allocator>::iterator vector<T, Allocator>::end()
{
	typename vector<T, Allocator>::iterator it = begin();
	for (size_type i = 0; i < _size; i++)
		it++;
	return (it);
}

template< class T, class Allocator >
typename vector<T, Allocator>::const_iterator vector<T, Allocator>::end() const
{
	typename vector<T, Allocator>::const_iterator it = begin();
	for (size_type i = 0; i < _size; i++)
		it++;
	return (it);
}

template< class T, class Allocator >
typename vector<T, Allocator>::reverse_iterator vector<T, Allocator>::rbegin()
{
	typename vector<T, Allocator>::reverse_iterator it(_array + _size - 1);

	return (it);
}

template< class T, class Allocator >
typename vector<T, Allocator>::const_reverse_iterator vector<T, Allocator>::rbegin() const
{
	typename vector<T, Allocator>::const_reverse_iterator it(_array + _size - 1);

	return (it);
}

template< class T, class Allocator >
typename vector<T, Allocator>::reverse_iterator vector<T, Allocator>::rend()
{
	typename vector<T, Allocator>::reverse_iterator it(_array - 1);

	return (it);
}

template< class T, class Allocator >
typename vector<T, Allocator>::const_reverse_iterator vector<T, Allocator>::rend() const
{
	typename vector<T, Allocator>::const_reverse_iterator it(_array - 1);

	return (it);
}
/*
** --------------------------------- CAPACITY ---------------------------------
*/

template< class T, class Allocator >
bool vector<T, Allocator>::empty() const
{
	return (_size == 0);
}

template< class T, class Allocator >
size_type vector<T, Allocator>::size() const
{
	return (_size);
}

template< class T, class Allocator >
size_type vector<T, Allocator>::max_size() const
{
	return (std::distance(begin(), end()));
}

template< class T, class Allocator >
void vector<T, Allocator>::reserve( size_type new_cap )
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
	
	if (tmp_array)
		delete [] tmp_array;
}

template< class T, class Allocator >
size_type vector<T, Allocator>::capacity() const
{
	return (_capacity);
}

/*
** -------------------------------- MODIFIERS ---------------------------------
*/

template< class T, class Allocator >
void vector<T, Allocator>::clear()
{
	if (_array)
		delete [] _array;
	_size = 0;
}

template< class T, class Allocator >
typename vector<T, Allocator>::iterator vector<T, Allocator>::insert( 
	typename vector<T, Allocator>::iterator pos, 
	const T& value )
{
	if (_capacity == 0)
		reserve(1);
	if (_size == _capacity)
		reserve(_size * 2);
	
	size_type i = 0;
	while ( i < _size) {
		if (*pos == _array[i++])
			break ;
	}
	size_type anchor = i;
	i = _size;
	while ( i != anchor ) {
		_array[i] = _array[i - 1];
		i--;
	}
	_array[anchor] = value;
	vector<T, Allocator>::iterator it(_array + anchor);
	return (it);
}

/* ************************************************************************** */
} // namespace ft
/* ************************************************************************** */