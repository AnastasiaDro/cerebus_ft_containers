#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include "utils.hpp"
#include "bidirectional_iterator.hpp"
#include "RedBlackTree.hpp"
#include "node_tree.hpp"
#include "reverse_iterator.hpp"

namespace ft
{
	template <class Key, class T,
	class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map
	{
		public:
			typedef Key															key_type;
			typedef T															mapped_type;
			typedef pair<const key_type, mapped_type>							value_type;
			typedef Compare														key_compare;
			typedef Alloc														allocator_type;
			typedef typename allocator_type::reference							reference;
			typedef typename allocator_type::const_reference					const_reference;
			typedef typename allocator_type::pointer							pointer;
			typedef typename allocator_type::const_pointer						const_pointer;
			typedef bidirectional_iterator<true, value_type>					const_iterator;
			typedef bidirectional_iterator<false, value_type>					iterator;
			typedef ft::reverse_iterator<iterator>								reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type		difference_type;
			typedef size_t														size_type;

			class value_compare : std::binary_function<value_type, value_type, bool>
			{
				friend class map<key_type, mapped_type, key_compare, Alloc>;

				protected:
					Compare comp;
					value_compare(Compare c) : comp(c) {}

				public:
					bool operator()(const value_type &x, const value_type &y) const
					{
						return (comp(x.first, y.first));
					}
			};

		private:
			typedef typename allocator_type::template rebind<Node<value_type> >::other	node_allocator;
			typedef RedBlackTree<value_type, value_compare, node_allocator>				node_container;
			typedef Node<value_type>*													node_pointer;
			typedef Node<value_type>&													node_reference;

			node_container	container;
			key_compare		compare;
			allocator_type	allocator;

		public:
			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: container(node_container(value_compare(comp))), compare(comp), allocator(alloc)
			{}

			template <class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: container(node_container(value_compare(comp))), compare(comp), allocator(alloc) {
				insert(first, last);
			}

			map(const map& x) : container(x.container), compare(x.compare), allocator(x.allocator) {}

			~map() {
				clear();
			}

			map& operator=(const map& x) {
				if (this != &x) {
					clear();
					container = x.container;
				}
				return (*this);
			}

			iterator begin() {
				return (iterator(container.get_node_ptr(), container.get_root()));
			}

			const_iterator begin() const{
				return (const_iterator(container.get_node_ptr(), container.get_root()));
			}

			iterator end() {
				return (iterator(NULL, container.get_root()));
			}

			const_iterator end() const {
				return (const_iterator(NULL, container.get_root()));
			}

			reverse_iterator rbegin() {
				return (reverse_iterator(end()));
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

			bool empty() const {
				if (!container.get_size())
					return (true);
				else
					return (false);
			}

			size_type size() const {
				return (container.get_size());
			}

			size_type max_size() const {
				return (container.get_alloc().max_size());
			}

			mapped_type& at(const key_type& k) {
				ft::pair< const key_type, mapped_type> value = ft::make_pair<const key_type, mapped_type>(k, mapped_type());
				node_pointer tmp = container.search_node(value);
				if (!tmp)
					throw std::out_of_range("map");
				return (tmp->value.second);
			}

			const mapped_type& at(const key_type& k) const {
				ft::pair< const key_type, mapped_type> value = ft::make_pair<const key_type, mapped_type>(k, mapped_type());
				node_pointer tmp = container.search_node(value);
				if (!tmp)
					throw std::out_of_range("map");
				return (tmp->value.second);
			}

			mapped_type& operator[](const key_type& k) {
				ft::pair< const key_type, mapped_type> value = ft::make_pair<const key_type, mapped_type>(k, mapped_type());
				return (insert(value).first->second);
			}

			pair<iterator,bool> insert(const value_type& x) {
				bool b_insert;
				node_pointer tmp = container.insert(x, &b_insert);
				return (ft::make_pair<iterator, bool>(iterator(tmp, container.get_root()), b_insert));
			}

			iterator insert(iterator position, const value_type& x) {
				return iterator(container.insert(position.base(), x), container.get_root());
			}

			template <class InputIterator>
			void insert(InputIterator first, InputIterator last)
			{
				while (first != last)
				{
					insert(*first);
					++first;
				}
			}

			void erase(iterator position)
			{
				container.erase(position.base());
			}

			size_type erase(const key_type& k) {
				ft::pair<const key_type, mapped_type> value = ft::make_pair<const key_type, mapped_type>(k, mapped_type());
				return (container.erase(value));
			}

			void erase(iterator first, iterator last) {
				for(iterator it; first != last;) {
					it = first++;
					erase(it);
				}
			}

			void swap(map& x) {
				container.swap(x.container);
			}

			void clear() {
				container.clear();
			}

			key_compare key_comp() const {
				return (compare);
			}

			value_compare value_comp() const {
				return (value_compare(key_compare()));
			}

			iterator find (const key_type& k) {
				ft::pair<const key_type, mapped_type> value = ft::make_pair<const key_type, mapped_type>(k, mapped_type());
				return (iterator(container.search_node(value), container.get_root()));
			}

			const_iterator find (const key_type& k) const {
				ft::pair<const key_type, mapped_type> value = ft::make_pair<const key_type, mapped_type>(k, mapped_type());
				return (const_iterator(container.search_node(value), container.get_root()));
			}

			size_type count (const key_type& key) const {
				ft::pair<const key_type, mapped_type> value = ft::make_pair<const key_type, mapped_type>(key, mapped_type());
				if (container.search_node(value))
					return (1);
				else
					return (0);
			}

			iterator lower_bound (const key_type& key) {
				ft::pair<const key_type, mapped_type> value = ft::make_pair<const key_type, mapped_type>(key, mapped_type());
				node_pointer other = NULL;
				container.lower(value, container.get_root(), &other);
				return (iterator(other, container.get_root()));
			}

			const_iterator lower_bound(const key_type& key) const {
				ft::pair<const key_type, mapped_type> value = ft::make_pair<const key_type, mapped_type>(key, mapped_type());
				node_pointer other = NULL;
				container.lower(value, container.get_root(), &other);
				return (const_iterator(other, container.get_root()));
			}

			iterator upper_bound(const key_type& key) {
				node_pointer sougth = NULL;
				ft::pair<const key_type, mapped_type> p = ft::make_pair<const key_type, mapped_type>(key, mapped_type());
				container.upper(p, container.get_root(), &sougth);
				return iterator(sougth, container.get_root());
			}

			const_iterator upper_bound(const key_type& key) const {
				ft::pair<const key_type, mapped_type> value = ft::make_pair<const key_type, mapped_type>(key, mapped_type());
				node_pointer other = NULL;
				container.upper(value, container.get_root(), &other);
				return (const_iterator(other, container.get_root()));
			}

			pair<const_iterator,const_iterator> equal_range(const key_type& key) const {
				return ft::make_pair(lower_bound(key), upper_bound(key));
			}

			pair<iterator,iterator> equal_range(const key_type& key) {
				return ft::make_pair(lower_bound(key), upper_bound(key));
			}

			allocator_type get_allocator() const {
				return (allocator);
			}
	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
		return (!(lhs == rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
		return (!(rhs < lhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
		return (rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {
		return (!(lhs < rhs));
	}

	template<class Key, class T, class Compare, class Alloc>
	void swap(map<Key,T,Compare,Alloc>& lhs, map<Key,T,Compare,Alloc>& rhs) {
		lhs.swap(rhs);
	}
}

#endif
