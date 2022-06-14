#ifndef REDBLACKTREE
#define REDBLACKTREE

#include "utils.hpp"
#include "bidirectional_iterator.hpp"

namespace ft
{
	typedef enum
	{
		RED,
		BLACK
	} color;

	template <typename T, class Compare, class Alloc>
	class RedBlackTree
	{
		public:
			typedef T				value_type;
			typedef Compare			compare_key;
			typedef size_t			size_type;
			typedef Alloc			allocator_type;
			typedef ft::Node<T>		node_type;
			typedef node_type*		pointer;
			typedef node_type&		reference;

		private:
			compare_key		_compare;
			allocator_type	_alloc;
			pointer			_root;
			pointer			_node_ptr;
			size_type		_size;

		public:
			RedBlackTree(const compare_key cmp) : _compare(cmp), _alloc(allocator_type()), _root(NULL), _node_ptr(NULL), _size(0) {}

			RedBlackTree(const RedBlackTree &other) : _compare(other._compare), _alloc(other._alloc), _root(NULL), _node_ptr(NULL), _size(other._size)
			{
				copyTree(&this->_root, other._root, NULL, NULL);
				left_minimum();
			}

			~RedBlackTree()
			{
				clearTree(this->_root);
			}

			RedBlackTree &operator=(const RedBlackTree &other)
			{
				if (this != &other)
				{
					clearTree(this->_root);
					copyTree(&this->_root, other._root, NULL, NULL);
					left_minimum();
					this->_size = other._size;
				}
				return (*this);
			}

			allocator_type get_alloc() const
			{
				return (this->_alloc);
			}

			pointer get_root() const
			{
				return (this->_root);
			}

			pointer get_node_ptr() const
			{
				return (this->_node_ptr);
			}

			size_type get_size() const
			{
				return (this->_size);
			}

			void swap (RedBlackTree &other)
			{
				pointer new_node = this->_root;
				this->_root = other._root;
				other._root = new_node;
				size_type new_size = this->_size;
				this->_size = other._size;
				other._size = new_size;
				pointer new_node_ptr = this->_node_ptr;
				this->_node_ptr = other._node_ptr;
				other._node_ptr = new_node_ptr;
			}

			void erase(pointer position)
			{
				if (!position)
					return ;
				if (position == this->_node_ptr)
					left_minimum();
				delete_tree(position);
				--this->_size;
			}

			pointer search_node(const value_type &value) const
			{
				pointer search = this->_root;
				while (search)
				{
					if (this->_compare(search->value, value))
						search = search->node_right;
					else if (this->_compare(value, search->value))
						search = search->node_left;
					else
						break ;
				}
				return (search);
			}

			bool erase(const value_type &value)
			{
				pointer search = search_node(value);
				while (search)
				{
					if (this->_compare(search->value, value))
						search = search->node_right;
					else if (this->_compare(value, search->value))
						search = search->node_left;
					else
						break ;
				}

				if (!search)
					return (0);
				if (search == this->_node_ptr)
					left_minimum();
				delete_tree(search);
				--this->_size;
				return (1);
			}

			pointer next(pointer position)
			{
				if (!position)
				{
					position = this->_root;
					if (position)
					{
						while (position->node_left)
							position = position->node_left;
					}
					return (position);
				}
				if (position->node_right)
				{
					position = position->node_right;
					while (position->node_left)
						position = position->node_left;
				}
				else
				{
					while (position == position->node_parent->node_right && position->node_parent)
						position = position->node_parent;
					position = position->node_parent;
				}
				return (position);
			}

			pointer insert(pointer position, const value_type& val)
			{
				bool b_insert;
				if (!_root || !position)
					return (insert(val, &b_insert));

				pointer copy_position = position;
				position = next(position);

				if (this->_compare(copy_position->value, val) && (!position || this->_compare(val, position->value)))
				{
					pointer new_node = create_node(val);
					if (!copy_position->node_right)
						copy_position->node_right = new_node;
					else
					{
						pointer tmp = copy_position->node_right;
						while (tmp->node_left)
							tmp = tmp->node_left;
						if (_node_ptr == tmp)
							_node_ptr = new_node;
						tmp->node_left = new_node;
					}
					if (this->_size == 0)
						_node_ptr = new_node;
					insert_case1(new_node);
					++this->_size;
					return (new_node);
				}
				else
					return (insert(val, &b_insert));
				return (NULL);
			}

