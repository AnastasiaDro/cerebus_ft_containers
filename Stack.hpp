//
// Created by Cesar Erebus on 5/10/22.
//

#ifndef FT_CONTAINERS_STACK_H
#define FT_CONTAINERS_STACK_H
#include "Vector.hpp"


namespace ft {
    template<class T, class Container = ft::vector<T> >
            class stack {
    protected:
        Container container;
    public:
        typedef Container container_type;
        typedef typename Container::value_type value_type;
        typedef typename Container::size_type size_type;

        //нужен ли здесь второй конструктор
        explicit stack(const container_type &cont = container_type()) : container(cont) {}

        //template functions
        bool empty() const {
            return container.empty();
        }
        size_type size() const {
            return container.size();
        }

        const value_type& top ( ) const {
            return container.back();
        }

        value_type &top() {
           return container.back();
        }

        void push(const value_type& x) {
            container.push_back(x);
        }

        void pop() {
            container.pop_back();
        }

        template<class T1, class T2>
        friend bool operator==(const stack<T1, T2> &lhs, const stack<T1, T2> &rhs);

        template<class T1, class T2>
        friend bool operator!=(const stack<T1, T2> &lhs, const stack<T1, T2> &rhs);

        template<class T1, class T2>
        friend bool operator<(const stack<T1, T2> &lhs, const stack<T1, T2> &rhs);

        template<class T1, class T2>
        friend bool operator<=(const stack<T1, T2> &lhs, const stack<T1, T2> &rhs);

        template<class T1, class T2>
        friend bool operator>(const stack<T1, T2> &lhs, const stack<T1, T2> &rhs);

        template<class T1, class T2>
        friend bool operator>=(const stack<T1, T2> &lhs, const stack<T1, T2> &rhs);

        virtual ~stack() {}
    };

    template <class T, class Container>
        bool operator==(const stack<T, Container>& lhs, const stack<T, Container>&rhs) {
            return (lhs == rhs);
        }

    template <class T, class Container>
        bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>&rhs) {
            return (lhs != rhs);
        }

    template<class T, class Container>
    bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
        return (lhs.container < rhs.container);
    }

    template<class T, class Container>
    bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
        return (lhs.container > rhs.container);
    }

    template<class T, class Container>
    bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
        return (lhs.container <= rhs.container);
    }

    template <class T, class Container>
    bool operator>=(const stack<T, Container>& lhs, const stack <T, Container>&rhs) {
        return (lhs.container >= rhs.container);
    }
}

#endif
