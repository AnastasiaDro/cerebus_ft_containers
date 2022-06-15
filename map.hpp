#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include "utils.hpp"
#include "bidirectional_iterator.hpp"
#include "RedBlackTree.hpp"
#include "node_tree.hpp"
#include "reverse_iterator.hpp"

namespace ft {
	template <class Key, class T,
	class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key,T> > >
    class map {
    public:
        typedef Key key_type;
        typedef T val_type;
        typedef Allocator allocator_type;
        typedef pair<const key_type, val_type> pair_type;
        typedef Compare key_compare;

        typedef typename allocator_type::pointer ptr;
        typedef typename allocator_type::const_pointer const_ptr;
        typedef typename allocator_type::reference ref;
        typedef typename allocator_type::const_reference const_ref;

        typedef size_t size_type;
        typedef bidirectional_iterator<true, pair_type> const_it;
        typedef bidirectional_iterator<false, pair_type> iterator;
        typedef typename ft::iterator_traits<iterator>::diff_type diff_type;
        typedef ft::reverse_iterator<const_it> const_reverse_it;
        typedef ft::reverse_iterator<iterator> reverse_it;

        class value_compare : std::binary_function<pair_type, pair_type, bool> {
            friend class map<key_type, val_type, key_compare, Allocator>;

        protected:
            Compare compare;
            explicit value_compare(Compare c) : compare(c) { }

        public:
            bool operator()(const pair_type &x, const pair_type &y) const {
                return (compare(x.first, y.first));
            }
        };

		private:
            typedef Node<pair_type> *node_ptr;
            typedef Node<pair_type> &node_ref;
            typedef typename allocator_type::template rebind<Node<pair_type> >::other node_allocator;
            typedef RedBlackTree<pair_type, value_compare, node_allocator>				node_container;
			node_container	container;
			key_compare		compare;
            allocator_type	allocator;

		public:
            map(const map& x) : container(x.container), compare(x.compare), allocator(x.allocator) {}

            explicit map(const key_compare& comp = key_compare(), const allocator_type& allocator = allocator_type()) : container(node_container(value_compare(comp))), compare(comp), allocator(allocator) { }

			template <class InputIterator>
			map(InputIterator f, InputIterator l, const key_compare& comp = key_compare(), const allocator_type& allocator = allocator_type()) : container(node_container(value_compare(comp))), compare(comp), allocator(allocator) {
				insert(f, l);
			}

			~map() {
				clear();
			}

			iterator begin() {
				return (iterator(container.get_node_ptr(), container.get_root()));
			}

			const_it begin() const {
				return (const_it(container.get_node_ptr(), container.get_root()));
			}

			iterator end() {
				return (iterator(NULL, container.get_root()));
			}

			const_it end() const {
				return (const_it(NULL, container.get_root()));
			}

			reverse_it rbegin() {
				return (reverse_it(end()));
			}

			const_reverse_it rbegin() const {
				return (const_reverse_it(end()));
			}

			reverse_it rend() {
				return (reverse_it(begin()));
			}

			const_reverse_it rend() const {
				return (const_reverse_it(begin()));
			}

			bool empty() const {
				return (container.get_size() == 0);
			}

			size_type size() const {
				return (container.get_size());
			}

			size_type max_size() const {
				return (container.get_alloc().max_size());
			}

            const val_type& at(const key_type& k) const {
                ft::pair< const key_type, val_type> value = ft::make_pair<const key_type, val_type>(k, val_type());
                node_ptr tmp = container.search_node(value);
                if (!tmp)
                    throw std::out_of_range("map");
                return (tmp->value.second);
            }

			val_type& at(const key_type& k) {
				ft::pair< const key_type, val_type> value = ft::make_pair<const key_type, val_type>(k, val_type());
				node_ptr tmp = container.search_node(value);
				if (!tmp)
					throw std::out_of_range("map");
				return (tmp->value.second);
			}

            map& operator=(const map& map) {
                if (this != &map) {
                    clear();
                    container = map.container;
                }
                return (*this);
            }

