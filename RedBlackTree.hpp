#ifndef REDBLACKTREE
#define REDBLACKTREE

#include "utils.hpp"
#include "bidirectional_iterator.hpp"

namespace ft {
    typedef enum {
        RED,
        BLACK
    } Color;

    template<typename T, class Compare, class Allocator>
    class RedBlackTree {
    public:
        typedef T value_type;
        typedef Compare compare_key;
        typedef size_t size_type;
        typedef Allocator alloc_type;
        typedef ft::Node<T> node_type;
        typedef node_type *node_ptr;
        typedef node_type &node_ref;

    private:
        compare_key compare;
        alloc_type alloc;
        node_ptr root;
        node_ptr node_p;
        size_type m_size;

    public:
        RedBlackTree(const compare_key key) : compare(key), alloc(alloc_type()), root(NULL), node_p(NULL), m_size(0) {}

        RedBlackTree(const RedBlackTree &another) : compare(another.compare), alloc(another.alloc), root(NULL),
                                                    node_p(NULL), m_size(another.m_size) {
            copyTree(&this->root, another.root, NULL, NULL);
            left_minimum();
        }


        RedBlackTree &operator=(const RedBlackTree &another) {
            if (this != &another) {
                clearTree(root);
                copyTree(&this->root, another.root, NULL, NULL);
                left_minimum();
                this->m_size = another.m_size;
            }
            return (*this);
        }

        ~RedBlackTree() {
            clearTree(this->root);
        }

        node_ptr get_root() const {
            return (root);
        }

        alloc_type get_alloc() const {
            return (alloc);
        }

        size_type get_size() const {
            return (m_size);
        }

        node_ptr get_node_ptr() const {
            return (node_p);
        }


        void erase(node_ptr pos) {
            if (!pos)
                return;
            if (pos == node_p)
                left_minimum();
            delete_tree(pos);
            --this->m_size;
        }

        void swap(RedBlackTree &another) {
            node_ptr new_node = root;
            root = another.root;
            another.root = new_node;
            size_type new_size = m_size;
            m_size = another.m_size;
            another.m_size = new_size;
            node_ptr new_node_ptr = node_p;
            node_p = another.node_p;
            another.node_p = new_node_ptr;
        }

        node_ptr search_node(const value_type &x) const {
            node_ptr ptr = root;
            while (ptr) {
                if (this->compare(ptr->value, x))
                    ptr = ptr->node_right;
                else if (this->compare(x, ptr->value))
                    ptr = ptr->node_left;
                else
                    break;
            }
            return (ptr);
        }

        bool erase(const value_type &x) {
            node_ptr ptr = search_node(x);
            while (ptr) {
                if (this->compare(ptr->value, x))
                    ptr = ptr->node_right;
                else if (this->compare(x, ptr->value))
                    ptr = ptr->node_left;
                else
                    break;
            }
            if (!ptr)
                return (0);
            if (ptr == node_p)
                left_minimum();
            delete_tree(ptr);
            --this->m_size;
            return (1);
        }

        node_ptr insert(node_ptr position, const value_type &val) {
            bool b_insert;
            if (!root || !position)
                return (insert(val, &b_insert));

            node_ptr copy_position = position;
            position = next(position);

            if (this->compare(copy_position->value, val) && (!position || this->compare(val, position->value))) {
                node_ptr new_node = create_node(val);
                if (!copy_position->node_right)
                    copy_position->node_right = new_node;
                else {
                    node_ptr tmp = copy_position->node_right;
                    while (tmp->node_left)
                        tmp = tmp->node_left;
                    if (node_p == tmp)
                        node_p = new_node;
                    tmp->node_left = new_node;
                }
                if (this->m_size == 0)
                    node_p = new_node;
                insert_case1(new_node);
                ++this->m_size;
                return (new_node);
            } else
                return (insert(val, &b_insert));
            return (NULL);
        }