			pointer insert(const value_type& val, bool *b_insert)
			{
				pointer x = this->_root;
				pointer new_node = create_node(val);

				while(x)
				{
					if (this->_compare(val, x->value))
					{
						if (x->node_left)
							x = x->node_left;
						else
						{
							new_node->node_parent = x;
							x->node_left = new_node;
							if (this->_node_ptr == x)
								this->_node_ptr = new_node;
							break ;
						}
					}
					else if (this->_compare(x->value, val))
					{
						if (x->node_right)
							x = x->node_right;
						else
						{
							new_node->node_parent = x;
							x->node_right = new_node;
							break ;
						}
					}
					else
					{
						delete_node(new_node);
						*b_insert = false;
						return (x);
					}
				}
				if (this->_size == 0)
					this->_node_ptr = new_node;
				insert_case1(new_node);
				++this->_size;
				*b_insert = true;
				return (new_node);
			}

			void clear()
			{
				this->_size = 0;
				clearTree(this->_root);
			}

			void lower(const value_type &val, pointer node, pointer *other_node) const
			{
				if (*other_node || !node)
					return ;
				lower(val, node->node_left, other_node);
				if (*other_node)
					return ;
				if (!this->_compare(node->value, val))
					*other_node = node;
				lower(val, node->node_right, other_node);
			}

			void upper(const value_type &val, pointer node, pointer *other_node) const
			{
				if (*other_node || !node)
					return ;
				upper(val, node->node_left, other_node);
				if (*other_node)
					return ;
				if (this->_compare(val, node->value))
					*other_node = node;
				upper(val, node->node_right, other_node);
			}

		private:
			void copyTree(pointer *lnode, pointer rnode, pointer lpar, pointer rpar)
			{
				if (!rnode)
					return ;

				*lnode = create_node(rnode->value);
				(*lnode)->node_parent = lpar;
				if (rpar)
				{
					if (rpar->node_right == rnode)
						lpar->node_right = *lnode;
					else
						lpar->node_left = *lnode;
				}
				copyTree(&((*lnode)->node_left), rnode->node_left, *lnode, rnode);
				copyTree(&((*lnode)->node_right), rnode->node_right, *lnode, rnode);
			}

			void left_minimum()
			{
				if (!this->_node_ptr)
				{
					this->_node_ptr = this->_root;
					if (this->_node_ptr)
					{
						while (this->_node_ptr->node_left)
							this->_node_ptr = this->_node_ptr->node_left;
					}
					return ;
				}
				if (this->_node_ptr->node_right)
				{
					this->_node_ptr = this->_node_ptr->node_right;
					while (this->_node_ptr->node_left)
						this->_node_ptr = this->_node_ptr->node_left;
				}
				else
				{
					while (this->_node_ptr->node_parent && this->_node_ptr == this->_node_ptr->node_parent->node_right)
						this->_node_ptr = this->_node_ptr->node_parent;
					this->_node_ptr = this->_node_ptr->node_parent;
				}
			}

			pointer minimum(pointer left_more)
			{
				while (left_more->node_left != NULL)
					left_more = left_more->node_left;
				return (left_more);
			}

			pointer get_grandparent(pointer x)
			{
				if (x->node_parent != NULL)
					return (x->node_parent->node_parent);
				return (NULL);
			}

			pointer get_uncle(pointer x)
			{
				pointer old = get_grandparent(x);
				if (old == NULL)
					return (NULL);
				if (x->node_parent == old->node_left)
					return (old->node_right);
				else
					return (old->node_left);
			}

