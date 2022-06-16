#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>
#include "vector_iterator.hpp"
#include "reverse_iterator.hpp"
#include "ft_is_integral.hpp"

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef ft::vector_iterator<false, value_type>		iterator;
			typedef ft::vector_iterator<true, value_type>		const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
			typedef ptrdiff_t									difference_type;
			typedef size_t										size_type;

			explicit vector (const allocator_type& alloc = allocator_type()) : _array(NULL), _size(0), _capacity(0), _allocator(alloc) {}


			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) :
			_size(n), _capacity(n), _allocator(alloc)
			{
					_array = _allocator.allocate(_capacity);
					for (size_type i = 0; i < n; ++i)
						_allocator.construct(&_array[i], val);
			}

			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0) : _array(NULL), _size(0), _capacity(0), _allocator(alloc)
			{
				_allocator = alloc;
				insert(begin(), first, last);
			}

			vector (const vector& x) : _array(NULL), _size(0), _capacity(0), _allocator(x._allocator)
			{
				insert(begin() ,x.begin(), x.end());
			}

			~vector()
			{
				clear();
				if (this->_capacity != 0)
					this->_allocator.deallocate(this->_array, this->_capacity);
			}

			vector& operator= (const vector& x)
			{
				if (this != &x)
				{
					for (size_type i = 0; i < _size; ++i)
						_allocator.destroy(_array + i);
					if (_capacity < x._capacity)
					{
						_allocator.deallocate(_array, _capacity);
						this->_capacity = x._capacity;
						this->_array = _allocator.allocate(_capacity);
					}
					for (size_type i = 0; i < x._size; ++i)
						_allocator.construct(&_array[i], x._array[i]);
					this->_size = x._size;
				}
				return (*this);
			}

			iterator begin()
			{
				return iterator(this->_array);
			}

			const_iterator begin() const
			{
				return const_iterator(this->_array);
			}

			iterator end()
			{
				return iterator(this->_array + _size);
			}
			const_iterator end() const
			{
				return const_iterator(this->_array + _size);
			}

			reverse_iterator rbegin()
			{
				return (reverse_iterator(end()));
			}

			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(end()));
			}

			reverse_iterator rend()
			{
				return (reverse_iterator(begin()));
			}

			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(begin()));
			}

			size_type size() const
			{
				return (this->_size);
			}

			size_type max_size() const
			{
				return (this->_allocator.max_size());
			}

			void resize (size_type n, value_type val = value_type())
			{
				if (n > _size)
				{
					if (n > _capacity)
						reserve(n);
				}
				for (; _size < _capacity; ++_size)
					_allocator.construct(&_array[_size], val);
				for (size_type i = n; i < _capacity; ++i)
					_allocator.destroy(&_array[i]);
				this->_size = n;
			}

			size_type capacity() const
			{
				return (this->_capacity);
			}

			bool empty() const
			{
				return (this->_size == 0);
			}

			void reserve (size_type n)
			{
				if (n > _capacity)
				{
					size_type i = 0;
					pointer new_array = _allocator.allocate(n);
					try
					{
						for (i = 0; i < _size; ++i)
						{
							_allocator.construct(&new_array[i], _array[i]);
						}
					}
					catch(const std::exception& e)
					{
						for (size_type j = 0; j < i; ++j)
							_allocator.destroy(&new_array[i]);
						_allocator.deallocate(new_array, n);
						throw;
					}
					for (size_type j = 0; j < _size; ++j)
					{
						_allocator.destroy(&_array[j]);
					}
					_allocator.deallocate(_array, _capacity);
					_array = new_array;
					_capacity = n;
				}
			}

			reference operator[] (size_type n)
			{
				return (this->_array[n]);
			}

			const_reference operator[] (size_type n) const
			{
				return (this->_array[n]);
			}

			reference at (size_type n)
			{
				if (n > this->_size)
					throw std::out_of_range("vector::at()");
				return (reference(this->_array[n]));
			}

			const_reference at (size_type n) const
			{
				if (n > this->_size)
					throw std::out_of_range("vector::at()");
				return (const_reference(this->_array[n]));
			}

			reference front()
			{
				return *(this->_array);
			}

			const_reference front() const
			{
				return *(this->_array);
			}

			reference back()
			{
				return *(this->_array + (this->_size - 1));
			}

			const_reference back() const
			{
				return *(this->_array + (this->_size - 1));
			}

			template <class InputIterator>
			void assign (InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value>::type* = 0)
			{
				size_type new_size = 0;
				for (size_type i = 0; i < this->_size; ++i)
					this->_allocator.destroy(&this->_array[i]);
				for (InputIterator it = first; it != last; ++it)
					new_size += 1;
				if (new_size > max_size())
					reserve(new_size);
				if (this->_capacity < new_size)
				{
					this->_allocator.deallocate(this->_array, this->_capacity);
					this->_capacity = new_size;
					this->_array = this->_allocator.allocate(this->_capacity);
				}
				int i = 0;
				for (InputIterator it = first; it != last; ++it, ++i)
					this->_allocator.construct(&this->_array[i], *it);
				this->_size = new_size;
			}

			void assign (size_type n, const value_type& val)
			{
				for (size_type i = 0; i < this->_size; ++i)
						this->_allocator.destroy(&this->_array[i]);
				if (n > this->_capacity)
				{
					this->_allocator.deallocate(this->_array, this->_capacity);
					this->_capacity = n;
					this->_array = this->_allocator.allocate(n);
				}
				for (size_type i = 0; i < n; ++i)
					this->_allocator.construct(&this->_array[i], val);
				this->_size = n;
			}

			void push_back (const value_type& val)
			{
				insert(end(), val);
			}

			void pop_back()
			{
				--_size;
				_allocator.destroy(_array + _size);
			}

			iterator insert (iterator position, const value_type& val)
			{
				size_type pos = &(*position) - _array;
				insert(position, (size_type)1, val);
				return (begin() + pos);
			}

			void insert (iterator position, size_type n, const value_type& val)
			{
				if (this->_size + n >= this->_capacity)
				{
					this->_capacity = this->_capacity * 2 + (this->_capacity == 0);
					if (this->_capacity < this->_size + n)
						this->_capacity = this->_size + n;
					pointer new_arr = this->_allocator.allocate(this->_capacity);
					int i = 0;
					for (iterator it = begin(); it != position; ++it, ++i)
						this->_allocator.construct(new_arr + i, *it);
					for (size_type j = 0; j < n; ++j, ++i)
						this->_allocator.construct(new_arr + i, val);
					for (iterator it = position; it != end(); ++it, ++i)
						this->_allocator.construct(new_arr + i, *it);
					for (size_type i = 0; i < this->_size; ++i)
						this->_allocator.destroy(&this->_array[i]);
					if (this->_array)
						this->_allocator.deallocate(this->_array, this->_capacity);
					this->_size += n;
					this->_array = new_arr;
				}
				else
				{
					iterator it = end();
					for (; it != position; --it)
					{
						this->_allocator.destroy(&(*it) + n);
						this->_allocator.construct((&(*it) + n), *it);
					}
					this->_allocator.destroy(&(*it) + n);
					this->_allocator.construct((&(*it) + n), *it);
					for (size_type j = 0; j != n; ++j, ++it)
					{
						this->_allocator.destroy(&(*it));
						this->_allocator.construct(&(*it), val);
					}
					this->_size += n;
				}
			}

			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
			{
				size_type n = 0;
				size_type new_cap = this->_capacity;
				size_type start = position - this->begin();
				for (InputIterator it = first; it != last; ++it)
					n++;
				if (this->_size + n >= this->_capacity)
				{
					new_cap = new_cap * 2 + (new_cap == 0);
					if (new_cap < this->_size + n)
						new_cap = this->_size + n;
					pointer new_arr = this->_allocator.allocate(new_cap);
					try
					{

						std::uninitialized_copy(begin(), position, new_arr);
						std::uninitialized_copy(first, last, new_arr + start);
						std::uninitialized_copy(position, end(), new_arr + start + n);
					}
					catch(...)
					{
						this->_allocator.deallocate(new_arr,new_cap);
						throw;
					}

					for (size_type i = 0; i < this->_size; ++i)
						this->_allocator.destroy(&this->_array[i]);
					if (this->_array)
						this->_allocator.deallocate(this->_array, this->_capacity);
					this->_size += n;
					this->_array = new_arr;
					this->_capacity = new_cap;
				}
				else
				{
					iterator it = end();
					for (; it != position; --it)
					{
						this->_allocator.destroy(&(*it) + n);
						this->_allocator.construct((&(*it) + n), *it);
					}
					this->_allocator.destroy(&(*it) + n);
					this->_allocator.construct((&(*it) + n), *it);
					InputIterator jt = first;
					for (size_type j = 0; j != n; ++j, ++it, ++jt)
					{
						this->_allocator.destroy(&(*it));
						this->_allocator.construct(&(*it), *jt);
					}
					this->_size += n;
				}
			}

			iterator erase (iterator position)
			{
				return (erase(position, position + 1));
			}

			iterator erase (iterator first, iterator last)
			{
				pointer p = &(*first);
				int sum = 0;
				for (iterator it = first; it != last; ++it)
				{
					this->_allocator.destroy(&(*it));
					sum++;
				}
				this->_size -= sum;
				for (size_type i = 0; i < this->_size; ++i)
					this->_allocator.construct(&(*first) + i, *(&(*last) + i));
				return (iterator(p));
			}

			void swap (vector& x)
			{
				pointer tmp_array = x._array;
				size_type tmp_size = x._size;
				size_type tmp_capacity = x._capacity;
				allocator_type tmp_allocator = x._allocator;

				x._array = this->_array;
				x._size = this->_size;
				x._capacity = this->_capacity;
				x._allocator = this->_allocator;

				this->_array = tmp_array;
				this->_size = tmp_size;
				this->_capacity = tmp_capacity;
				this->_allocator = tmp_allocator;

				// ft::swap(this->_array, x._array);
				// ft::swap(this->_size, x._size);
				// ft::swap(this->_capacity, x._capacity);
				// ft::swap(this->_allocator, x._allocator);
			}

			void clear()
			{
				for (size_type i = 0; i < this->_size; ++i)
					this->_allocator.destroy(&this->_array[i]);
				this->_size = 0;
			}

			value_type* data()
			{
				return (this->_array);
			}

			const value_type* data() const
			{
				return (this->_array);
			}

			allocator_type get_allocator() const
			{
				return (this->_allocator);
			}

		private:
			pointer _array;
			size_type _size;
			size_type _capacity;
			allocator_type _allocator;

	};

	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		if (lhs.size() == rhs.size()) {
			typename ft::vector<T>::const_iterator it1 = lhs.begin();
			typename ft::vector<T>::const_iterator it2 = rhs.begin();
			for (; it1 != lhs.end(); it1++, it2++) {
				if (*it1 != *it2 || it2 == rhs.end())
					return (false);
			}
			return (true);
		} else
			return (false);
	}

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (!(lhs > rhs));
	}

	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (!(lhs < rhs));
	}

	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {
		x.swap(y);
	}
}

#endif