        node_ptr insert(const value_type &x, bool *b_insert) {
            node_ptr ptr = root;
            node_ptr new_node = create_node(x);
            while (ptr) {
                if (compare(x, ptr->value)) {
                    if (ptr->node_left)
                        ptr = ptr->node_left;
                    else {
                        new_node->node_parent = ptr;
                        ptr->node_left = new_node;
                        if (this->node_p == ptr)
                            this->node_p = new_node;
                        break;
                    }
                } else if (this->compare(ptr->value, x)) {
                    if (ptr->node_right)
                        ptr = ptr->node_right;
                    else {
                        new_node->node_parent = ptr;
                        ptr->node_right = new_node;
                        break;
                    }
                } else {
                    delete_node(new_node);
                    *b_insert = false;
                    return (ptr);
                }
            }
            if (m_size == 0)
                node_p = new_node;
            insert_case1(new_node);
            ++this->m_size;
            *b_insert = true;
            return (new_node);
        }

        node_ptr next(node_ptr pos) {
            if (!pos) {
                pos = root;
                if (pos) {
                    while (pos->node_left)
                        pos = pos->node_left;
                }
                return (pos);
            }
            if (pos->node_right) {
                pos = pos->node_right;
                while (pos->node_left)
                    pos = pos->node_left;
            } else {
                while (pos == pos->node_parent->node_right && pos->node_parent)
                    pos = pos->node_parent;
                pos = pos->node_parent;
            }
            return (pos);
        }

        void clear() {
            m_size = 0;
            clearTree(this->root);
        }


        void upper(const value_type &x, node_ptr m_node, node_ptr *another_node) const {
            if (*another_node || !m_node)
                return;
            upper(x, m_node->node_left, another_node);
            if (*another_node)
                return;
            if (compare(x, m_node->value))
                *another_node = m_node;
            upper(x, m_node->node_right, another_node);
        }

        void lower(const value_type &x, node_ptr m_node, node_ptr *another_node) const {
            if (*another_node || !m_node)
                return;
            lower(x, m_node->node_left, another_node);
            if (*another_node)
                return;
            if (!compare(m_node->value, x))
                *another_node = m_node;
            lower(x, m_node->node_right, another_node);
        }

