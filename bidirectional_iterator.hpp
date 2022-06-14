#ifndef BIDIRECTIONAL_ITERATOR_HPP
#define BIDIRECTIONAL_ITERATOR_HPP

#include "node_tree.hpp"
#include "utils.hpp"

namespace ft
{
	template <bool C_I, typename T>
	class bidirectional_iterator
	{
		public:
			typedef typename std::iterator<std::bidirectional_iterator_tag, T>::value_type		value_type;
			typedef typename std::iterator<std::bidirectional_iterator_tag, T>::difference_type	difference_type;
			typedef typename std::iterator<std::bidirectional_iterator_tag, T>::iterator_category	iterator_category;
			typedef typename ft::conditional<C_I, const T *, T *>::type					pointer;
			typedef typename ft::conditional<C_I, const T &, T &>::type					reference;
			typedef Node<value_type> *node_pointer;

		private:
			node_pointer	node_ptr;
			node_pointer	root;

			void setnext()
			{
				if (!this->node_ptr)
				{
					this->node_ptr = this->root;
					if (this->node_ptr)
					{
						while (this->node_ptr->node_left)
							this->node_ptr = this->node_ptr->node_left;
					}
					return ;
				}
				if (this->node_ptr->node_right)
				{
					this->node_ptr = this->node_ptr->node_right;
					while (this->node_ptr->node_left)
						this->node_ptr = this->node_ptr->node_left;
				}
				else
				{
					while (this->node_ptr->node_parent && this->node_ptr == this->node_ptr->node_parent->node_right)
						this->node_ptr = this->node_ptr->node_parent;
					this->node_ptr = this->node_ptr->node_parent;
				}
			}

			void setprev()
			{
				if (!this->node_ptr)
				{
					this->node_ptr = this->root;
					if (this->node_ptr)
					{
						while (this->node_ptr->node_right)
							this->node_ptr = this->node_ptr->node_right;
					}
					return ;
				}
				if (this->node_ptr->node_left)
				{
					this->node_ptr = this->node_ptr->node_left;
					while (this->node_ptr->node_right)
						this->node_ptr = this->node_ptr->node_right;
				}
				else
				{
					while (this->node_ptr->node_parent && this->node_ptr == this->node_ptr->node_parent->node_left)
						this->node_ptr = this->node_ptr->node_parent;
					this->node_ptr = this->node_ptr->node_parent;
				}

			}

		public:
			bidirectional_iterator() : node_ptr(NULL), root(NULL){}

			bidirectional_iterator(const bidirectional_iterator &other) : node_ptr(other.node_ptr), root(other.root)
			{
			}

			bidirectional_iterator(node_pointer node_ptr, node_pointer root) : node_ptr(node_ptr), root(root)
			{
			}

			virtual ~bidirectional_iterator() {}

			bidirectional_iterator	&operator=(const bidirectional_iterator &other)
			{
				if (this != &other)
				{
					this->node_ptr = other.node_ptr;
					this->root = root;
				}
				return (*this);
			}

			node_pointer base()
			{
				return (this->node_ptr);
			}

			node_pointer base() const
			{
				return (this->node_ptr);
			}

			reference				operator*() const
			{
				return (this->node_ptr->value);
			}

			pointer					operator->() const
			{
				return (&(operator*()));
			}

			bidirectional_iterator	&operator++()
			{
				setnext();
				return (*this);
			}

			bidirectional_iterator	operator++(int)
			{
				bidirectional_iterator it = *this;
				setnext();
				return (it);
			}

			bidirectional_iterator	&operator--()
			{
				setprev();
				return (*this);
			}

			bidirectional_iterator	operator--(int)
			{
				bidirectional_iterator it = *this;
				setprev();
				return (it);
			}

			template<bool Iter1, bool Iter2, typename U>
			friend bool operator==(const bidirectional_iterator<Iter1, U> &lhs, const bidirectional_iterator<Iter2, U> &rhs)
			{
				return (lhs.node_ptr == rhs.node_ptr);
			}

			template<bool Iter1, bool Iter2, typename U>
			friend bool operator!=(const bidirectional_iterator<Iter1, U> &lhs, const bidirectional_iterator<Iter2, U> &rhs)
			{
				return (lhs.node_ptr != rhs.node_ptr);
			}

			operator bidirectional_iterator<true, value_type>() const
			{
				return (bidirectional_iterator<true, value_type>(this->node_ptr, this->root));
			}
	};

}


#endif