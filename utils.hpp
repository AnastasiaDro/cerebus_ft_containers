#ifndef UTILS_HPP
#define UTILS_HPP

#include <iterator>

namespace ft
{
	template <typename InIt1, typename InIt>
	bool equal( InIt1 first1, InIt1 last1, InIt first2 ) {
		while (first1!=last1) {
		if (*first1 != *first2)
			return false;
		first1++;
		first2++;
		}
		return true;
	}

	template <typename InIt1, typename InIt2>
	bool lexicographical_compare (InIt1 first1, InIt1 last1, InIt2 first2, InIt2 last2) {
		while (first1 != last1) {
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			first1++;
			first2++;
		}
		return (first2 != last2);
	}

	template <typename InIt1, typename InIt2, typename Compare>
	bool lexicographical_compare (InIt1 first1, InIt1 last1, InIt2 first2, InIt2 last2, Compare comp) {
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

	template <typename Iterator>
	class iterator_traits {
		public:
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
			typedef typename Iterator::iterator_category	iterator_category;
	};

	template <typename T>
	class iterator_traits<T*> {
		public:
			typedef ptrdiff_t							difference_type;
			typedef T									value_type;
			typedef T*									pointer;
			typedef T&									reference;
			typedef std::random_access_iterator_tag		iterator_category;
	};

	template <typename T>
	class iterator_traits<const T*> {
		public:
			typedef ptrdiff_t						difference_type;
			typedef T								value_type;
			typedef const T*						pointer;
			typedef const T&						reference;
			typedef std::random_access_iterator_tag	iterator_category;
	};

	template<bool Cond, typename T = void>
	struct enable_if { };

	template<typename T>
	struct enable_if<true, T> {
		typedef T type;
	};

	template <bool bo, typename T1, typename T2>
	struct conditional {
		typedef T2 type;
	};

	template <typename T1, typename T2>
	struct conditional<true, T1, T2> {
		typedef T1 type;
	};

	template <class InIt>
	size_t	distance(InIt first, InIt second) {
		size_t i = 0;
		for (InIt it = first; it != second; it++)
			i++;
		return (i);
	}

	template <class T>
	const T& max(const T &a, const T &b) {
		return (a < b) ? b : a;
	}

	template <class T>
    void swap(T &a, T &b) {
        T c(a);
        a = b;
        b = c;
    }

	template <class T1, class T2>
	struct pair {
	public:
		typedef T1 first_type;
		typedef T2 second_type;

	public:
		first_type first;
		second_type second;

	public:
		pair() : first(first_type()), second(second_type()) {}

		pair(const first_type &a, const second_type &b) : first(a), second(b) { }

		template <class U1, class U2>
		pair(const pair<U1, U2> &pr) : first(pr.first), second(pr.second) { }

		~pair() {}

		pair &operator=(const pair &other) {
			if (this != &other) {
				first = other.first;
				second = other.second;
			}
			return (*this);
		}
	};

	template <class T1, class T2>
	pair<T1, T2> make_pair(T1 t, T2 u) {
		return (pair<T1, T2>(t, u));
	}

	template <class T1, class T2>
	bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template <class T1, class T2>
	bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		return (!(lhs == rhs));
	}

	template <class T1, class T2>
	bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		if (lhs.first < rhs.first)
			return (true);
		else if (rhs.first < lhs.first)
			return (false);
		else if (lhs.second < rhs.second)
			return (true);
		else
			return (false);
	}

	template <class T1, class T2>
	bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		return (!(rhs < lhs));
	}

	template <class T1, class T2>
	bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		return (rhs < lhs);
	}

	template <class T1, class T2>
	bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
		return (!(lhs < rhs));
	}
}

#endif