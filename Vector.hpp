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

        template<class <class InIt>
                vector(InIt first, InIt last);

        template<class <class InIt>
                vector(InIt first, InIt last, const A& a1);
        vois reserve(size_type n);
        size_type capacity() const;

        //дальше страница 357




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
