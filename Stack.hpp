//
// Created by Cesar Erebus on 5/10/22.
//

#ifndef CEREBUS_FT_CONTAINERS_STACK_H
#define CEREBUS_FT_CONTAINERS_STACK_H

namespace ft {
    template<class T, class Cont >
    class Stack {
    private:
  //      _container
    public:
        typedef Cont container_type;

        Stack();

        //нужен ли здесь второй конструктор
        explicit Stack(const container_type &cont);


        //template functions
        bool empty();
        int size();
        //top
        //push();
        //pop();


    };
    template <class T, class Cont>
        bool operator==(const Stack<T, Cont>& lhs, const Stack<T, Cont>&);
  //  template
}



#endif //CEREBUS_FT_CONTAINERS_STACK_H
