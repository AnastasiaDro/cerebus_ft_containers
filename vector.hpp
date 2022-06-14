//
// Created by Дрогунова Анастасия Викторовна on 05.06.2022.
//

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <memory>
#include "vector_iterator.hpp"
#include "reverse_iterator.hpp"
#include "ft_is_integral.hpp"

namespace ft {

    template < class T, class A = std::allocator<T> >
    class vector {

    public:
        typedef A allocator_type;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::value_type value_type;
		typedef ft::vector_iterator<false, value_type>		iterator;
		typedef ft::vector_iterator<true, value_type>		const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
		typedef ptrdiff_t									difference_type;
		typedef size_t										size_type;

	private:
        pointer array; //указатель на память
        size_type arr_capacity;
        size_type arr_size;
		allocator_type allocator;

    public:
        template <class InputIterator>
        vector (InputIterator first, InputIterator last, const allocator_type& a = allocator_type(),
                typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0) : array(NULL), arr_size(0), arr_capacity(0), allocator(a){
            allocator = a;
            insert(begin(), first, last);
        }

        vector(): array(NULL), arr_capacity(0), arr_size(0) {}

        explicit vector(const allocator_type& a1 = allocator_type())  : array(NULL), arr_size(0), arr_capacity(0), allocator_type(a1) {}

        explicit vector(size_type n) : arr_capacity((int)(n * 1.5)), arr_size(n), array(NULL) {
			array = allocator.allocate(arr_capacity);
		}

        explicit vector(size_type n, const T& x = T()): arr_size(n), arr_capacity((int)(n * 1.5)) {
			allocator = allocator_type();
			array = allocator.allocate(arr_capacity);
			for (int i = 0; i < n; ++i) {
				allocator.construct(&array[i], x);
			}
		}

        explicit vector(size_type n, const T& x = T(), const A& a1 = allocator_type()) : arr_size(n), arr_capacity(n), allocator(a1) {
			array = allocator.allocate(n);
			for (int i = 0; i < n; ++i) {
				allocator.construct(&array[i], x);
			}
		}

        vector(const vector& x) : array(NULL), arr_size(0), arr_capacity(0), allocator_type(x.allocator_type) {
			insert(begin(), x.begin(), x.end());
		}


        ~vector() {
			clear();
			if (arr_capacity != 0)
				allocator.deallocate(array, arr_capacity);
		}


        void reserve (size_type n)
        {
            if (n > arr_capacity)
            {
                size_type i = 0;
                pointer new_array = allocator.allocate(n);
                try
                {
                    for (i = 0; i < arr_size; ++i)
                    {
                        allocator.construct(&new_array[i], array[i]);
                    }
                }
                catch(const std::exception& e)
                {
                    for (size_type j = 0; j < i; ++j)
                        allocator.destroy(&new_array[i]);
                    allocator.deallocate(new_array, n);
                    throw;
                }
                for (size_type j = 0; j < arr_size; ++j)
                {
                    allocator.destroy(&array[j]);
                }
                allocator.deallocate(array, arr_capacity);
                array = new_array;
                arr_capacity = n;
            }
        }

        //iterators
        iterator begin() {
			return iterator(array);
		}
        const_iterator begin() const {
			return const_iterator (array);
		}
        iterator end() {
			return iterator(array + arr_size);
		}
        const_iterator end() const {
			return const_iterator(array + arr_size);
		}
		const_reverse_iterator rbegin() const {
			return (const_reverse_iterator(end()));
		}

		reverse_iterator rend() {
			return (reverse_iterator(begin()));
		}

		const_reverse_iterator rend() const {
			return (const_reverse_iterator(begin()));
		}

        //capacity

        void resize(size_type n, value_type val = value_type())
        {
            if (n > arr_size)
            {
                if (n > arr_capacity)
                    reserve(n);
            }
            for (; arr_size < arr_capacity; arr_size++)
                allocator.construct(&array[arr_size], val);
            for (size_type i = n; i < arr_capacity; ++i)
                allocator.destroy(&array[i]);
            this->_size = n;
        }
        size_type size() const {
			return arr_size;
		}

