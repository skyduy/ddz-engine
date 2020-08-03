#include "utils.h"

void print(const std::vector<int>& v) {
    for (int i : v) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}

void print(const std::vector<std::vector<int>>& vs) {
    for (auto v : vs) {
        print(v);
    }
    std::cout << std::endl;
}