			val_type& operator[](const key_type& key) {
				ft::pair< const key_type, val_type> value = ft::make_pair<const key_type, val_type>(key, val_type());
				return insert(value).first->second;
			}

			pair<iterator,bool> insert(const pair_type& val) {
				bool b;
				node_ptr tmp = container.insert(val, &b);
				return (ft::make_pair<iterator, bool>(iterator(tmp, container.get_root()), b));
			}


			template <class InIt>
			void insert(InIt f, InIt l) {
				while (f != l) {
					insert(*f);
					f++;
				}
			}

            iterator insert(iterator pos, const pair_type& pair) {
                return iterator(container.insert(pos.base(), pair), container.get_root());
            }

            size_type erase(const key_type& key) {
                ft::pair<const key_type, val_type> pair = ft::make_pair<const key_type, val_type>(key, val_type());
                return (container.erase(pair));
            }

            void erase(iterator pos) {
				container.erase(pos.base());
			}

			void erase(iterator f, iterator l) {
				for(iterator it; f != l;) {
					it = f++;
					erase(it);
				}
			}

            void clear() {
                container.clear();
            }

			void swap(map& map) {
				container.swap(map.container);
			}

			key_compare key_comp() const {
				return (compare);
			}

			value_compare value_comp() const {
				return (value_compare(key_compare()));
			}

			iterator find (const key_type& key) {
				ft::pair<const key_type, val_type> pair = ft::make_pair<const key_type, val_type>(key, val_type());
				return (iterator(container.search_node(pair), container.get_root()));
			}

			const_it find (const key_type& k) const
			{
				ft::pair<const key_type, val_type> value = ft::make_pair<const key_type, val_type>(k, val_type());
				return (const_it(container.search_node(value), container.get_root()));
			}

			size_type count (const key_type& k) const
			{
				ft::pair<const key_type, val_type> value = ft::make_pair<const key_type, val_type>(k, val_type());
				if (container.search_node(value))
					return (1);
				else
					return (0);
			}

			iterator lower_bound (const key_type& k)
			{
				ft::pair<const key_type, val_type> value = ft::make_pair<const key_type, val_type>(k, val_type());
				node_ptr other = NULL;
				container.lower(value, container.get_root(), &other);
				return (iterator(other, container.get_root()));
			}

			const_it lower_bound(const key_type& k) const
			{
				ft::pair<const key_type, val_type> value = ft::make_pair<const key_type, val_type>(k, val_type());
				node_ptr other = NULL;
				container.lower(value, container.get_root(), &other);
				return (const_it(other, container.get_root()));
			}

			iterator upper_bound(const key_type& k)
			{
				node_ptr sougth = NULL;
				ft::pair<const key_type, val_type> p = ft::make_pair<const key_type, val_type>(k, val_type());
				container.upper(p, container.get_root(), &sougth);
				return iterator(sougth, container.get_root());
			}

			const_it upper_bound(const key_type& k) const
			{
				ft::pair<const key_type, val_type> value = ft::make_pair<const key_type, val_type>(k, val_type());
				node_ptr other = NULL;
				container.upper(value, container.get_root(), &other);
				return (const_it(other, container.get_root()));
			}

			pair<const_it,const_it> equal_range(const key_type& k) const
			{
				return ft::make_pair(lower_bound(k), upper_bound(k));
			}

			pair<iterator,iterator> equal_range(const key_type& k)
			{
				return ft::make_pair(lower_bound(k), upper_bound(k));
			}

			allocator_type get_allocator() const
			{
				return (this->allocator);
			}
	};

	template <class Key, class T, class Compare, class Alloc>
	bool operator==(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return (!(rhs < lhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return (rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
	{
		return (!(lhs < rhs));
	}

	template<class Key, class T, class Compare, class Alloc>
	void swap(map<Key,T,Compare,Alloc>& lhs, map<Key,T,Compare,Alloc>& rhs)
	{
		lhs.swap(rhs);
	}
}

#endif
