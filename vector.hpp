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

			void pop_back() {
				_size--;
				_allocator.destroy(_array + _size);
			}

            void push_back (const value_type& x) {
                insert(end(), x);
            }

			void insert (iterator pos, size_type n, const value_type& x) {
				if (_size + n >= _capacity) {
					_capacity = _capacity * 2 + (_capacity == 0);
					if (_capacity < _size + n)
						_capacity = _size + n;
					pointer new_arr = _allocator.allocate(_capacity);
					int i = 0;
					for (iterator it = begin(); it != pos; it++, i++)
						_allocator.construct(new_arr + i, *it);
					for (size_type j = 0; j < n; j++, i++)
						_allocator.construct(new_arr + i, x);
					for (iterator it = pos; it != end(); it++, i++)
						_allocator.construct(new_arr + i, *it);
					for (size_type i = 0; i < _size; i++)
						_allocator.destroy(&this->_array[i]);
					if (_array)
						_allocator.deallocate(_array, _capacity);
					_size += n;
					_array = new_arr;
				} else {
					iterator it = end();
					for (; it != pos; it--) {
						_allocator.destroy(&(*it) + n);
						_allocator.construct((&(*it) + n), *it);
					}
					_allocator.destroy(&(*it) + n);
					_allocator.construct((&(*it) + n), *it);
					for (size_type j = 0; j != n; j++, it++) {
						_allocator.destroy(&(*it));
						_allocator.construct(&(*it), x);
					}
					_size += n;
				}
			}

            iterator insert(iterator pos, const value_type& val) {
                size_type position = &(*pos) - _array;
                insert(pos, (size_type)1, val);
                return (begin() + position);
            }

			template <class InIt>
			void insert(iterator pos, InIt f, InIt l, typename ft::enable_if<!ft::is_integral<InIt>::value >::type* = 0) {
				size_type n = 0;
				size_type new_cap = _capacity;
				size_type start = pos - begin();
				for (InIt it = f; it != l; it++)
					n++;
				if (n + _size >= _capacity) {
					new_cap = new_cap * 2 + (new_cap == 0);
					if (new_cap < _size + n)
						new_cap = _size + n;
					pointer new_arr = _allocator.allocate(new_cap);
					try {
						std::uninitialized_copy(begin(), pos, new_arr);
						std::uninitialized_copy(f, l, new_arr + start);
						std::uninitialized_copy(pos, end(), new_arr + start + n);
					}
					catch(...) {
						_allocator.deallocate(new_arr,new_cap);
						throw;
					}
					for (size_type i = 0; i < _size; ++i)
						_allocator.destroy(&this->_array[i]);
					if (_array)
						_allocator.deallocate(_array, _capacity);
					_size += n;
					_array = new_arr;
					_capacity = new_cap;
				} else {
					iterator it = end();
					for (; it != pos; it--) {
						_allocator.destroy(&(*it) + n);
						_allocator.construct((&(*it) + n), *it);
					}
					_allocator.destroy(&(*it) + n);
					_allocator.construct((&(*it) + n), *it);
					InIt jt = f;
					for (size_type j = 0; j != n; j++, it++, jt++) {
						_allocator.destroy(&(*it));
						_allocator.construct(&(*it), *jt);
					}
					_size += n;
				}
			}
            
			iterator erase (iterator f, iterator l) {
                int sum = 0;
				pointer ptr = &(*f);
				for (iterator it = f; it != l; it++) {
					_allocator.destroy(&(*it));
					sum++;
				}
				_size -= sum;
				for (size_type i = 0; i < _size; i++)
					this->_allocator.construct(&(*f) + i, *(&(*l) + i));
				return (iterator(ptr));
			}

            iterator erase (iterator pos) {
                return (erase(pos, pos + 1));
            }

			void swap (vector& v) {
                size_type tmp_capacity = v._capacity;
                allocator_type tmp_allocator = v._allocator;
				pointer tmp_arr = v._array;
				size_type tmp_size = v._size;
                
                v._capacity = _capacity;
                v._allocator = _allocator;
				v._array = _array;
				v._size = _size;

                _capacity = tmp_capacity;
                _allocator = tmp_allocator;
				_array = tmp_arr;
				_size = tmp_size;
			}


            allocator_type get_allocator() const {
                return (_allocator);
            }

            value_type *data() {
                return (_array);
            }

            const value_type *data() const {
                return (_array);
            }

            void clear() {
                for (size_type i = 0; i < this->_size; ++i)
                    this->_allocator.destroy(&this->_array[i]);
                this->_size = 0;
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