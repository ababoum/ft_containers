/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:58:01 by mababou           #+#    #+#             */
/*   Updated: 2022/06/11 17:33:29 by mababou          ###   ########.fr       */
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
	_array = (NULL);
	_allocator = Allocator();
	_capacity = 0;
}

template< class T, class Allocator >					/* 2 */
vector<T, Allocator>::vector( const Allocator& alloc )
{
	_size = 0;
	_array = NULL;
	_allocator = alloc;
	_capacity = 0;
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
		_allocator.construct(&_array[i], value);
	}
}

template< class T, class Allocator >					/* 4 */
vector<T, Allocator>::vector( size_type count )
{
	_size = count;
	_capacity = count;
	_allocator = Allocator();
	_array = _allocator.allocate(count);
	for (size_type i = 0; i < _size; i++) {
		_allocator.construct(&_array[i], T());
	}
}

template< class T, class Allocator >					/* 5 */
template< class InputIt >
vector<T, Allocator>::vector( InputIt first, InputIt last,
        	const Allocator& alloc)
{
	_size = 0;
	_capacity = 0;
	_allocator = alloc;
	_array = NULL;
	for (InputIt it = first; it != last; ++it)
		push_back(*it);
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
		_array = _allocator.allocate(_capacity);
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
	_capacity = count;
	_array = _allocator.allocate(_capacity);
	for (size_type i = 0; i < _size; i++)
		_allocator.construct(&_array[i], value);
}

template< class T, class Allocator >
template< class InputIt>
void vector<T, Allocator>::assign( InputIt first, InputIt last )
{
	if (_array)
		delete [] _array;

	_size = 0;
	_capacity = 0;
	_array = NULL;
	for (InputIt it = first; it != last; ++it)
		push_back(*it);
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
	return (*this->begin());
}

template< class T, class Allocator >
const T&	vector<T, Allocator>::front() const
{
	return (*this->begin());
}

template< class T, class Allocator >
T&	vector<T, Allocator>::back()
{
	return (_array[_size]);
}

template< class T, class Allocator >
const T&	vector<T, Allocator>::back() const
{
	return (_array[_size]);
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
	return (_allocator.max_size());
}

template< class T, class Allocator >
void vector<T, Allocator>::reserve( size_type new_cap )
{
	if (new_cap <= _capacity)
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

// INSERT

// ERASE

template< class T, class Allocator >
void vector<T, Allocator>::push_back( const T& value )
{
	if (_capacity == 0)
		reserve(1);
	if (_size == _capacity)
		reserve(_size * 2);

	_allocator.construct(&_array[_size], value);
	_size++;
}

template< class T, class Allocator >
void vector<T, Allocator>::pop_back()
{
	_allocator.destroy(&_array[_size - 1]);
	_size--;
}

template< class T, class Allocator >
void vector<T, Allocator>::resize( size_type count, T value )
{
	if (_size > count) {
		for (size_type i = count; i < _size; i++) {
			pop_back();
		}
	}
	else {
		for (size_type i = _size; i < count; i++) {
			push_back(value);
		}
	}
}

template< class T, class Allocator >
void vector<T, Allocator>::swap( vector& other )
{
	std::swap(_array, other._array);
	std::swap(_size, other._size);
	std::swap(_capacity, other._capacity);
}

/*
** ----------------------------- NON-MEMBER FUNCTIONS -----------------------------
*/

template<class T, class Alloc>
bool operator==(const vector<T, Alloc>& lhs,
	const vector<T, Alloc>& rhs)
{
	if (lhs.size() != rhs.size())
		return false;
	return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template< class T, class Alloc >
bool operator!=( const std::vector<T,Alloc>& lhs,
	const std::vector<T,Alloc>& rhs )
{
	return !(lhs == rhs);
}

template< class T, class Alloc >
bool operator<( const std::vector<T,Alloc>& lhs,
	const std::vector<T,Alloc>& rhs )
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template< class T, class Alloc >
bool operator<=( const std::vector<T,Alloc>& lhs,
	const std::vector<T,Alloc>& rhs )
{
	return !(lhs > rhs);
}

template< class T, class Alloc >
bool operator>( const std::vector<T,Alloc>& lhs,
	const std::vector<T,Alloc>& rhs )
{
	return (rhs < lhs);
}

template< class T, class Alloc >
bool operator>=( const std::vector<T,Alloc>& lhs,
	const std::vector<T,Alloc>& rhs )
{
	return !(lhs < rhs);
}

template< class T, class Alloc >
void swap(vector<T, Alloc>& lhs, vector<T, Alloc>& rhs)
{
	lhs.swap(rhs);
}


/* ************************************************************************** */
} // namespace ft
/* ************************************************************************** */