			void rotateRight(pointer x)
			{
				pointer pivot = x->node_left;
				if (x == this->_root)
					this->_root = pivot;
				pivot->node_parent = x->node_parent;
				if (pivot->node_parent != NULL)
				{
					if (x->node_parent->node_left == x)
						x->node_parent->node_left = pivot;
					else
						x->node_parent->node_right = pivot;
				}
				x->node_left = pivot->node_right;
				if (x->node_left != NULL)
					pivot->node_right->node_parent = x;
				x->node_parent = pivot;
				pivot->node_right = x;
			}

			void rotateLeft(pointer x)
			{
				pointer pivot = x->node_right;

				if (x == this->_root)
					this->_root = pivot;
				pivot->node_parent = x->node_parent;
				if (pivot->node_parent != NULL)
				{
					if (x->node_parent->node_left == x)
						x->node_parent->node_left = pivot;
					else
						x->node_parent->node_right = pivot;
				}
				x->node_right = pivot->node_left;
				if (x->node_right != NULL)
					pivot->node_left->node_parent = x;
				x->node_parent = pivot;
				pivot->node_left = x;
			}

			void insert_case1(pointer x)
			{
				if (x->node_parent == NULL)
				{
					this->_root = x;
					x->red = BLACK;
				}
				else
					insert_case2(x);
			}

			void insert_case2(pointer x)
			{
				if (x->node_parent->red == RED)
					insert_case3(x);
			}

			void insert_case3(pointer x)
			{
				pointer new_uncle = get_uncle(x);

				if (new_uncle != NULL && new_uncle->red == RED)
				{
					x->node_parent->red = BLACK;
					new_uncle->red = BLACK;
					pointer old = get_grandparent(x);
					old->red = RED;
					insert_case1(old);
				}
				else
					insert_case4(x);
			}

			void insert_case4(pointer x)
			{
				pointer old = get_grandparent(x);

				if ((x == x->node_parent->node_right) && (x->node_parent == old->node_left))
				{
					rotateLeft(x->node_parent);
					x = x->node_left;
				}
				else if ((x == x->node_parent->node_left) && (x->node_parent == old->node_right))
				{
					rotateRight(x->node_parent);
					x = x->node_right;
				}
				insert_case5(x);
			}

			void insert_case5(pointer x)
			{
				pointer old = get_grandparent(x);

				x->node_parent->red = BLACK;
				old->red = RED;
				if ((x == x->node_parent->node_left) && (x->node_parent == old->node_left))
					rotateRight(old);
				else
					rotateLeft(old);
			}

			pointer get_right_min(pointer x)
			{
				x = x->node_right;
				if (x)
				{
					while (x->node_left)
						x = x->node_left;
				}
				return (x);
			}

			pointer get_left_max(pointer x)
			{
				x = x->node_left;
				if (x)
				{
					while (x->node_right)
						x = x->node_right;
				}
				return (x);
			}

			pointer get_sibling(pointer x)
			{
				if (x == x->node_parent->node_left)
					return (x->node_parent->node_right);
				else
					return (x->node_parent->node_left);
			}

			pointer get_search_for_swap(pointer x)
			{
				pointer tmp = get_left_max(x);
				if(!tmp)
					tmp = get_right_min(x);
				return (tmp);
			}

			void swap_nodes(pointer before, const pointer after)
			{
				if (this->_root == before)
					this->_root = after;
				if (before->node_parent)
				{
					if (before->node_parent->node_left == before)
						before->node_parent->node_left = after;
					else
						before->node_parent->node_right = after;
				}
				if (after->node_parent->node_left == after)
					after->node_parent->node_left = before;
				else
					after->node_parent->node_right = before;

				pointer new_node = before->node_parent;
				before->node_parent = after->node_parent;
				after->node_parent = new_node;

				if (before->node_left)
					before->node_left->node_parent = after;
				if (after->node_left)
					after->node_left->node_parent = before;

				new_node = before->node_left;
				before->node_left = after->node_left;
				after->node_left = new_node;

				if (before->node_right)
					before->node_right->node_parent = after;
				if (after->node_right)
					after->node_right->node_parent = before;

				new_node = before->node_right;
				before->node_right = after->node_right;
				after->node_right = new_node;

				bool new_color = after->red;
				after->red = before->red;
				before->red = new_color;
			}

