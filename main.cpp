#include <iostream>
#include <vector>
#include "Stack.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;

    // vector::pop_back

       std::vector<int> myvector = std::vector<int>();

        ft::stack <int> my_stack = ft::stack<int>(myvector);
      //  ft::stack<int> my_stack;
        int sum (0);
//        myvector.push_back (100);
//        myvector.push_back (200);
//        myvector.push_back (300);
        my_stack.push(100);
        my_stack.push(200);
        my_stack.push(300);

//        while (!myvector.empty())
//        {
//            sum+=myvector.back();
//            myvector.pop_back();
//        }

        std::cout << "size of stack is " << my_stack.size() << std::endl;
        while (!my_stack.empty())
        {
            sum+=my_stack.top();
            my_stack.pop();
        }

        std::cout << "The elements of myvector add up to " << sum << '\n';

        return 0;

}
