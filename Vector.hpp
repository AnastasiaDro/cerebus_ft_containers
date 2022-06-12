//
// Created by Дрогунова Анастасия Викторовна on 05.06.2022.
//

#ifndef CEREBUS_FT_CONTAINERS_VECTOR_H
#define CEREBUS_FT_CONTAINERS_VECTOR_H

namespace ft {

    template<class T, class A> class vector {


    public:
        typedef A allocator;
        typedef typename allocator::pointer pointer;
        typedef typename allocator::const_pointer const_pointer;
        typedef typename allocator::reference reference;
        typedef typename allocator::const_reference const_reference;
        typedef typename allocator::value_type value_type;
        typedef T0 iterator;
        typedef T1 const_iterator;
        typedef T2 size_type;
        typedef T3 difference_type;
        typedef reverse_iterator<const_iterator> const_reverse_iterator;
        typedef reverse_iterator<iterator> reverse_iterator;

    private:
        pointer array; //указатель на память
        size_type capacity;
        size_type size;

    public:
        vector(): container(nullptr), capacity(0), size(0) {}

        //explicit vector(const A& a1);
        explicit vector(const allocator& a1 = allocator_type) :  {

        }
        explicit vector(size_type n) {
			allocator.alocate(n)
		}
        vector(size_type n, const T& x);
        vector(size_type n, const T& x, const A& a1);
        vector(const vectors x);

        template<class InIt>
            vector(InIt first, InIt last);
        template<class InIt>
                vector(InIt first, InIt last, const A& al);

        ~vector() {
			clear();
			if (capacity != 0)
				allocator.deallocate(array, capacity);
		}

        template<class <class InIt>
                vector(InIt first, InIt last);

        template<class <class InIt>
                vector(InIt first, InIt last, const A& a1);
        void reserve(size_type n);
        size_type capacity() const {
			return capacity;
		}

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
			return size;
		}
        size_type max_size() const {
			return allocator.max_size();
		}

        bool empty() const {
			return (size == 0);
		}

        A get_allocator() const {
			return allocator_type;
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
        void swap(vectors x);


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
