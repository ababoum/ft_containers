/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 14:06:48 by mababou           #+#    #+#             */
/*   Updated: 2022/07/27 21:31:48 by mababou          ###   ########.fr       */
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
		typedef random_access_iterator<const_pointer>			const_iterator;
		typedef	ft::reverse_iterator<const_iterator>			const_reverse_iterator;
		typedef ft::reverse_iterator<iterator>					reverse_iterator;
		

	private:
		void _reset_array()
		{
			if (_size > 0)
			{
				for (size_type i = 0; i < _size; ++i)
				{
					_allocator.destroy(&_array[i]);
				}
				_size = 0;
			}

			if (_array)
			{
				_allocator.deallocate(_array, sizeof(T) * _capacity);
				_capacity = 0;
				_array = NULL;
			}
		}

		template<typename _ForwardIterator>
    	void _assignHelper(_ForwardIterator first, _ForwardIterator last,
		    std::forward_iterator_tag)
		{
			size_type count = std::distance(first, last);
			T* tmp = _allocator.allocate(sizeof(T) * count);

			_ForwardIterator it = first;
			for (size_type i = 0; i < count; ++i)
				_allocator.construct(tmp + i, *(it++));

			_reset_array();
			_size = count;
			_capacity = count;
			_array = _allocator.allocate(sizeof(T) * _capacity);
			for (size_type i = 0; i < _size; ++i)
				_allocator.construct(_array + i, tmp[i]);

			for (size_type i = 0; i < _size; ++i)
				_allocator.destroy(tmp + i);
			_allocator.deallocate(tmp, sizeof(T) * count);
		}

		template<typename _InputIterator>
    	void _assignHelper(_InputIterator first, _InputIterator last,
		    std::input_iterator_tag)
		{
			pointer tmp = _array;
			size_type	count = 0;
			
			while (first != last && tmp != (_array + _size))
			{
				*tmp = *first;
				++tmp;
				++first;
				++count;
			}

			if (first == last)
			{
				resize(count);
			}
			else
			{
				insert(end(), first, last);
			}
		}

		template<typename _InputIterator>
		void _insertHelper(iterator pos, _InputIterator first,
		      _InputIterator last, std::input_iterator_tag)
		{
			if (pos == end())
			{
				while (first != last)
				{
					insert(end(), *first);
					++first;
				}
			}
			else if (first != last)
			{
				size_type pos_index = std::distance(begin(), pos);
				size_type count = 0;
				_InputIterator tmp(first);
			
				while (tmp != last)
					++count;

				if (_capacity == 0)
					reserve(count);
				size_type	target_capacity = _capacity;
				while (_size + count > target_capacity)
					target_capacity *= 2;
				reserve(target_capacity);
				
				iterator it = begin();
				iterator pos_after_resize(begin() + pos_index);

				while ( it != pos_after_resize && it != end()) {
					++it;
				}
				
				if (it == end())
				{
					while (first != last)
					{
						_allocator.construct(&(*it), *first);
						++_size;
						++first;
						++it;
					}
					return ;
				}
				
				iterator new_range_start = it;
				it = end() + count - 1;
				for (size_type i = 0; i < count; ++i) {
					_allocator.construct(&(*it), *(it - count));
					--it;
				}
				
				for (size_type i = 0; i < _size - pos_index; ++i) {
					*new_range_start = *first;
					++new_range_start;
					++first;
				}
				_size += count;
			}
		}

		template<typename _ForwardIterator>
		void _insertHelper(iterator pos, _ForwardIterator first,
		      _ForwardIterator last, std::forward_iterator_tag)
		{
			size_t pos_index = std::distance(begin(), pos);
			
			if (std::distance(first, last) <= 0)
				return ;

			size_type count = std::distance(first, last);

			if (_capacity == 0)
				reserve(count);
			size_type	target_capacity = _capacity;
			while (_size + count > target_capacity)
				target_capacity *= 2;
			reserve(target_capacity);
			
			iterator it = begin();
			iterator pos_after_resize(begin() + pos_index);

			while ( it != pos_after_resize && it != end()) {
				++it;
			}

			if (it == end())
			{
				while (first != last)
				{
					_allocator.construct(&(*it), *first);
					++it;
					++_size;
					++first;
				}
				return ;
			}

			iterator new_range_start = pos_after_resize;
			it = end() + count - 1; // the future end()
			
			// extend the end of the vector with constructions
			while(it - count >= new_range_start)
			{
				_allocator.construct(&(*it), *(it - count));
				--it;
			}

			// translate the remaining values
			if (_size > pos_index + count)
			{
				for (size_type i = 0; i < _size - pos_index - count; ++i) {
						*it = *(it - count);
						--it;
					}
			}
				
			// populate new values
			while (new_range_start <= it)
			{
				if (new_range_start < end())
					*new_range_start = *first;
				else
					_allocator.construct(&(*new_range_start), *first);
				++first;
				++new_range_start;
			}
			
			_size += count;

			// iterator new_range_start = pos_after_resize;
			// it = end() + count - 1;
			// while ( it != new_range_start + count - 1 ) {
			// 	_allocator.construct(&(*it), *(it - count));
			// 	--it;
			// }
			
			// for (size_type i = 0; i < count; ++i) {
			// 	*new_range_start = *first;
			// 	++new_range_start;
			// 	++first;
			// }
			// _size += count;
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
			if (sizeof(T) * count > _allocator.max_size())
			{
				throw std::length_error("Maximum possible size is exceeded");
			}
			_array = _allocator.allocate(sizeof(T) * count);
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
			_size = 0;
			_capacity = 0;
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
				_array = _allocator.allocate(sizeof(T) * _capacity);
				for (size_type i = 0; i < _size; i++)
					_allocator.construct(&_array[i], other[i]);
			}
			return (*this);
		}

		/* 1 */
		void assign( size_type count, const T& value )
		{
			resize(count);

			_size = count;
			for (size_type i = 0; i < _size; ++i)
				_array[i] = value;
		}

		/* 2 */
		template< class InputIt >
		void assign( InputIt first, InputIt last,
			typename enable_if<!ft::is_integral< InputIt >::value, void* >::type* = NULL)
		{
			_assignHelper(first, last, typename ft::iterator_traits<InputIt>::iterator_category());
		}
		
		allocator_type get_allocator() const
		{
			return (_allocator);
		}

		/* ELEMENT ACCESS  */
		
		reference at( size_type pos )
		{
			if (!(pos < _size))
				throw std::out_of_range("Catch out_of_range exception!");
			return ((*this)[pos]);
		}

		const_reference at( size_type pos ) const
		{
			if (!(pos < size()))
				throw std::out_of_range("Catch out_of_range exception!");
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
			iterator it(_array + _size);
			return it;
		}
		
		const_iterator end() const
		{
			const_iterator it(_array + _size);
			return it;
		}
		
		reverse_iterator rbegin()
		{
			reverse_iterator it(end());
			return it;
			
		}
		
		const_reverse_iterator rbegin() const
		{
			const_reverse_iterator it(end());
			return it;
		}
		
		reverse_iterator rend()
		{
			reverse_iterator it(begin());
			return it;
		}
		
		const_reverse_iterator rend() const
		{
			const_reverse_iterator it(begin());
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
			
			size_type	initial_size = _size;
			T*	tmp_array;
			tmp_array = _allocator.allocate(sizeof(T) * new_cap);
			for (size_type i = 0; i < _size; i++)
				_allocator.construct(&tmp_array[i], _array[i]);
			
			_reset_array();
			
			_capacity = new_cap;
			_array = tmp_array;
			_size = initial_size;
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
			size_t pos_index = std::distance(begin(), pos);
			
			if (_capacity == 0)
				reserve(1);
			if (_size == _capacity)
				reserve(_capacity * 2);
			
			iterator it = begin();
			iterator pos_after_resize(begin() + pos_index);
			
			while ( it != pos_after_resize && it != end()) {
				++it;
			}

			if (it == end())
			{
				_allocator.construct(&(*it), value);
				++_size;
				
				return it;
			}
			
			iterator new_slot = it;
			it = end();
			_allocator.construct(&(*it), *(it - 1));
			--it;
			while ( it != new_slot ) {
				*it = *(it - 1);
				--it;
			}
			*it = value;
			++_size;
			return (new_slot);
		}

		/* 2 */
		void		insert( iterator pos, size_type count, const T& value )
		{
			size_t pos_index = std::distance(begin(), pos);
			
			if (count == 0)
				return ;
			if (_capacity == 0)
				reserve(count);
				
			size_type	target_capacity = _capacity;
			while (_size + count > target_capacity)
				target_capacity *= 2;
			reserve(target_capacity);
			
			iterator it = begin();
			iterator pos_after_resize(begin() + pos_index);
			
			while ( it != pos_after_resize && it != end()) {
				++it;
			}

			if (it == end())
			{
				for (size_type i = 0; i < count; ++i)
				{
					_allocator.construct(&(*it), value);
					++_size;
					++it;
				}				
				return ;
			}
			
			iterator new_range_start = pos_after_resize;
			it = end() + count - 1;
			// extend the end of the vector with constructions
			for (size_type i = 0; i < count; ++i)
			{
				_allocator.construct(&(*it), *(it - count));
				--it;
			}

			// translate the remaining values
			for (size_type i = 0; i < _size - pos_index - count; ++i) {
					*it = *(it - count);
					--it;
				}
				
			// populate new values
			for (size_type i = 0; i < count; ++i)
			{
				*new_range_start = value;
				++new_range_start;
			}
			
			_size += count;
		}

		/* 3 */
		template< class InputIt >
		void		insert(iterator pos, InputIt first, InputIt last,
			typename enable_if<!ft::is_integral< InputIt >::value, void* >::type* = NULL)
		{
			_insertHelper(pos, first, last, typename ft::iterator_traits<InputIt>::iterator_category());
		}
		
		iterator	erase( iterator pos )
		{
			iterator it = begin();
			iterator initial_end(end());
			
			while ( it != pos && it != end()) {
				++it;
			}
			if (it == end())
				return (pos);
			
			while ( it != initial_end - 1) {
				*it = *(it + 1);
				++it;
			}
			_allocator.destroy(&(*it));
			--_size;
			return (pos);
		}
		
		iterator	erase( iterator first, iterator last )
		{
			if (std::distance(first, last) <= 0)
				return last;
			
			difference_type	range = std::distance(first, last);
			for (difference_type i = 0; i < range; i++)
				erase(first);
			return first;
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
			--_size;
		}
		
		void		resize( size_type count, T value = T() )
		{
			if (_size > count) {
				size_type diff = _size - count;
				for (size_type i = 0; i < diff; ++i) {
					pop_back();
				}
			}
			else if (_size < count) {
				size_type diff = count - _size;
				for (size_type i = 0; i < diff; ++i) {
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
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
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
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
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