			void delete_case_rebalance(pointer x)
			{
				pointer s = get_sibling(x);

				if (!s)
					return ;

				if (x == x->node_parent->node_left)
				{
					if (s->red == BLACK)
					{
						if (s->node_right && s->node_right->red == RED)
							del_case_left_rotate(get_sibling(x), x);
						else if (s->node_left && s->node_left->red == RED)
						{
							s->red = RED;
							s->node_left->red = BLACK;
							rotateRight(s);
							del_case_left_rotate(get_sibling(x), x);
						}
						else
						{
							s->red = RED;
							if (x->node_parent->red == RED)
								x->node_parent->red = BLACK;
							else if (x->node_parent != this->_root)
								delete_case_rebalance(x->node_parent);
						}
					}
					else
					{
						s->node_parent->red = RED;
						s->red = BLACK;
						rotateLeft(s->node_parent);

						if (s->node_left->node_right)
						{
							s->node_left->red = BLACK;
							s->node_left->node_right->red = RED;
						}
						if (s != this->_root)
							delete_case_rebalance(s);
					}
				}
				else
				{
					if (s->red == BLACK)
					{
						if (s->node_left && s->node_left->red == RED)
							del_case_right_rotate(get_sibling(x), x);
						else if (s->node_right && s->node_right->red == RED)
						{
							s->red = RED;
							s->node_right->red = BLACK;
							rotateLeft(s);
							del_case_right_rotate(get_sibling(x), x);
						}
						else
						{
							s->red = RED;
							if (x->node_parent->red == RED)
								x->node_parent->red = BLACK;
							else if (x->node_parent != this->_root)
								delete_case_rebalance(x->node_parent);
						}
					}
					else
					{
						s->node_parent->red = RED;
						s->red = BLACK;
						rotateRight(s->node_parent);

						if (s->node_right->node_left)
						{
							s->node_right->red = BLACK;
							s->node_right->node_left->red = RED;
						}
						if (s != this->_root)
							delete_case_rebalance(s);
					}
				}
			}

			void del_case_left_rotate(pointer s, pointer x)
			{
				s->red = x->node_parent->red;
				x->node_parent->red = BLACK;
				s->node_right->red = BLACK;
				rotateLeft(x->node_parent);
				return ;
			}

			void del_case_right_rotate(pointer s, pointer x)
			{
				s->red = x->node_parent->red;
				x->node_parent->red = BLACK;
				s->node_left->red = BLACK;
				rotateRight(x->node_parent);
				return ;
			}

			void delete_tree(pointer x)
			{
				pointer child = get_search_for_swap(x);
				if (!child)
				{
					if (x->red == RED)
						delete_node(x);
					else
					{
						if (x != this->_root)
							delete_case_rebalance(x);
						delete_node(x);
					}

				}
				else
				{
					swap_nodes(x, child);
					if (x->red == RED)
						delete_node(x);
					else
					{
						if (x->node_left)
						{
							swap_nodes(x, x->node_left);
							delete_node(x);
						}
						else if (x->node_right)
						{
							swap_nodes(x, x->node_right);
							delete_node(x);
						}
						else
						{
							delete_case_rebalance(x);
							delete_node(x);
						}
					}
				}
			}

			pointer create_node(const value_type &value)
			{
				pointer new_node = this->_alloc.allocate(1);
				this->_alloc.construct(new_node, value);
				return (new_node);
			}

			void delete_node(pointer node)
			{
				if (node->node_parent)
				{
					if (node->node_parent->node_left == node)
						node->node_parent->node_left = NULL;
					else
						node->node_parent->node_right = NULL;
				}
				this->_alloc.destroy(node);
				this->_alloc.deallocate(node, 1);
				if (node == this->_root)
				{
					this->_root = NULL;
					this->_node_ptr = NULL;
				}
			}

			void clearTree(pointer node)
			{
				if (!node)
					return;
				clearTree(node->node_left);
				clearTree(node->node_right);
				delete_node(node);
			}
	};
}
#endif
