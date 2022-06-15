#include <iostream>
#include "vector.hpp"
#include "stack.hpp"
#include "map.hpp"
#include <map>
#include <vector>
#include <stack>
#include <iterator>

int main() {

    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "VECTOR" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::vector<int> stdVector;
    std::stack<int, std::vector<int> > stackV;

    ft::vector<int> myVector;
    ft::stack<int> myStack;
    stdVector.push_back(22); stdVector.push_back(23);
    stackV.push(33); stackV.push(34);
    myVector.push_back(22);myVector.push_back(23);
    myStack.push(33); myStack.push(34);
    std::cout << "Push back 2  + size " << "std Vector = " << stdVector.size() << std::endl;
    std::cout << "Push back 2 + size " << "my Vector  = " << myVector.size() << std::endl;
    std::cout << "Max.size " << "std Vector = " << stdVector.size() << std::endl;
    std::cout << "Max.size " << "my Vector  = " << myVector.size() << std::endl;

    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "CONSTRUCTOR" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    ft::vector<int> empty(10, 4);
    ft::vector<int> empty1(empty);
    std::cout << "Construct1 " << "empty   = " << empty.size() << std::endl;
    std::cout << "Construct2 " << "empty1  = " << empty1.size() << std::endl;
    ft::vector<int> test3;
    test3 = empty;
    std::cout << "Construct3 " << "test3  = " << test3.size() << std::endl;
    ft::vector<int> test2(test3.begin(), test3.end());
    std::cout << "Construct4 " << "test2  = " << test2.size() << std::endl;
    try { ft::vector<int> tmp5(-1, -1); }
    catch (std::exception &e) { myVector.push_back(1); }

    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "INSERT" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << myVector.size() << " myVector.size()" << std::endl;
    std::cout << *myVector.insert(myVector.end(), 9999) << " myVector.insert(myVector.end(), 9999) " << std::endl;
    std::cout << myVector.size() << " myVector.size()" << std::endl;
    myVector.insert(myVector.end(), 2, 123);
    std::cout << *(myVector.end() - 2) << " *(myVector.end() - 2)" << std::endl;
    std::cout << *(myVector.end() - 1) << " *(myVector.end() - 1)" << std::endl;
    std::cout << myVector.size() << " myVector.size() =+ 2" << std::endl << std::endl;

    myVector.clear();
    myVector.insert(myVector.end(),42);
    myVector.insert(myVector.begin(), 2, 21);
    myVector.insert(myVector.end() - 2,42);

    std::cout << *(myVector.begin()) << " TEST " << std::endl;
    std::cout << *(myVector.end() - 2) << " TEST " << std::endl;
    std::cout << *(myVector.end() - 1) << " TEST *(myVector.end() - 1)" << std::endl;
    std::cout << myVector.size() << " myVector.size()" << std::endl << std::endl;

    myVector.insert(myVector.end(), stdVector.begin(), stdVector.begin() + 2);
    stdVector.clear();
    std::cout << stdVector.size() << " stdVector.size() " << std::endl;
    std::cout << *(myVector.end() - 2) << " *(myVector.end() - 2)" << std::endl;
    std::cout << *(myVector.end() - 1) << " *(myVector.end() - 1)" << std::endl;
    std::cout << myVector.size() << " myVector.size() =+ 2" << std::endl;


    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "ASSIGN" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << stdVector.size() << " stdVector.size() " << std::endl;
    stdVector.assign(0, 20);
    std::cout << stdVector.size() << " stdVector.size() " << std::endl;
    std::cout << myVector.size() << " myVector.size()" << std::endl;
    myVector.assign(2, 20);
    std::cout << myVector.size() << " myVector.size()" << std::endl;

    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "ERASE" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << myVector.size() << " myVector.size()" << std::endl;
    std::cout << *(myVector.erase(myVector.begin() , myVector.begin() + 1)) << " myVector.erase" << std::endl;
    std::cout << myVector.size() << " myVector.size()" << std::endl;
    std::cout << *myVector.erase(myVector.end() - 1) << " myVector.erase" << std::endl;
    std::cout << myVector.size() << " myVector.size()" << std::endl;

    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "ERASE BIG DATA" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    for (int i = 0; i < 990000; ++i)
        myVector.push_back(i);
    myVector.push_back(*(myVector.erase(myVector.begin() + 8000, myVector.end() - 15000)));
    std::cout << "Erase big " << "myVector  = " << myVector.size() << std::endl;

    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "SWAP" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << myVector.size() << " myVector.size()" << std::endl;
    ft::vector<int> some;
    myVector.swap(some);
    std::cout << myVector.size() << " myVector.size()" << std::endl;

    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "SIZE VECTOR" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << myVector.size() << " myVector.size()" << std::endl;
    std::cout << stdVector.size() << " stdVector.size()" << std::endl;

    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "VECTOR TOP" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << stackV.top() << " stackVector.top()" << std::endl;
    std::cout << myStack.top() << " myStack.top()" << std::endl;

    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "VECTOR RESIZE" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << stdVector.size() << " stdVector.size()" << std::endl;
    stdVector.resize(3);
    myVector.resize(3);
    std::cout << stdVector.size() << " stdVector.size()" << std::endl;

    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "ITERATOR" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::vector<int>::iterator it = stdVector.begin();
    ft::vector<int>::iterator myIt = myVector.begin();
    std::cout << *myIt << " myIt" << std::endl;
    std::cout << *it << " it" << std::endl;

    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "INCREMENT DECREMENT" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << *myIt++ << " myIt postfix ++" << std::endl;
    std::cout << *++myIt << " myIt prefix ++" << std::endl;
    std::cout << *myIt-- << " myIt postfix --" << std::endl;
    std::cout << *--myIt << " myIt prefix --" << std::endl;

    /* const vs noconst */
    ft::vector<int>::const_iterator myConstIt = myVector.begin();
    ft::vector<int>::const_iterator myConstIt2(myVector.begin());
    std::vector<int>::const_iterator realConst(it + 2);
    myConstIt = myIt;

    /*     *myConstIt = 123; */
    std::cout << (myConstIt == myIt) << " - (myConstIt == myIt)" << std::endl;
    std::cout << (myConstIt2 != myIt) << " - (myConstIt2 != myIt)" << std::endl;
    std::cout << ((myIt + 2) - myConstIt2) << " - ((myIt + 2) - myConstIt2)" << std::endl;

    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "REVERSE ITERATOR" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    ft::vector<int>::reverse_iterator myRevIt = myVector.rbegin();
    for (int i = 0; i < 5; ++i)
        myRevIt[i] = (5 - i) * 5;
    stdVector.push_back(26);
    std::vector<int>::reverse_iterator revIt = stdVector.rbegin();
    for (int i = 0; i < 5; ++i)
        revIt[i] = (5 - i) * 5;
    std::cout << stdVector.size() << " stdVector.size() " << std::endl;
    std::cout << myVector.size() << " myVector.size()" << std::endl;
    revIt = revIt + 5;
    myRevIt = myRevIt + 5;
    myRevIt = 1 + myRevIt;
    revIt = 1 + revIt;
    myRevIt = myRevIt - 4;
    revIt = revIt - 4;
    std::cout << *(revIt += 2) << std::endl;
    std::cout << *(myRevIt += 2) << std::endl;
    std::cout << *(revIt -= 1) << std::endl;
    std::cout << *(myRevIt -= 1) << std::endl;
    ft::vector<int>::const_reverse_iterator myConstRevIt(myVector.rbegin());
    std::cout << *revIt << " - *revIt" << std::endl;
    std::cout << (myRevIt < myConstRevIt) << " - (myRevIt == myConstRevIt)" << std::endl;

    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "MAP" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::map<int, std::string> stdMap;
    ft::map<int, std::string> myMap;

    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "MAP UPPER AND LOWER BOUND" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::map<int,int> mymmap;
    std::map<int,int>::iterator itloww,itupp;
    mymmap[11]=11;
    mymmap[22]=22;
    mymmap[33]=33;
    mymmap[44]=44;
    mymmap[55]=55;
    itloww=mymmap.lower_bound (53);
    itupp=mymmap.upper_bound (55);
    if (itloww != mymmap.end())
        std::cout << itloww->first << " => " << " itlowww " << '\n';
    if (itupp != mymmap.end())
        std::cout << itupp->first << " => " << " itupppp" << '\n';
    ft::map<int,int> mymap;
    ft::map<int,int>::iterator itlow,itup;
    mymap[11]=11;
    mymap[22]=22;
    mymap[33]=33;
    mymap[44]=44;
    mymap[55]=55;
    itlow=mymap.lower_bound (56);
    itup=mymap.upper_bound (54);
    if (itlow != mymap.end())
        std::cout << itlow->first << " => " << " itlow 12" << '\n';
    std::cout << itup->first << " => " << "itup" << '\n';
    for (ft::map<int,int>::iterator itlow = mymap.begin(); itlow != mymap.end(); ++itlow)
        std::cout << itlow->first << " => " << " itlow 12" << '\n';
    std::pair<int, std::string> rr = std::make_pair(1, "2222");
    ft::pair<int, std::string> ded = ft::make_pair(11, "1HEY");
    ft::pair<int, std::string> fff(ded);

    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "MAP MAX SIZE DIFFERENT" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "stdMap: " << stdMap.max_size() << std::endl;
    std::cout << "myMap: " << myMap.max_size() << std::endl;

    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "MAP INSERT" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    for (int i = 1; i < 8; i +=  1)
        myMap.insert(ft::make_pair(i, "1"));
    const ft::map<int, std::string> myMap2(myMap.begin(), myMap.end());
    ft::map<int, std::string>::const_iterator myIt2(myMap2.begin());
    ft::pair <ft::map<int, std::string>::iterator, bool> test = myMap.insert(ft::make_pair(222, "222"));
    std::cout << test.second << " result is " << test.first->first << "  " << test.first->second << std::endl;
    for (; myIt2 != myMap2.end(); ++myIt2)
        std::cout << myIt2->first << myIt2->second << std::endl;
    typedef ft::map<int, int>::iterator iterator;
    ft::map<int, int, std::plus<int> > mp3;
    for (int i = 1; i < 3; i +=  1)
        mp3.insert(ft::make_pair(i, i));
    for (iterator it = mp3.begin(); it != mp3.end(); ++it) {
        std::cout << it->first << std::endl;
    }
    std::map<int, int, std::plus<int> > mp;
    for (int i = 1; i < 3; i +=  1)
        mp.insert(std::make_pair(i, i));
    for (std::map<int, int>::iterator it1 = mp.begin(); it1 != mp.end(); ++it1) {
        std::cout << it1->first << std::endl;
    }

    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "MAP ERASE" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    for (int i = 50000; i > 0; i -=  1)
        stdMap.insert(std::make_pair(i, "1"));
    stdMap.erase(stdMap.begin(), ((--stdMap.end())));
    std::map<int, std::string>::iterator It(stdMap.begin());
    for (; It != stdMap.end(); ++It) {
        std::cout << (*(It)).first << "\t";
    }
    ft::map<int, std::string> copymap(myMap);
    std::cout << std::endl << "result is " << stdMap.size() << std::endl;
    myMap.erase(9998);
    for (int i = 30; i < 50000; i +=  1)
        myMap.insert(ft::make_pair(i, "1"));
    std::cout << std::endl << "result is " << myMap.size() << std::endl;
    myMap.erase(myMap.begin(), ((--myMap.end())));

    ft::map<int, std::string>::iterator myIt3(myMap.begin());
    for (; myIt3 != myMap.end(); ++myIt3) {
        std::cout << (*(myIt3)).first << "\t";
    }

    ft::map<int, std::string> copy2(myMap);
    std::cout << std::endl << "result is " << copy2.size() << std::endl;

    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "MAP SIZE + MAX_SIZE" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << myMap.max_size() << std::endl;
    std::cout << myMap.size() << std::endl;

    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "ITERATORS + REVERSE" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    for (int i = 5; i > 0; i -=  1)
        myMap.insert(ft::make_pair(i, "1"));
    ft::map<int, std::string>::const_iterator myIt4(myMap.begin());
    ft::map<int, std::string>::reverse_iterator myR(myMap.rbegin());
    for (; myIt4 != myMap.end(); ++myIt4)
        std::cout << (*(myIt4)).second << std::endl;
    for (; myR != myMap.rend(); ++myR)
        std::cout << (*(myR)).second << std::endl;

    // upper bound equal_range
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "PAIR" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    ft::map<int, int> mpp;
    std::map<int, int> m;
    std::cout << "std MAKE_PAIR: " << std::endl;
    m.insert(std::make_pair(20, 20));
    m.insert(std::make_pair(30, 30));
    m.insert(std::make_pair(40, 40));
    m.insert(std::make_pair(50, 50));
    m.insert(std::make_pair(60, 60));
    m.insert(std::make_pair(-10, 10));
    m.insert(std::make_pair(-20, 20));
    std::map<int, int>::iterator iter(m.begin());
    std::cout << "my MAKE_PAIR: " << std::endl;
    mpp.insert(ft::make_pair(20, 20));
    mpp.insert(ft::make_pair(30, 30));
    mpp.insert(ft::make_pair(40, 40));
    mpp.insert(ft::make_pair(50, 50));
    mpp.insert(ft::make_pair(60, 60));
    mpp.insert(ft::make_pair(-10, 10));
    mpp.insert(ft::make_pair(-20, 20));
    ft::map<int, int>::iterator IT(mpp.begin());
    if (mpp.upper_bound(11) == mpp.end())
        std::cout << "no" << std::endl;
    else
        std::cout << mpp.upper_bound(11)->first << std::endl;
    if (m.upper_bound(11) == m.end())
        std::cout << "no" << std::endl;
    else
        std::cout << m.upper_bound(11)->first << std::endl;
    if (mpp.lower_bound(11) == mpp.end())
        std::cout << "no" << std::endl;
    else
        std::cout << mpp.upper_bound(11)->first << std::endl;
    if (m.lower_bound(11) == m.end())
        std::cout << "no" << std::endl;
    else
        std::cout << m.upper_bound(11)->first << std::endl;
    ft::pair<ft::map<int, int>::iterator, ft::map<int, int>::iterator> res = mpp.equal_range(20);
    std::pair<std::map<int, int>::iterator, std::map<int, int>::iterator> res1 = m.equal_range(20);
    if (res.first != mpp.end()) {
        std::cout << res.first->first << std::endl;
        std::cout << res.second->first << std::endl;
    }
    if (res1.first != m.end()) {
        std::cout << res1.first->first << std::endl;
        std::cout << res1.second->first << std::endl;
    }
    for (int i = 1; i < 60; i += 10) {
        IT = mpp.upper_bound(i);
        std::cout << (*(IT)).second << std::endl;}
    for (; IT != mpp.end(); ++IT)
        std::cout << (*(IT)).first << "  " << (*(IT)).second << std::endl;
    for (; iter != m.end(); ++iter)
        std::cout << (*(iter)).first << "  " << (*(iter)).second << std::endl;

    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "MAP CLEAR" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    myMap.clear();

    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "MAP SIZE + MAX_SIZE" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << myMap.max_size() << std::endl;
    std::cout << myMap.size() << std::endl;

    return 0;
}