    private:
        void copyTree(node_ptr *lnode, node_ptr rnode, node_ptr lpar, node_ptr rpar) {
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


        node_ptr minimum(node_ptr more_left) {
            while (more_left->node_left != NULL)
                more_left = more_left->node_left;
            return (more_left);
        }

        void left_minimum() {
            if (!node_p) {
                node_p = root;
                if (node_p) {
                    while (node_p->node_left)
                        node_p = node_p->node_left;
                }
                return;
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


        node_ptr get_grandparent(node_ptr x) {
            if (x->node_parent != NULL)
                return (x->node_parent->node_parent);
            return (NULL);
        }

        node_ptr get_uncle(node_ptr ptr) {
            node_ptr old = get_grandparent(ptr);
            if (old == NULL)
                return (NULL);
            return (ptr->node_parent == old->node_left) ? (old->node_right) : (old->node_left);
        }

        void rotateRight(node_ptr ptr) {
            node_ptr piv = ptr->node_left;
            if (ptr == root)
                root = piv;
            piv->node_parent = ptr->node_parent;
            if (piv->node_parent != NULL) {
                if (ptr->node_parent->node_left == ptr)
                    ptr->node_parent->node_left = piv;
                else
                    ptr->node_parent->node_right = piv;
            }
            ptr->node_left = piv->node_right;
            if (ptr->node_left != NULL)
                piv->node_right->node_parent = ptr;
            ptr->node_parent = piv;
            piv->node_right = ptr;
        }

        void rotateLeft(node_ptr ptr) {
            node_ptr piv = ptr->node_right;

            if (ptr == root)
                root = piv;
            piv->node_parent = ptr->node_parent;
            if (piv->node_parent != NULL) {
                if (ptr->node_parent->node_left == ptr)
                    ptr->node_parent->node_left = piv;
                else
                    ptr->node_parent->node_right = piv;
            }
            ptr->node_right = piv->node_left;
            if (ptr->node_right != NULL)
                piv->node_left->node_parent = ptr;
            ptr->node_parent = piv;
            piv->node_left = ptr;
        }

        void insert_case1(node_ptr ptr) {
            if (ptr->node_parent == NULL) {
                this->root = ptr;
                ptr->red = BLACK;
            } else
                insert_case2(ptr);
        }

        void insert_case2(node_ptr ptr) {
            if (ptr->node_parent->red == RED)
                insert_case3(ptr);
        }

        void insert_case3(node_ptr ptr) {
            node_ptr new_uncle = get_uncle(ptr);
            if (new_uncle != NULL && new_uncle->red == RED) {
                ptr->node_parent->red = BLACK;
                new_uncle->red = BLACK;
                node_ptr old = get_grandparent(ptr);
                old->red = RED;
                insert_case1(old);
            } else
                insert_case4(ptr);
        }

        void insert_case4(node_ptr ptr) {
            node_ptr old = get_grandparent(ptr);
            if ((ptr == ptr->node_parent->node_right) && (ptr->node_parent == old->node_left)) {
                rotateLeft(ptr->node_parent);
                ptr = ptr->node_left;
            } else if ((ptr == ptr->node_parent->node_left) && (ptr->node_parent == old->node_right)) {
                rotateRight(ptr->node_parent);
                ptr = ptr->node_right;
            }
            insert_case5(ptr);
        }

        void insert_case5(node_ptr ptr) {
            node_ptr old = get_grandparent(ptr);

            ptr->node_parent->red = BLACK;
            old->red = RED;
            if ((ptr == ptr->node_parent->node_left) && (ptr->node_parent == old->node_left))
                rotateRight(old);
            else
                rotateLeft(old);
        }


        node_ptr get_left_max(node_ptr ptr) {
            ptr = ptr->node_left;
            if (ptr) {
                while (ptr->node_right)
                    ptr = ptr->node_right;
            }
            return (ptr);
        }

        node_ptr get_right_min(node_ptr ptr) {
            ptr = ptr->node_right;
            if (ptr) {
                while (ptr->node_left)
                    ptr = ptr->node_left;
            }
            return (ptr);
        }

        node_ptr get_sibling(node_ptr ptr) {
            return (ptr == ptr->node_parent->node_left) ? (ptr->node_parent->node_right)
                                                        : (ptr->node_parent->node_left);
        }

        node_ptr get_search_for_swap(node_ptr ptr) {
            node_ptr tmp = get_left_max(ptr);
            if (!tmp)
                tmp = get_right_min(ptr);
            return (tmp);
        }

        void swap_nodes(node_ptr prev, const node_ptr next) {
            if (root == prev)
                root = next;
            if (prev->node_parent) {
                if (prev->node_parent->node_left == prev)
                    prev->node_parent->node_left = next;
                else
                    prev->node_parent->node_right = next;
            }
            if (next->node_parent->node_left == next)
                next->node_parent->node_left = prev;
            else
                next->node_parent->node_right = prev;
            node_ptr node_new = prev->node_parent;
            prev->node_parent = next->node_parent;
            next->node_parent = node_new;
            if (prev->node_left)
                prev->node_left->node_parent = next;
            if (next->node_left)
                next->node_left->node_parent = prev;

            node_new = prev->node_left;
            prev->node_left = next->node_left;
            next->node_left = node_new;
            if (prev->node_right)
                prev->node_right->node_parent = next;
            if (next->node_right)
                next->node_right->node_parent = prev;

            node_new = prev->node_right;
            prev->node_right = next->node_right;
            next->node_right = node_new;
            bool new_color = next->red;
            next->red = prev->red;
            prev->red = new_color;
        }

        void delete_case_rebalance(node_ptr ptr) {
            node_ptr s = get_sibling(ptr);
            if (!s)
                return;
            if (ptr == ptr->node_parent->node_left) {
                if (s->red == BLACK) {
                    if (s->node_right && s->node_right->red == RED)
                        del_case_left_rotate(get_sibling(ptr), ptr);
                    else if (s->node_left && s->node_left->red == RED) {
                        s->red = RED;
                        s->node_left->red = BLACK;
                        rotateRight(s);
                        del_case_left_rotate(get_sibling(ptr), ptr);
                    } else {
                        s->red = RED;
                        if (ptr->node_parent->red == RED)
                            ptr->node_parent->red = BLACK;
                        else if (ptr->node_parent != this->root)
                            delete_case_rebalance(ptr->node_parent);
                    }
                } else {
                    s->node_parent->red = RED;
                    s->red = BLACK;
                    rotateLeft(s->node_parent);
                    if (s->node_left->node_right) {
                        s->node_left->red = BLACK;
                        s->node_left->node_right->red = RED;
                    }
                    if (s != this->root)
                        delete_case_rebalance(s);
                }
            } else {
                if (s->red == BLACK) {
                    if (s->node_left && s->node_left->red == RED)
                        del_case_right_rotate(get_sibling(ptr), ptr);
                    else if (s->node_right && s->node_right->red == RED) {
                        s->red = RED;
                        s->node_right->red = BLACK;
                        rotateLeft(s);
                        del_case_right_rotate(get_sibling(ptr), ptr);
                    } else {
                        s->red = RED;
                        if (ptr->node_parent->red == RED)
                            ptr->node_parent->red = BLACK;
                        else if (ptr->node_parent != this->root)
                            delete_case_rebalance(ptr->node_parent);
                    }
                } else {
                    s->node_parent->red = RED;
                    s->red = BLACK;
                    rotateRight(s->node_parent);
                    if (s->node_right->node_left) {
                        s->node_right->red = BLACK;
                        s->node_right->node_left->red = RED;
                    }
                    if (s != this->root)
                        delete_case_rebalance(s);
                }
            }
        }

        void del_case_right_rotate(node_ptr a, node_ptr b) {
            a->red = b->node_parent->red;
            b->node_parent->red = BLACK;
            a->node_left->red = BLACK;
            rotateRight(b->node_parent);
        }

        void del_case_left_rotate(node_ptr a, node_ptr b) {
            a->red = b->node_parent->red;
            b->node_parent->red = BLACK;
            a->node_right->red = BLACK;
            rotateLeft(b->node_parent);
        }


        void delete_tree(node_ptr ptr) {
            node_ptr child = get_search_for_swap(ptr);
            if (!child) {
                if (ptr->red == RED)
                    delete_node(ptr);
                else {
                    if (ptr != root)
                        delete_case_rebalance(ptr);
                    delete_node(ptr);
                }
            } else {
                swap_nodes(ptr, child);
                if (ptr->red == RED)
                    delete_node(ptr);
                else {
                    if (ptr->node_left) {
                        swap_nodes(ptr, ptr->node_left);
                        delete_node(ptr);
                    } else if (ptr->node_right) {
                        swap_nodes(ptr, ptr->node_right);
                        delete_node(ptr);
                    } else {
                        delete_case_rebalance(ptr);
                        delete_node(ptr);
                    }
                }
            }
        }

        node_ptr create_node(const value_type &x) {
            node_ptr new_node = this->alloc.allocate(1);
            this->alloc.construct(new_node, x);
            return (new_node);
        }

        void delete_node(node_ptr ptr) {
            if (ptr->node_parent) {
                if (ptr->node_parent->node_left == ptr)
                    ptr->node_parent->node_left = NULL;
                else
                    ptr->node_parent->node_right = NULL;
            }
            alloc.destroy(ptr);
            alloc.deallocate(ptr, 1);
            if (ptr == root) {
                root = NULL;
                node_p = NULL;
            }
        }

        void clearTree(node_ptr ptr) {
            if (!ptr)
                return;
            clearTree(ptr->node_left);
            clearTree(ptr->node_right);
            delete_node(ptr);
        }
    };
}

#endif
