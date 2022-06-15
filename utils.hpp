#ifndef UTILS_HPP
# define UTILS_HPP

# include <iterator>

namespace ft {
    template<typename InIt1, typename InIt2>
    bool lexicographical_compare(InIt1 start1, InIt1 end1, InIt2 start2, InIt2 end2) {
        while (start1 != end1) {
            if (start2 == end2 || *start2 < *start1)
                return false;
            else if (*start1 < *start2)
                return true;
            start1++;
            start2++;
        }
        return (start2 != end2);
    }

    template<typename InIt1, typename InIt>
    bool equal(InIt1 start1, InIt1 end1, InIt start2) {
        while (start1 != end1) {
            if (*start1 != *start2)
                return false;
            start1++;
            start2++;
        }
        return true;
    }

    template<typename InIt1, typename InIt2, typename Compare>
    bool lexicographical_compare(InIt1 first1, InIt1 last1, InIt2 first2, InIt2 last2, Compare comp) {
        while (first1 != last1) {
            if (first2 == last2 || comp(*first2, *first1))
                return false;
            else if (comp(*first1, *first2))
                return true;
            first1++;
            first2++;
        }
        return (first2 != last2);
    }

    template<typename It>
    class iterator_traits {
    public:
        typedef typename It::difference_type diff_type;
        typedef typename It::value_type value_type;
        typedef typename It::pointer ptr;
        typedef typename It::reference ref;
        typedef typename It::iterator_category iterator_category;
    };

    template<typename T>
    class iterator_traits<const T *> {
    public:
        typedef ptrdiff_t diff_type;
        typedef T value_type;
        typedef const T *ptr;
        typedef const T &ref;
        typedef std::random_access_iterator_tag iterator_category;
    };

    template<typename T>
    class iterator_traits<T *> {
    public:
        typedef ptrdiff_t diff_type;
        typedef T value_type;
        typedef T *ptr;
        typedef T &ref;
        typedef std::random_access_iterator_tag iterator_category;
    };

    template<bool Cond, typename T = void>
    struct enable_if {
    };

    template<typename T>
    struct enable_if<true, T> {
        typedef T type;
    };

    template<bool bo, typename T1, typename T2>
    struct conditional {
        typedef T2 type;
    };

    template<class InIt>
    size_t distance(InIt start, InIt end) {
        size_t i = 0;
        for (InIt it = start; it != end; it++)
            i++;
        return (i);
    }

    template<typename T1, typename T2>
    struct conditional<true, T1, T2> {
        typedef T1 type;
    };

    template<class T>
    void swap(T &a, T &b) {
        T c(a);
        a = b;
        b = c;
    }

    template<class T>
    const T &max(const T &a, const T &b) {
        return (a < b) ? b : a;
    }

    template<class T1, class T2>
    struct pair {
    public:
        typedef T1 first_type;
        typedef T2 second_type;

        first_type first;
        second_type second;

        pair() : first(first_type()), second(second_type()) { }

        pair(const first_type &first, const second_type &second) : first(first), second(second) { }

        template<class V1, class V2>
        pair(const pair<V1, V2> &m_pair) : first(m_pair.first), second(m_pair.second) { }

        ~pair() {}

        pair &operator=(const pair &another) {
            if (this != &another) {
                first = another.first;
                second = another.second;
            }
            return (*this);
        }
    };

    template<class T1, class T2>
    pair<T1, T2> make_pair(T1 t, T2 u) {
        return (pair<T1, T2>(t, u));
    }

    template<class T1, class T2>
    bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return (lhs.first == rhs.first && lhs.second == rhs.second);
    }


    template<class T1, class T2>
    bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        if (lhs.first < rhs.first) {
            return (true);
        } else if (rhs.first < lhs.first) {
            return (false);
        } else if (lhs.second < rhs.second) {
            return (true);
        }
        return (false);
    }

    template<class T1, class T2>
    bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return !(rhs == lhs);
    }

    template<class T1, class T2>
    bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return (rhs < lhs);
    }

    template<class T1, class T2>
    bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return (!(rhs < lhs));
    }

    template<class T1, class T2>
    bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
        return (!(lhs < rhs));
    }
}

#endif
