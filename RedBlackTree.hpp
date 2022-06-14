#ifndef REDBLACKTREE
#define REDBLACKTREE

#include "utils.hpp"
#include "bidirectional_iterator.hpp"

namespace ft
{
	typedef enum {
		RED,
		BLACK
	} color;

	template <typename T, class Compare, class Alloc>
	class RedBlackTree {
		public:
			typedef T				value_type;
			typedef Compare			compare_key;
			typedef size_t			size_type;
			typedef Alloc			allocator_type;
			typedef ft::Node<T>		node_type;
			typedef node_type*		pointer;
			typedef node_type&		reference;

		private:
			compare_key		compare;
			allocator_type	alloc;
			pointer			root;
			pointer			node_p;
			size_type		tree_size;

		public:
			RedBlackTree(const compare_key cmp) : compare(cmp), alloc(allocator_type()), root(NULL), node_p(NULL), tree_size(0) {}

			RedBlackTree(const RedBlackTree &other) : compare(other.compare), alloc(other.alloc), root(NULL), node_p(NULL), tree_size(other.tree_size){
				copyTree(&this->root, other.root, NULL, NULL);
				left_minimum();
			}

			~RedBlackTree() {
				clearTree(root);
			}

			RedBlackTree &operator=(const RedBlackTree &other)
			{
				if (this != &other)
				{
					clearTree(root);
					copyTree(&this->root, other.root, NULL, NULL);
					left_minimum();
					tree_size = other.tree_size;
				}
				return (*this);
			}

			allocator_type getalloc() const {
				return (alloc);
			}

			pointer getroot() const {
				return (root);
			}

			pointer getnode_p() const {
				return (node_p);
			}

			size_type get_size() const {
				return (tree_size);
			}

			void swap (RedBlackTree &other) {
				pointer new_node = root;
				root = other.root;
				other.root = new_node;
				size_type new_size = tree_size;
				tree_size = other.tree_size;
				other.tree_size = new_size;
				pointer newnode_p = node_p;
				node_p = other.node_p;
				other.node_p = newnode_p;
			}

			void erase(pointer position) {
				if (!position)
					return;
				if (position == node_p)
					left_minimum();
				delete_tree(position);
				tree_size--;
			}

			pointer search_node(const value_type &value) const {
				pointer search = root;
				while (search) {
					if (compare(search->value, value))
						search = search->node_right;
					else if (compare(value, search->value))
						search = search->node_left;
					else
						break;
				}
				return (search);
			}

			bool erase(const value_type &value) {
				pointer search = search_node(value);
				while (search) {
					if (compare(search->value, value))
						search = search->node_right;
					else if (compare(value, search->value))
						search = search->node_left;
					else
						break;
				}
				if (!search)
					return (0);
				if (search == node_p)
					left_minimum();
				delete_tree(search);
				tree_size--;
				return (1);
			}

			pointer next(pointer position) {
				if (!position) {
					position = root;
					if (position) {
						while (position->node_left)
							position = position->node_left;
					}
					return (position);
				}
				if (position->node_right) {
					position = position->node_right;
					while (position->node_left)
						position = position->node_left;
				} else {
					while (position == position->node_parent->node_right && position->node_parent)
						position = position->node_parent;
					position = position->node_parent;
				}
				return (position);
			}

			pointer insert(pointer position, const value_type& x) {
				bool b_insert;
				if (!root || !position)
					return (insert(x, &b_insert));

				pointer copy_position = position;
				position = next(position);

				if (compare(copy_position->value, x) && (!position || compare(x, position->value))) {
					pointer new_node = create_node(x);
					if (!copy_position->node_right)
						copy_position->node_right = new_node;
					else {
						pointer tmp = copy_position->node_right;
						while (tmp->node_left)
							tmp = tmp->node_left;
						if (node_p == tmp)
							node_p = new_node;
						tmp->node_left = new_node;
					}
					if (tree_size == 0)
						node_p = new_node;
					insert_case1(new_node);
					tree_size++;
					return (new_node);
				}
				else
					return (insert(x, &b_insert));
			}

