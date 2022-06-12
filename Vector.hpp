//
// Created by Дрогунова Анастасия Викторовна on 05.06.2022.
//

#ifndef CEREBUS_FT_CONTAINERS_VECTOR_H
#define CEREBUS_FT_CONTAINERS_VECTOR_H

#include <cstddef>

namespace ft {

    template<class T, class A> class vector {


    public:
        typedef A allocator_type;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::value_type value_type;
        typedef T0 iterator;
        typedef T1 const_iterator;
        typedef T2 size_type;
        typedef T3 difference_type;
        typedef reverse_iterator<const_iterator> const_reverse_iterator;
        typedef reverse_iterator<iterator> reverse_iterator;

    private:
        pointer array; //указатель на память
        size_type arrCapacity;
        size_type arrSize;
		allocator_type allocator;

    public:
        vector(): array(nullptr), arrCapacity(0), arrSize(0) {}

        explicit vector(const allocator_type& a1)  : array(NULL), arrSize(0), arrCapacity(0), allocator_type(a1) {}

        explicit vector(size_type n) : arrCapacity(n), arrSize(n), array(NULL) {
			array = allocator.allocate(n);
		}

        vector(size_type n, const T& x);
        vector(size_type n, const T& x, const A& a1);
        vector(const vector& x) : array(NULL), arrSize(0), arrCapacity(0), allocator_type(x.allocator_type) {
			insert(begin(), x.begin(), x.end());
		}

        template<class InIt>
            vector(InIt first, InIt last);
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
        void reserve(size_type n);

        //дальше страница 357
        //iterators
        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;
        reverse_iterator rend();
        const_reverse_iterator rend() const;

        //capacity
        void resize(size_type n);
        void resize(size_type n, T x);
        size_type size() const {
			return arrSize;
		}

		size_type capacity() const {
			return capacity;
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

        reference at(size_type pos);
        const_reference at(size_type pos) const;
        reference operator[](size_type pos);
        const_reference operator[](size_type pos);
        reference front();
        const_reference front() const;
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
