//
// Created by Дрогунова Анастасия Викторовна on 05.06.2022.
//

#ifndef CEREBUS_FT_CONTAINERS_VECTOR_H
#define CEREBUS_FT_CONTAINERS_VECTOR_H

#include <cstddef>
#include <memory>

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
        size_type arrCapacity;
        size_type arrSize;
		allocator_type allocator;

    public:
        vector(): array(NULL), arrCapacity(0), arrSize(0) {}

        explicit vector(const allocator_type& a1 = allocator_type())  : array(NULL), arrSize(0), arrCapacity(0), allocator_type(a1) {}

        explicit vector(size_type n) : arrCapacity((int)(n * 1.5)), arrSize(n), array(NULL) {
			array = allocator.allocate(arrCapacity);
		}

        explicit vector(size_type n, const T& x = T()): arrSize(n), arrCapacity((int)(n * 1.5)) {
			allocator = allocator_type();
			array = allocator.allocate(arrCapacity);
			for (int i = 0; i < n; ++i) {
				allocator.construct(&array[i], x);
			}
		}

        explicit vector(size_type n, const T& x = T(), const A& a1 = allocator_type()) : arrSize(n), arrCapacity(n), allocator(a1) {
			array = allocator.allocate(n);
			for (int i = 0; i < n; ++i) {
				allocator.construct(&array[i], x);
			}
		}

        vector(const vector& x) : array(NULL), arrSize(0), arrCapacity(0), allocator_type(x.allocator_type) {
			insert(begin(), x.begin(), x.end());
		}

        template<class InIt>
            vector(InIt first, InIt last, const allocator_type& alloc = allocator_type(),
				   typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0) : array(NULL), arrSize(0), arrCapacity(0), allocator_type(alloc)
		{
			allocator = alloc;
			insert(begin(), first, last);
		}
        template<class InIt>
                vector(InIt first, InIt last, const A& al);

        ~vector() {
			clear();
			if (arrCapacity != 0)
				allocator.deallocate(array, arrCapacity);
		}

        template<class <class InIt>
                vector(InIt first, InIt last);

        template<class <class InIt>
                vector(InIt first, InIt last, const A& a1);
        void reserve (size_type n)
        {
            if (n > arrCapacity)
            {
                size_type i = 0;
                pointer new_array = allocator.allocate(n);
                try
                {
                    for (i = 0; i < arrSize; ++i)
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
                for (size_type j = 0; j < arrSize; ++j)
                {
                    allocator.destroy(&array[j]);
                }
                allocator.deallocate(array, arrCapacity);
                array = new_array;
                arrCapacity = n;
            }
        }

        //дальше страница 357
        //iterators
        iterator begin() {
			return iterator(array);
		}
        const_iterator begin() const {
			return const_iterator (array);
		}
        iterator end() {
			return iterator(array + arrSize);
		}
        const_iterator end() const {
			return const_iterator(array + arrSize);
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

        void resize (size_type n, value_type val = value_type())
        {
            if (n > arrSize)
            {
                if (n > arrCapacity)
                    reserve(n);
            }
            for (; arrSize < arrCapacity; arrSize++)
                allocator.construct(&array[arrSize], val);
            for (size_type i = n; i < arrCapacity; ++i)
                allocator.destroy(&array[i]);
            this->_size = n;
        }
        size_type size() const {
			return arrSize;
		}

		size_type capacity() const {
			return arrCapacity;
		}

        size_type max_size() const {
			return allocator.max_size();
		}

        bool empty() const {
			return (arrSize == 0);
		}

        A get_allocator() const {
			return allocator;
		}

        reference at(size_type pos) {
            if (pos > arrSize)
                throw std::out_of_range("vector::at()");
            return (reference(array[pos]));
        }
        const_reference at(size_type pos) const {
            if (pos > arrSize)
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
        reference back();
        const_reference back() const;

        void push_back(const T& x);
        void pop_back();

        template<class InIt>
                void assign(InIt first, InIt last);
        void assign(size_type n, const T& x);
        iterator insert(iterator it, const T& x);
        void insert(iterator it, size_type n, const T& x);
        template<class InIt>
                void insert(iterator it, InIt first, InIt last);
        iterator erase(iterator it);
        iterator erase(iterator first, iterator last);

        void clear() {
            erase(begin(), end());
        }
        void swap(vector& x);


    };

    template<class T, class A>
        bool operator==(const vector<T, А>& lhs , const vector<T, А>& rhs ){
            return (lhs.size() == rhs.size() && equal(lhs.begin(), lhs.end(), rhs.begin()));
        }
    template<class T , class A>
        bool operator!=(const vector<T, А>& lhs , const vector<T, А>& rhs ) {
            return ! (lhs == rhs);
        }
    template<class T , class A>
        bool operator<(const vector<T, А>& lhs , const vector<T, А>& rhs ) {
            return(lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()))
        }
    template<class T , class A>
        bool operator>(const vector<T, А>& lhs , const vector<T, А>& rhs ) {
            return(rhs < lhs);
        }
    template<class T , class A>
        bool operator<=(const vector<T, А>& lhs , const vector<T, А>& rhs ) {
            return !(rhs < lhs);
        }
    template<class T , class A>
        bool operator>=(const vector<T, А>& lhs , const vector<T, А>& rhs ) {
            return !(lhs < rhs);
        }

}

#endif //CEREBUS_FT_CONTAINERS_VECTOR_H
