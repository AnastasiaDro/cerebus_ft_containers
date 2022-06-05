//
// Created by Cesar Erebus on 5/10/22.
//

#ifndef CEREBUS_FT_CONTAINERS_STACK_H
#define CEREBUS_FT_CONTAINERS_STACK_H
#include <vector>


namespace ft {
    template<class T, class Container = std::vector<T> >
            class stack {
    protected:
        Container _container;
    public:
        typedef Container container_type;
        typedef typename Container::value_type value_type;
        typedef typename Container::size_type size_type;

        //нужен ли здесь второй конструктор
        explicit stack(const container_type &cont = container_type()) : _container(cont) {}

        //template functions
        bool empty() const {
            return _container.empty();
        }
        size_type size() const {
            return _container.size();
        }

        const value_type& top ( ) const {
            return _container.back();
        }

        value_type &top() {
           return _container.back();
        }
        void push(const value_type& x) {
            _container.push_back(x);
        }

        void pop() {
            _container.pop_back();
        }

        virtual ~stack() {}
    };

    template <class T, class Container>
        bool operator==(const stack<T, Container>& lhs, const stack<T, Container>&rhs) {
            return (lhs.size() == rhs.size() && equal(lhs.begin(), lhs.end(), rhs.begin()));
        }

    template <class T, class Container>
        bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>&rhs) {
            return !(lhs == rhs);
        }

    template <class T, class Container>
        bool operator<(const stack<T, Container>& lhs, const stack <T, Container>&);
    template <class T, class Container>
        bool operator>(const stack<T, Container>& lhs, const stack <T, Container>&);
    template <class T, class Container>
        bool operator<=(const stack<T, Container>& lhs, const stack <T, Container>&);
    template <class T, class Container>
        bool operator>=(const stack<T, Container>& lhs, const stack <T, Container>&);
  //  template
}



#endif //CEREBUS_FT_CONTAINERS_STACK_H
