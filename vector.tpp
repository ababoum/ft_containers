/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:58:01 by mababou           #+#    #+#             */
/*   Updated: 2022/06/14 10:12:49 by mababou          ###   ########.fr       */
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

template< class T, class Allocator >					/* 5 */
template< class InputIt,
enable_if<is_integral<InputIt>::value, bool>
>
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
		_capacity = other.size();
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
	for (size_type i = 0; i < _size; ++i)
		_allocator.construct(&_array[i], value);
}

template< class T, class Allocator >
template< class InputIt,
enable_if<is_integral<InputIt>::value, bool>
>
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
	return (*begin());
}

template< class T, class Allocator >
const T&	vector<T, Allocator>::front() const
{
	return (*begin());
}

template< class T, class Allocator >
T&	vector<T, Allocator>::back()
{
	return (*(end() - 1));
}

template< class T, class Allocator >
const T&	vector<T, Allocator>::back() const
{
	return (*(end() - 1));
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
	typename vector<T, Allocator>::iterator it = begin() + _size;

	return (it);
}

template< class T, class Allocator >
typename vector<T, Allocator>::const_iterator vector<T, Allocator>::end() const
{
	typename vector<T, Allocator>::const_iterator it = begin() + _size;

	return (it);
}

template< class T, class Allocator >
typename vector<T, Allocator>::reverse_iterator vector<T, Allocator>::rbegin()
{
	typename vector<T, Allocator>::reverse_iterator it(end());

	return (it);
}

template< class T, class Allocator >
typename vector<T, Allocator>::const_reverse_iterator vector<T, Allocator>::rbegin() const
{
	typename vector<T, Allocator>::const_reverse_iterator it(end());

	return (it);
}

template< class T, class Allocator >
typename vector<T, Allocator>::reverse_iterator vector<T, Allocator>::rend()
{
	typename vector<T, Allocator>::reverse_iterator it(begin());

	return (it);
}

template< class T, class Allocator >
typename vector<T, Allocator>::const_reverse_iterator vector<T, Allocator>::rend() const
{
	typename vector<T, Allocator>::const_reverse_iterator it(begin());

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
	size_type	i = 0;
	for (; i < _size; ++i) {
		_allocator.destroy(&_array[i]);
	}
	_size = 0;
}

template< class T, class Allocator >
typename vector<T, Allocator>::iterator vector<T, Allocator>::insert
( typename vector<T, Allocator>::iterator pos, const T& value )
{
	if (_capacity == 0)
		reserve(1);
	if (_size == _capacity)
		reserve(_capacity * 2);
	
	typename vector<T, Allocator>::iterator it = begin();
	while ( it != pos && it != end()) {
		++it;
	}
	
	typename vector<T, Allocator>::iterator new_slot = it;
	it = end();
	while ( it != new_slot ) {
		*it = *(it - 1);
		--it;
	}
	*new_slot = value;
	++_size;
	return (new_slot);
}

template< class T, class Allocator >
void	vector<T, Allocator>::insert
( typename vector<T, Allocator>::iterator pos, size_type count, const T& value )
{
	if (count == 0)
		return ;
	if (_capacity == 0)
		reserve(count);
	size_type	target_capacity = _capacity;
	while (_size + count > target_capacity)
		target_capacity *= 2;
	reserve(target_capacity);
	
	typename vector<T, Allocator>::iterator it = begin();
	while ( it != pos && it != end()) {
		++it;
	}
	
	typename vector<T, Allocator>::iterator new_range_start = it;
	it = end() + count - 1;
	while ( it != new_range_start + count - 1 ) {
		*it = *(it - count);
		--it;
	}
	
	for (size_type i = 0; i < count; ++i) {
		*new_range_start = value;
		++new_range_start;
	}
	_size += count;
}

template< class T, class Allocator >
template< class InputIt >
void	vector<T, Allocator>::insert
( typename vector<T, Allocator>::iterator pos, InputIt first, InputIt last )
{
	if (first >= last)
		return ;

	size_type count = 0;
	for (InputIt countIt = first; countIt!= last; ++countIt) {
		++count;
	}
	if (_capacity == 0)
		reserve(count);
	size_type	target_capacity = _capacity;
	while (_size + count > target_capacity)
		target_capacity *= 2;
	reserve(target_capacity);
	
	typename vector<T, Allocator>::iterator it = begin();
	while ( it != pos && it != end()) {
		++it;
	}
	
	typename vector<T, Allocator>::iterator new_range_start = it;
	it = end() + count - 1;
	while ( it != new_range_start + count - 1 ) {
		*it = *(it - count);
		--it;
	}
	
	for (size_type i = 0; i < count; ++i) {
		*new_range_start = *first;
		++new_range_start;
		++first;
	}
	_size += count;
}

template< class T, class Allocator >
typename vector<T, Allocator>::iterator	vector<T, Allocator>::erase
( typename vector<T, Allocator>::iterator pos )
{
	typename vector<T, Allocator>::iterator it = begin();
	while ( it != pos && it != end()) {
		++it;
	}
	if (it == end())
		return (pos);
	
	while ( it != end() - 1 ) {
		*it = *(it + 1);
		++it;
	}
	--_size;
	return (pos);
}

template< class T, class Allocator >
typename vector<T, Allocator>::iterator	vector<T, Allocator>::erase
( typename vector<T, Allocator>::iterator first, 
	typename vector<T, Allocator>::iterator last )
{
	if (first >= last)
		return (last);

	size_type count = 0;
	for (typename vector<T, Allocator>::iterator countIt = first; countIt!= last; ++countIt) {
		++count;
	}
	
	typename vector<T, Allocator>::iterator it = begin();
	while ( it != first && it != end()) {
		++it;
	}
	if (it == end())
		return (last);
	if (it + count < end()) {
		while (it + count != end()) {
			*it = *(it + count);
			++it;
		}
	}
	_size -= count;
	return (end());
}

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
	else if (_size < count) {
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