			pointer insert(const value_type& x, bool *b_insert) {
				pointer p = root;
				pointer new_node = create_node(x);
				while(p) {
					if (compare(x, p->value)) {
						if (p->node_left)
							p = p->node_left;
						else {
							new_node->node_parent = p;
							p->node_left = new_node;
							if (node_p == p)
								node_p = new_node;
							break;
						}
					}
					else if (compare(p->value, x))
					{
						if (p->node_right)
							p = p->node_right;
						else {
							new_node->node_parent = p;
							p->node_right = new_node;
							break;
						}
					}
					else {
						delete_node(new_node);
						*b_insert = false;
						return (p);
					}
				}
				if (tree_size == 0)
					node_p = new_node;
				insert_case1(new_node);
				tree_size++;
				*b_insert = true;
				return (new_node);
			}

			void clear() {
				tree_size = 0;
				clearTree(root);
			}

			void lower(const value_type &val, pointer node, pointer *other_node) const {
				if (*other_node || !node)
					return ;
				lower(val, node->node_left, other_node);
				if (*other_node)
					return ;
				if (!compare(node->value, val))
					*other_node = node;
				lower(val, node->node_right, other_node);
			}

			void upper(const value_type &val, pointer node, pointer *other_node) const {
				if (*other_node || !node)
					return ;
				upper(val, node->node_left, other_node);
				if (*other_node)
					return ;
				if (compare(val, node->value))
					*other_node = node;
				upper(val, node->node_right, other_node);
			}

		private:
			void copyTree(pointer *lnode, pointer rnode, pointer lpar, pointer rpar) {
				if (!rnode)
					return;
				*lnode = create_node(rnode->value);
				(*lnode)->node_parent = lpar;
				if (rpar) {
					if (rpar->node_right == rnode)
						lpar->node_right = *lnode;
					else
						lpar->node_left = *lnode;
				}
				copyTree(&((*lnode)->node_left), rnode->node_left, *lnode, rnode);
				copyTree(&((*lnode)->node_right), rnode->node_right, *lnode, rnode);
			}

			void left_minimum() {
				if (!node_p)
				{
					node_p = root;
					if (node_p) {
						while (node_p->node_left)
							node_p = node_p->node_left;
					}
					return ;
				}
                if (node_p->node_right) {
					node_p = node_p->node_right;
					while (node_p->node_left)
						node_p = node_p->node_left;
				} else {
					while (node_p->node_parent && node_p == node_p->node_parent->node_right)
						node_p = node_p->node_parent;
					node_p = node_p->node_parent;
				}
			}

			pointer minimum(pointer left_more) {
				while (left_more->node_left != NULL)
					left_more = left_more->node_left;
				return (left_more);
			}

			pointer get_grandparent(pointer x) {
				if (x->node_parent != NULL)
					return (x->node_parent->node_parent);
				return (NULL);
			}

			pointer get_uncle(pointer x) {
				pointer old = get_grandparent(x);
				if (old == NULL)
					return (NULL);
				if (x->node_parent == old->node_left)
					return (old->node_right);
				else
					return (old->node_left);
			}

