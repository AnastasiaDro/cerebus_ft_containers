//
// Created by Дрогунова Анастасия Викторовна on 05.06.2022.
//

#ifndef CEREBUS_FT_CONTAINERS_VECTOR_H
#define CEREBUS_FT_CONTAINERS_VECTOR_H

namespace ft {

    template<class T, class A> class vector {
    public:
        typedef A allocator_type;
        typedef typename A::pointer pointer;
        typedef typename A::const_pointer const_pointer;
        typedef typename A::reference reference;
        typedef typename A::const_reference const_reference;
        typedef typename A::value_type value_type;
        typedef T0 iterator;
        typedef T1 const_iterator;
        typedef T2 size_type;
        typedef T3 difference_type;
        typedef reverse_iterator<const_iterator> const_reverse_iterator;
        typedef reverse_iterator<iterator> reverse_iterator;
        vector();
        explicit vector(const A& a1);
        explicit vector(size_type n);
        vector(size_type n, const T& x);
        vector(size_type n, const T& x, const A& a1);
        vector(const vectors x);
        ~vector();

        template<class <class InIt>
                vector(InIt first, InIt last);

        template<class <class InIt>
                vector(InIt first, InIt last, const A& a1);
        vois reserve(size_type n);
        size_type capacity() const;

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
        size_type size() const;
        size_type max_size() const;
        bool empty() const;

        A get_allocator() const;
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
        iterator insert(iterator it, const T& x);
        void insert(iterator it, size_type n, const T& x);
        template<class InIt>
                void insert(iterator it, InIt first, InIt last);
        iterator erase(iterator it);
        iterator erase(iterator first, iterator last);
        void clear();
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
