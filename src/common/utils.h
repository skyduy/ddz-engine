#ifndef __CARD_UTILS_H__
#define __CARD_UTILS_H__

#include <iostream>
#include <vector>

template <typename T>
void print(const std::vector<T>& v) {
    for (T i : v) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}

template <typename T>
void print(const std::vector<std::vector<T>>& vs) {
    for (auto v : vs) {
        print(v);
    }
    std::cout << std::endl;
}

#endif
