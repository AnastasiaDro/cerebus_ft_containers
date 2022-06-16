#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

# include <iterator>
# include "utils.hpp"
# include "ft_is_integral.hpp"

namespace ft {
    template<bool bo, typename T>
    class vector_iterator {
    public:
        typedef typename ft::conditional<bo, const T *, T *>::type pointer;
        typedef typename ft::conditional<bo, const T &, T &>::type reference;
        typedef typename std::iterator<std::random_access_iterator_tag, T>::iterator_category iterator_category;
        typedef typename std::iterator<std::random_access_iterator_tag, T>::value_type value_type;
        typedef typename std::iterator<std::random_access_iterator_tag, T>::difference_type difference_type;

        vector_iterator();
        vector_iterator(const vector_iterator &it);
        ~vector_iterator();

        vector_iterator<bo, T> &operator=(const vector_iterator &it);

        reference operator*() const;
        pointer operator->() const;

        vector_iterator<bo, T> &operator+=(difference_type n);
        vector_iterator<bo, T> &operator++();
        vector_iterator<bo, T> operator++(int);
        vector_iterator<bo, T> operator+(difference_type n) const;

        vector_iterator<bo, T> &operator-=(difference_type n);
        vector_iterator<bo, T> &operator--();
        vector_iterator<bo, T> operator--(int);
        vector_iterator<bo, T> operator-(difference_type n) const;

        template<bool B1, bool B2, typename U>
        friend bool operator<(const vector_iterator<B1, U> &lhs, const vector_iterator<B2, U> &rhs) {
            return lhs.ptr < rhs.ptr;
        }

        template<bool B1, bool B2, typename U>
        friend bool operator<=(const vector_iterator<B1, U> &lhs, const vector_iterator<B2, U> &rhs) {
            return lhs.ptr <= rhs.ptr;
        }

        template<bool B1, bool B2, typename U>
        friend bool operator>(const vector_iterator<B1, U> &lhs, const vector_iterator<B2, U> &rhs) {
            return lhs.ptr > rhs.ptr;
        }

        template<bool B1, bool B2, typename U>
        friend bool operator>=(const vector_iterator<B1, U> &lhs, const vector_iterator<B2, U> &rhs) {
            return lhs.ptr >= rhs.ptr;
        }

        template<bool B1, bool B2, typename U>
        friend bool operator==(const vector_iterator<B1, U> &lhs, const vector_iterator<B2, U> &rhs) {
            return lhs.ptr == rhs.ptr;
        }

        template<bool B1, bool B2, typename U>
        friend difference_type operator-(const vector_iterator<B1, U> &it1, const vector_iterator<B2, U> &it2) {
            difference_type n;
            n = it1.ptr - it2.ptr;
            return n;
        }

        template<bool B1, bool B2, typename U>
        friend bool operator!=(const vector_iterator<B1, U> &lhs, const vector_iterator<B2, U> &rhs) {
            return lhs.ptr != rhs.ptr;
        }

        reference operator[](difference_type n);

        explicit vector_iterator(pointer p);

        operator vector_iterator<true, value_type>() const {
            return vector_iterator<true, value_type>(ptr);
        }

    private:
        pointer ptr;
    };

    template<bool Bo, typename T>
    vector_iterator<Bo, T>::vector_iterator() : ptr(NULL) { }

    template<bool Bo, typename T>
    vector_iterator<Bo, T>::vector_iterator(const vector_iterator &it) : ptr(it.ptr) { }

    template<bool Bo, typename T>
    typename vector_iterator<Bo, T>::reference vector_iterator<Bo, T>::operator*() const {
        return *ptr;
    }

    template<bool Bo, typename T>
    typename vector_iterator<Bo, T>::pointer vector_iterator<Bo, T>::operator->() const {
        return &(operator*());
    }

    template<bool Bo, typename T>
    vector_iterator<Bo, T>::~vector_iterator() { }

    template<bool Bo, typename T>
    vector_iterator<Bo, T> &vector_iterator<Bo, T>::operator=(const vector_iterator &it) {
        if (it != *this)
            ptr = it.ptr;
        return *this;
    }

    template<bool Bo, typename T>
    vector_iterator<Bo, T> &vector_iterator<Bo, T>::operator+=(difference_type n) {
        ptr += n;
        return *this;
    }

    template<bool Bo, typename T>
    vector_iterator<Bo, T> &vector_iterator<Bo, T>::operator++() {
        *this += 1;
        return *this;
    }

    template<bool Bo, typename T>
    vector_iterator<Bo, T> vector_iterator<Bo, T>::operator++(int) {
        vector_iterator<Bo, T> temp(*this);
        *this += 1;
        return temp;
    }

    template<bool Bo, typename T>
    vector_iterator<Bo, T> vector_iterator<Bo, T>::operator+(difference_type n) const {
        vector_iterator<Bo, T> temp(*this);
        temp += n;
        return temp;
    }

    template<bool Bo, typename T>
    vector_iterator<Bo, T>
    operator+(typename vector_iterator<Bo, T>::difference_type n, const vector_iterator<Bo, T> &it) {
        vector_iterator<Bo, T> temp(it);
        temp += n;
        return temp;
    }

    template<bool Bo, typename T>
    vector_iterator<Bo, T> &vector_iterator<Bo, T>::operator-=(difference_type n) {
        *this += -n;
        return *this;
    }

    template<bool Bo, typename T>
    vector_iterator<Bo, T> &vector_iterator<Bo, T>::operator--() {
        *this -= 1;
        return *this;
    }

    template<bool Bo, typename T>
    vector_iterator<Bo, T> vector_iterator<Bo, T>::operator--(int) {
        vector_iterator<Bo, T> temp(*this);
        *this -= 1;
        return temp;
    }

    template<bool Bo, typename T>
    typename vector_iterator<Bo, T>::reference vector_iterator<Bo, T>::operator[](difference_type n) {
        return ptr[n];
    }

    template<bool Bo, typename T>
    vector_iterator<Bo, T> vector_iterator<Bo, T>::operator-(difference_type n) const {
        vector_iterator<Bo, T> temp(*this);
        temp -= n;
        return temp;
    }

    template<bool Bo, typename T>
    vector_iterator<Bo, T>::vector_iterator(pointer p) : ptr(p) {};
}

#endif
