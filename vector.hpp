/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 14:06:48 by mababou           #+#    #+#             */
/*   Updated: 2022/07/20 16:17:48 by mababou          ###   ########.fr       */
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

		typedef	T												value_type;
		typedef	Allocator										allocator_type;
		typedef std::size_t										size_type;
		typedef std::ptrdiff_t									difference_type;
		typedef value_type&										reference;
		typedef const value_type&								const_reference;
		typedef typename Allocator::pointer						pointer;
		typedef typename Allocator::const_pointer				const_pointer;
		typedef random_access_iterator<pointer>					iterator;
		typedef const_random_access_iterator<const_pointer>		const_iterator;
		typedef	reverse_iterator<const_iterator>				const_reverse_iterator;
		typedef reverse_iterator<iterator>						reverse_iterator;
		

	private:
		void _reset_array()
		{
			if (_array)
			{
				for (size_type i = 0; i < _size; i++)
					_allocator.destroy(&_array[i]);
				_allocator.deallocate(_array, _capacity);
			}
		}

	public:
		/* CONSTRUCTORS */

		/* 1 */
		vector():
			_size(0), _array(NULL), _allocator(Allocator()), _capacity(0) {}
		
		/* 2 */
		explicit vector( const Allocator& alloc ):
			_size(0), _array(NULL), _allocator(alloc), _capacity(0) {}

		/* 3 */
		explicit vector( size_type count,
			const T& value = T(),
			const Allocator& alloc = Allocator())
		{
			_size = count;
			_capacity = count;
			_allocator = alloc;
			_array = _allocator.allocate(count);
			for (size_type i = 0; i < _size; i++) {
				_allocator.construct(&_array[i], value);
			}
		}
		
		/* 4 */
		template< class InputIt >
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

		/* 5 */
		vector( const vector& other )
		{
			*this = other;
		}

		/* DESTRUCTOR */
		~vector()
		{
			_reset_array();
		}
		
		/* GENERAL MEMBER FUNCTIONS */
		vector& operator=( const vector& other )
		{
			if (*this != other) {
				_reset_array();
				_size = other.size();
				_capacity = other.size();
				_allocator = other.get_allocator();
				_array = _allocator.allocate(_capacity);
				for (size_type i = 0; i < _size; i++)
					_array[i] = other[i];
			}
			return (*this);
		}

		/* 1 */
		void assign( size_type count, const T& value )
		{
			_reset_array();

			_size = count;
			_capacity = count;
			_array = _allocator.allocate(_capacity);
			for (size_type i = 0; i < _size; ++i)
				_allocator.construct(&_array[i], value);
		}

		/* 2 */
		template< class InputIt >
		void assign( InputIt first, InputIt last,
			typename enable_if<!ft::is_integral< InputIt >::value, void* >::type* = NULL)
		{
			_reset_array();

			_size = 0;
			_capacity = 0;
			_array = NULL;
			for (InputIt it = first; it != last; ++it)
				push_back(*it);
		}
		
		allocator_type get_allocator() const
		{
			return (_allocator);
		}

		/* ELEMENT ACCESS  */
		
		reference at( size_type pos )
		{
			if (!(pos < _size))
				throw std::out_of_range("Specified position is out of range");
			return ((*this)[pos]);
		}

		const_reference at( size_type pos ) const
		{
			if (!(pos < size()))
				throw std::out_of_range("Specified position is out of range");
			return ((*this)[pos]);
		}
		
		reference operator[]( size_type pos )
		{
			return (_array[pos]);
		}
		
		const_reference operator[]( size_type pos ) const
		{
			return (_array[pos]);
		}
		
		reference front()
		{
			return (*begin());
		}
		
		const_reference front() const
		{
			return (*begin());
		}
		
		reference back()
		{
			return (*(end() - 1));
		}
		
		const_reference back() const
		{
			return (*(end() - 1));
		}
		
		T* data()
		{
			return (_array);
		}
		
		const T* data() const
		{
			return (_array);
		}
		
		/* ITERATORS */
		
		iterator begin()
		{
			iterator it(_array);
			return it;
		}
		
		const_iterator begin() const
		{
			const_iterator it(_array);
			return it;
		}
		
		iterator end()
		{
			iterator it = begin() + _size;
			return it;
		}
		
		const_iterator end() const
		{
			const_iterator it = begin() + _size;
			return it;
		}
		
		reverse_iterator rbegin()
		{
			reverse_iterator it = end() - 1;
			return it;
			
		}
		
		const_reverse_iterator rbegin() const
		{
			const_reverse_iterator it = end() - 1;
			return it;
		}
		
		reverse_iterator rend()
		{
			reverse_iterator it = begin() - 1;
			return it;
		}
		
		const_reverse_iterator rend() const
		{
			const_reverse_iterator it = begin() - 1;
			return it;
		}

		/* CAPACITY */
		
		bool		empty() const
		{
			return _size == 0;
		}
		
		size_type	size() const
		{
			return _size;
		}

		size_type	max_size() const
		{
			return _allocator.max_size();
		}
		
		void		reserve( size_type new_cap )
		{
			if (new_cap <= _capacity)
				return ;
			if (new_cap > max_size())
				throw std::length_error("Maximum possible size is exceeded");
			
			T*	tmp_array;
			tmp_array = _allocator.allocate(new_cap);
			for (size_type i = 0; i < _size; i++)
				tmp_array[i] = _array[i];
			
			_reset_array();
			
			_capacity = new_cap;
			_array = tmp_array;
		}
		
		size_type	capacity() const
		{
			return _capacity;
		}

		/* MODIFIERS */
		
		void clear()
		{
			for (size_type i = 0; i < _size; ++i) {
				_allocator.destroy(&_array[i]);
			}
			_size = 0;
		}
		
		/* 1 */
		iterator	insert( iterator pos, const T& value )
		{
			if (_capacity == 0)
				reserve(1);
			if (_size == _capacity)
				reserve(_capacity * 2);
			
			iterator it = begin();
			while ( it != pos && it != end()) {
				++it;
			}
			
			iterator new_slot = it;
			it = end();
			while ( it != new_slot ) {
				*it = *(it - 1);
				--it;
			}
			_allocator.construct(&(*new_slot), value);
			++_size;
			return (new_slot);
		}

		/* 2 */
		void		insert( iterator pos, size_type count, const T& value )
		{
			if (count == 0)
				return ;
			if (_capacity == 0)
				reserve(count);
				
			size_type	target_capacity = _capacity;
			while (_size + count > target_capacity)
				target_capacity *= 2;
			reserve(target_capacity);
			
			iterator it = begin();
			while ( it != pos && it != end()) {
				++it;
			}
			
			iterator new_range_start = it;
			it = end() + count - 1;
			while ( it != new_range_start + count - 1 ) {
				*it = *(it - count);
				--it;
			}
			
			for (size_type i = 0; i < count; ++i) {
				_allocator.construct(&(*new_range_start), value);
				++new_range_start;
			}
			_size += count;
		}

		/* 3 */
		template< class InputIt >
		void		insert(iterator pos, InputIt first, InputIt last,
			typename enable_if<!ft::is_integral< InputIt >::value, void* >::type* = NULL)
		{
			if (first >= last)
				return ;

			size_type count = std::distance(first, last);

			if (_capacity == 0)
				reserve(count);
			size_type	target_capacity = _capacity;
			while (_size + count > target_capacity)
				target_capacity *= 2;
			reserve(target_capacity);
			
			iterator it = begin();
			while ( it != pos && it != end()) {
				++it;
			}
			
			iterator new_range_start = it;
			it = end() + count - 1;
			while ( it != new_range_start + count - 1 ) {
				*it = *(it - count);
				--it;
			}
			
			for (size_type i = 0; i < count; ++i) {
				_allocator.construct(&(*new_range_start), *first);
				++new_range_start;
				++first;
			}
			_size += count;
		}
		
		iterator	erase( iterator pos )
		{
			iterator it = begin();
			while ( it != pos && it != end()) {
				++it;
			}
			if (it == end())
				return (pos);
			
			while ( it != end() - 1 ) {
				_allocator.destroy(&(*it));
				_allocator.construct(&(*it), *(it + 1));
				++it;
			}
			--_size;
			return (pos);
		}
		
		iterator	erase( iterator first, iterator last )
		{
			if (first >= last)
				return (last);

			size_type count = std::distance(first, last);
			
			iterator it = begin();
			while ( it != first && it != end()) {
				++it;
			}
			if (it == end())
				return (last);
			
			
			while (it + count != end()) {
				_allocator.destroy(&(*it));
				_allocator.construct(&(*it), *(it + count));
				++it;
			}
			
			_size -= count;
			return (end());
		}

		void		push_back( const T& value )
		{
			if (_capacity == 0)
				reserve(1);
			if (_size == _capacity)
				reserve(_size * 2);

			_allocator.construct(&_array[_size], value);
			_size++;
		}
		
		void		pop_back()
		{
			_allocator.destroy(&_array[_size - 1]);
			_size--;
		}
		
		void		resize( size_type count, T value = T() )
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
		
		void		swap( vector& other )
		{
			std::swap(_array, other._array);
			std::swap(_size, other._size);
			std::swap(_capacity, other._capacity);
			std::swap(_allocator, other._allocator);
		}
		
	private:
		size_type			_size;
		pointer				_array;
		
		allocator_type		_allocator;
		size_type			_capacity;
};

