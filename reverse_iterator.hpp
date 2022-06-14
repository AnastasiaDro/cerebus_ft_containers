#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include <iostream>
#include "utils.hpp"

namespace ft
{
	template<typename T>
	class reverse_iterator
	{
		public:
			typedef T													iterator_type;
			typedef typename ft::iterator_traits<T>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<T>::value_type			value_type;
			typedef typename ft::iterator_traits<T>::difference_type	difference_type;
			typedef typename ft::iterator_traits<T>::pointer			pointer;
			typedef typename ft::iterator_traits<T>::reference			reference;

			reverse_iterator();
			explicit reverse_iterator(iterator_type it);
			template<typename R_T>
			reverse_iterator(reverse_iterator<R_T> const &rev_it);
			~reverse_iterator();

			iterator_type base() const;
			reference operator*() const;
			reverse_iterator operator+(difference_type nbr) const;
			reverse_iterator operator++(int);
			reverse_iterator &operator++();
			reverse_iterator &operator+=(difference_type nbr);
			reverse_iterator operator-(difference_type nbr) const;
			reverse_iterator operator--(int);
			reverse_iterator &operator--();
			reverse_iterator &operator-=(difference_type nbr);
			pointer operator->() const;
			reference operator[](difference_type nbr);
			template<typename R_T>
			reverse_iterator &operator=(reverse_iterator<R_T> const &copy);

		private:
			iterator_type iter;

	};

	template<typename T>
	reverse_iterator<T>::reverse_iterator() : iter(iterator_type()) {}

	template<typename T>
	reverse_iterator<T>::reverse_iterator(reverse_iterator<T>::iterator_type it) : iter(it) {}

	template<typename T>
	template<typename R_T>
	reverse_iterator<T>::reverse_iterator(reverse_iterator<R_T> const &rev_it) : iter(rev_it.base()) {}

	template<typename T>
	reverse_iterator<T>::~reverse_iterator() {}

	template<typename T>
	typename reverse_iterator<T>::iterator_type reverse_iterator<T>::base() const
	{
		return (iter);
	}

	template<typename T>
	typename reverse_iterator<T>::reference reverse_iterator<T>::operator*() const
	{
		iterator_type tmp = this->iter;
		return (*(--tmp));
	}

	template<typename T>
	reverse_iterator<T> reverse_iterator<T>::operator+(reverse_iterator<T>::difference_type nbr) const
	{
		return (reverse_iterator(this->iter - nbr));
	}

	template<typename T>
	reverse_iterator<T> reverse_iterator<T>::operator++(int)
	{
		iterator_type tmp = base();
		--this->iter;
		return (reverse_iterator(tmp));
	}

	template<typename T>
	reverse_iterator<T> &reverse_iterator<T>::operator++()
	{
		--iter;
		return (*this);
	}

	template <typename T>
	reverse_iterator<T> &reverse_iterator<T>::operator+=(difference_type nbr)
	{
		iter -= nbr;
		return *this;
	}

	template <typename T>
	reverse_iterator<T> reverse_iterator<T>::operator-(difference_type nbr) const
	{
		reverse_iterator<T> copy(*this);
		copy -= nbr;

		return copy;
	}

	template<typename T>
	reverse_iterator<T> reverse_iterator<T>::operator--(int)
	{
		reverse_iterator<T> copy = *this;
		++iter;
		return (copy);
	}

	template<typename T>
	reverse_iterator<T> &reverse_iterator<T>::operator--()
	{
		++iter;
		return (*this);
	}

	template <typename T>
	reverse_iterator<T> &reverse_iterator<T>::operator-=(difference_type nbr)
	{
		*this += -nbr;
		return *this;
	}

	template<typename T>
	typename reverse_iterator<T>::pointer reverse_iterator<T>::operator->() const
	{
		return (&(operator*()));
	}

	template <typename T>
	typename reverse_iterator<T>::reference reverse_iterator<T>::operator[](difference_type n)
	{
		return (*this).base()[-n - 1];
	}

	template<typename T>
	template<typename R_T>
	reverse_iterator<T> &reverse_iterator<T>::operator=(reverse_iterator<R_T> const &copy)
	{
		this->iter = copy.base();
		return (*this);
	}

	template<typename T>
	bool operator==(reverse_iterator<T> const &lhs, reverse_iterator<T> const &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class T1, class T2>
	bool operator==(reverse_iterator<T1> const &lhs, reverse_iterator<T2> const &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class T1, class T2>
	bool operator!=(const reverse_iterator<T1> &lhs, const reverse_iterator<T2> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class T1, class T2>
	bool operator<(const reverse_iterator<T1> &lhs, const reverse_iterator<T2> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class T1, class T2>
	bool operator<=(reverse_iterator<T1> const &lhs, reverse_iterator<T2> const &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class T1, class T2>
	bool operator>(reverse_iterator<T1> const &lhs, reverse_iterator<T2> const &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class T1, class T2>
	bool operator>=(reverse_iterator<T1> const &lhs, reverse_iterator<T2> const &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template<typename T>
	reverse_iterator<T> operator+(typename reverse_iterator<T>::difference_type nbr, reverse_iterator<T> const &rev_it)
	{
		reverse_iterator<T> copy(rev_it);
		copy += nbr;
		return(copy);
	}

	template <typename T, typename T1>
	typename reverse_iterator<T>::difference_type operator-(const reverse_iterator<T> &lhs, const reverse_iterator<T1> &rhs)
	{
		return rhs.base() - lhs.base();
	}

}

#endif

