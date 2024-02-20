#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include "UniIterator.hpp"

int main() {
    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::deque<float> d1 = {6.2, 7.1, 8.3, 9.2, 10.8, 12.3};

    UniIterator<std::vector<int>::iterator, std::deque<float>::iterator> iter(v1.begin(), v1.end(), d1.begin(), d1.end());
    iter.setOperation(Operation::ADD);
    for (unsigned int i = 0; i < 10; i++, iter++)
        std::cout << *iter << std::endl;
    for (unsigned int i = 0; i < 10; i++, iter--)
        std::cout << *iter << std::endl;
    return 0;
}
