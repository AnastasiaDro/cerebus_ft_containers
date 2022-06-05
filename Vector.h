//
// Created by Дрогунова Анастасия Викторовна on 05.06.2022.
//

#ifndef CEREBUS_FT_CONTAINERS_VECTOR_H
#define CEREBUS_FT_CONTAINERS_VECTOR_H

namespace ft {
    template<class T, class A> class vector {

    };
    template<class A>
            class vector<bool>


    template<class T, class A>
        bool operator==(const vector<T, А>& lhs , const vector<T, А>& rhs ){
            return (lhs.size() == rhs.size() && equal(lhs.begin(), lhs.end(), rhs.begin()));
        }
    template<class T , class A>
        bool operator!=(const vector<T, А>& lhs , const vector<T, А>& rhs ) {
            return ! (lhs == rhs);
        }
    template<class T , class A>
        bool operator<(const vector<T, А>& lhs , const vector<T, А>& rhs ) ;
    template<class T , class A>
        bool operator>(const vector<T, А>& lhs , const vector<T, А>& rhs ) ;
    template<class T , class A>
        bool operator<=(const vector<T, А>& lhs , const vector<T, А>& rhs ) ;
    template<class T , class A>
        bool operator>=(const vector<T, А>& lhs , const vector<T, А>& rhs ) ;

}

#endif //CEREBUS_FT_CONTAINERS_VECTOR_H