			void rotateRight(pointer x) {
				pointer pivot = x->node_left;
				if (x == root)
					root = pivot;
				pivot->node_parent = x->node_parent;
				if (pivot->node_parent != NULL) {
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

			void rotateLeft(pointer x) {
				pointer pivot = x->node_right;

				if (x == root)
					root = pivot;
				pivot->node_parent = x->node_parent;
				if (pivot->node_parent != NULL) {
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

			void insert_case1(pointer x) {
				if (x->node_parent == NULL) {
					root = x;
					x->red = BLACK;
				}
				else
					insert_case2(x);
			}

			void insert_case2(pointer x) {
				if (x->node_parent->red == RED)
					insert_case3(x);
			}

			void insert_case3(pointer x) {
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

			void insert_case4(pointer x) {
				pointer old = get_grandparent(x);

				if ((x == x->node_parent->node_right) && (x->node_parent == old->node_left)) {
					rotateLeft(x->node_parent);
					x = x->node_left;
				}
				else if ((x == x->node_parent->node_left) && (x->node_parent == old->node_right)) {
					rotateRight(x->node_parent);
					x = x->node_right;
				}
				insert_case5(x);
			}

			void insert_case5(pointer x) {
				pointer old = get_grandparent(x);

				x->node_parent->red = BLACK;
				old->red = RED;
				if ((x == x->node_parent->node_left) && (x->node_parent == old->node_left))
					rotateRight(old);
				else
					rotateLeft(old);
			}

			pointer get_right_min(pointer x) {
				x = x->node_right;
				if (x) {
					while (x->node_left)
						x = x->node_left;
				}
				return (x);
			}

			pointer get_left_max(pointer x) {
				x = x->node_left;
                if (x) {
                    while (x->node_right)
                        x = x->node_right;
                }
				return (x);
			}

			pointer get_sibling(pointer x) {
				if (x == x->node_parent->node_left)
					return (x->node_parent->node_right);
				else
					return (x->node_parent->node_left);
			}

			pointer get_search_for_swap(pointer x) {
				pointer tmp = get_left_max(x);
				if(!tmp)
					tmp = get_right_min(x);
				return (tmp);
			}

			void swap_nodes(pointer before, const pointer after) {
				if (root == before)
					root = after;
				if (before->node_parent) {
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

			void delete_case_rebalance(pointer x) {
				pointer s = get_sibling(x);

				if (!s)
					return;
				if (x == x->node_parent->node_left) {
					if (s->red == BLACK) {
						if (s->node_right && s->node_right->red == RED)
							del_case_left_rotate(get_sibling(x), x);
						else if (s->node_left && s->node_left->red == RED) {
							s->red = RED;
							s->node_left->red = BLACK;
							rotateRight(s);
							del_case_left_rotate(get_sibling(x), x);
						} else {
							s->red = RED;
							if (x->node_parent->red == RED)
								x->node_parent->red = BLACK;
							else if (x->node_parent != this->root)
								delete_case_rebalance(x->node_parent);
						}
					} else {
						s->node_parent->red = RED;
						s->red = BLACK;
						rotateLeft(s->node_parent);

						if (s->node_left->node_right) {
							s->node_left->red = BLACK;
							s->node_left->node_right->red = RED;
						}
						if (s != root)
							delete_case_rebalance(s);
					}
				} else {
					if (s->red == BLACK) {
						if (s->node_left && s->node_left->red == RED)
							del_case_right_rotate(get_sibling(x), x);
						else if (s->node_right && s->node_right->red == RED) {
							s->red = RED;
							s->node_right->red = BLACK;
							rotateLeft(s);
							del_case_right_rotate(get_sibling(x), x);
						} else {
							s->red = RED;
							if (x->node_parent->red == RED)
								x->node_parent->red = BLACK;
							else if (x->node_parent != root)
								delete_case_rebalance(x->node_parent);
						}
					} else {
						s->node_parent->red = RED;
						s->red = BLACK;
						rotateRight(s->node_parent);

						if (s->node_right->node_left) {
							s->node_right->red = BLACK;
							s->node_right->node_left->red = RED;
						}
						if (s != root)
							delete_case_rebalance(s);
					}
				}
			}

			void del_case_left_rotate(pointer s, pointer x) {
				s->red = x->node_parent->red;
				x->node_parent->red = BLACK;
				s->node_right->red = BLACK;
				rotateLeft(x->node_parent);
			}

			void del_case_right_rotate(pointer s, pointer x) {
				s->red = x->node_parent->red;
				x->node_parent->red = BLACK;
				s->node_left->red = BLACK;
				rotateRight(x->node_parent);
			}

			void delete_tree(pointer x) {
				pointer child = get_search_for_swap(x);
				if (!child) {
					if (x->red == RED)
						delete_node(x);
					else {
						if (x != root)
							delete_case_rebalance(x);
						delete_node(x);
					}
				} else {
					swap_nodes(x, child);
					if (x->red == RED)
						delete_node(x);
					else {
						if (x->node_left) {
							swap_nodes(x, x->node_left);
							delete_node(x);
						} else if (x->node_right) {
							swap_nodes(x, x->node_right);
							delete_node(x);
						} else {
							delete_case_rebalance(x);
							delete_node(x);
						}
					}
				}
			}

			pointer create_node(const value_type &x) {
				pointer new_node = alloc.allocate(1);
				alloc.construct(new_node, x);
				return (new_node);
			}

			void delete_node(pointer node) {
				if (node->node_parent) {
					if (node->node_parent->node_left == node)
						node->node_parent->node_left = NULL;
					else
						node->node_parent->node_right = NULL;
				}
				alloc.destroy(node);
				alloc.deallocate(node, 1);
				if (node == root) {
					root = NULL;
					node_p = NULL;
				}
			}

			void clearTree(pointer node) {
				if (!node)
					return;
				clearTree(node->node_left);
				clearTree(node->node_right);
				delete_node(node);
			}
	};
}
#endif