		size_type capacity() const {
			return arr_capacity;
		}

        size_type max_size() const {
			return allocator.max_size();
		}

        bool empty() const {
			return (arr_size == 0);
		}

        A get_allocator() const {
			return allocator;
		}

        reference at(size_type pos) {
            if (pos > arr_size)
                throw std::out_of_range("vector::at()");
            return (reference(array[pos]));
        }

        const_reference at(size_type pos) const {
            if (pos > arr_size)
                throw std::out_of_range("vector::at()");
            return (reference(array[pos]));
        }

        reference operator[](size_type pos) {
            return array[pos];
        }
        const_reference operator[](size_type pos) const {
            return array[pos];
        }

        reference front() {
            return *array;
        }
        const_reference front() const {
            return *array;
        }
        reference back() {
            return *(array + arr_size - 1);
        }
        const_reference back() const {
            return *(array + arr_size - 1);
        }

        void push_back(const T& x) {
            insert(end(), x);
        }
        void pop_back() {
            allocator.destroy(array + arr_size - 1);
        }

        template <class InputIterator>
        void assign (InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value>::type* = 0)
        {
            size_type new_size = 0;
            for (size_type i = 0; i < arr_size; i++)
                allocator.destroy(&this->array[i]);
            for (InputIterator it = first; it != last; it++)
                new_size += 1;
            if (new_size > max_size())
                reserve(new_size);
            if (arr_capacity < new_size)
            {
                allocator.deallocate(array, arr_capacity);
                arr_capacity = new_size;
                array = allocator.allocate(arr_capacity);
            }
            int i = 0;
            for (InputIterator it = first; it != last; it++, i++)
                this->allocator.construct(&this->array[i], *it);
            arr_size = new_size;
        }

        void assign(size_type n, const T& x) {
            for (size_type i = 0; i < arr_size; i++)
                allocator.destroy(&this->array[i]);
            if (n > arr_capacity)
            {
                allocator.deallocate(array, arr_capacity);
                arr_capacity = n;
                array = allocator.allocate(n);
            }
            for (size_type i = 0; i < n; ++i)
                allocator.construct(&this->array[i], x);
            arr_size = n;
        }