template<class T, class Alloc>
bool operator==(const vector<T, Alloc>& lhs,
	const vector<T, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		return equal(lhs.begin(), lhs.end(), rhs.begin());
	}

template< class T, class Alloc >
bool operator!=( const vector<T,Alloc>& lhs,
	const vector<T,Alloc>& rhs )
	{
		return !(lhs == rhs);
	}

template< class T, class Alloc >
bool operator<( const vector<T,Alloc>& lhs,
	const vector<T,Alloc>& rhs )
	{
		return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

template< class T, class Alloc >
bool operator<=( const vector<T,Alloc>& lhs,
	const vector<T,Alloc>& rhs )
	{
		return !(lhs > rhs);
	}

template< class T, class Alloc >
bool operator>( const vector<T,Alloc>& lhs,
	const vector<T,Alloc>& rhs )
	{
		return (rhs < lhs);
	}

template< class T, class Alloc >
bool operator>=( const vector<T,Alloc>& lhs,
	const vector<T,Alloc>& rhs )
	{
		return !(lhs < rhs);
	}

template<class T, class Alloc>
void swap(vector<T, Alloc>& lhs, vector<T, Alloc>& rhs)
{
	lhs.swap(rhs);
}

} // namespace ft

#endif /* ********************************************************** VECTOR_H */