        iterator insert(iterator it_position, const T& x) {
            size_type pos = &(*it_position) - array;
            insert(it_position, (size_type)1, x);
            return (begin() + pos);
        }
        void insert(iterator it_position, size_type n, const T& x) {
            if (arr_size + n >= arr_capacity)
            {
                arr_capacity = arr_capacity * 2 + (arr_capacity == 0);
                if (arr_capacity < arr_size + n)
                    arr_capacity = arr_size + n;
                pointer new_arr = allocator.allocate(arr_capacity);
                int i = 0;
                for (iterator it = begin(); it != it_position; ++it, ++i)
                    allocator.construct(new_arr + i, *it);
                for (size_type j = 0; j < n; ++j, ++i)
                    allocator.construct(new_arr + i, x);
                for (iterator it = it_position; it != end(); ++it, ++i)
                    allocator.construct(new_arr + i, *it);
                for (size_type i = 0; i < arr_size; ++i)
                    allocator.destroy(&this->array[i]);
                if (array)
                    allocator.deallocate(array, arr_capacity);
                this->arr_size += n;
                this->array = new_arr;
            } else {
                iterator it = end();
                for (; it !=  it_position; --it) {
                    allocator.destroy(&(*it) + n);
                    allocator.construct((&(*it) + n), *it);
                }
                allocator.destroy(&(*it) + n);
                allocator.construct((&(*it) + n), *it);
                for (size_type j = 0; j != n; ++j, ++it) {
                    this->_allocator.destroy(&(*it));
                    this->_allocator.construct(&(*it), x);
                }
                arr_size += n;
            }
        }
        template <class InputIterator>
        void insert (iterator it_position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
        {
            size_type n = 0;
            size_type new_cap = arr_capacity;
            size_type start = it_position - this->begin();
            for (InputIterator it = first; it != last; it++)
                n++;
            if (arr_size + n >= arr_capacity)
            {
                new_cap = new_cap * 2 + (new_cap == 0);
                if (new_cap < arr_size + n)
                    new_cap = arr_size + n;
                pointer new_arr = allocator.allocate(new_cap);
                try {
                    std::uninitialized_copy(begin(), it_position, new_arr);
                    std::uninitialized_copy(first, last, new_arr + start);
                    std::uninitialized_copy(it_position, end(), new_arr + start + n);
                }
                catch(...) {
                    allocator.deallocate(new_arr,new_cap);
                    throw;
                }

                for (size_type i = 0; i < this->_size; i++)
                    allocator.destroy(&this->_array[i]);
                if (array)
                    allocator.deallocate(array, arr_capacity);
                arr_size += n;
                array = new_arr;
                arr_capacity = new_cap;
            } else {
                iterator it = end();
                for (; it != it_position; it--) {
                    allocator.destroy(&(*it) + n);
                    allocator.construct((&(*it) + n), *it);
                }
                allocator.destroy(&(*it) + n);
                allocator.construct((&(*it) + n), *it);
                InputIterator jt = first;
                for (size_type j = 0; j != n; ++j, ++it, ++jt) {
                    allocator.destroy(&(*it));
                    allocator.construct(&(*it), *jt);
                }
                arr_size += n;
            }
        }

        iterator erase(iterator it_position) {
            return (erase(it_position, it_position + 1));
        }

        iterator erase(iterator first, iterator last) {
            pointer p = &(*first);
            int sum = 0;
            for (iterator it = first; it != last; ++it) {
                this->allocator.destroy(&(*it));
                sum++;
            }
            arr_size -= sum;
            for (size_type i = 0; i < arr_size; i++)
                allocator.construct(&(*first) + i, *(&(*last) + i));
            return (iterator(p));
        }

        void clear() {
            erase(begin(), end());
        }

        void swap(vector& x) {
            pointer tmp_array = x.array;
            size_type tmp_size = x.arr_size;
            size_type tmp_capacity = x.arr_capacity;
            allocator_type tmp_allocator = x.allocator;

            x.array = array;
            x.arr_size = arr_size;
            x.arr_capacity = arr_capacity;
            x.allocator = allocator;

            array = tmp_array;
            arr_size = tmp_size;
            arr_capacity = tmp_capacity;
            allocator = tmp_allocator;
        }
    };

    template<class T, class A>
    bool operator==(const vector<T, A> &lhs, const vector<T, A> &rhs) {
        return (lhs.size() == rhs.size() && equal(lhs.begin(), lhs.end(), rhs.begin()));
    }

    template<class T, class A>
    bool operator!=(const vector<T, A> &lhs, const vector<T, A> &rhs) {
        return !(lhs == rhs);
    }

    template<class T, class A>
    bool operator<(const vector<T, A> &lhs, const vector<T, A> &rhs) {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }

    template<class T, class A>
    bool operator>(const vector<T, A> &lhs, const vector<T, A> &rhs) {
        return (rhs < lhs);
    }

    template<class T, class A>
    bool operator<=(const vector<T, A> &lhs, const vector<T, A> &rhs) {
        return !(rhs < lhs);
    }

    template<class T, class A>
    bool operator>=(const vector<T, A> &lhs, const vector<T, A> &rhs) {
        return !(lhs < rhs);
    }

    template <class T, class A>
    void swap (vector<T, A>& x, vector<T, A>& y) {
        x.swap(y);
    }
}

#endif //CEREBUS_FT_CONTAINERS_VECTOR_H
