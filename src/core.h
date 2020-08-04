#pragma once
#include <iostream>
#include <vector>

using std::vector;
typedef vector<uint16_t> CardVector;
typedef vector<uint16_t> CardList;

void combine(const CardList& options, size_t k, vector<CardList>& candidates);

vector<CardVector> getActions(CardVector& handcards, CardVector& last);

template <typename T>
void print(const vector<T>& v) {
    for (T i : v) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}

template <typename T>
void print(const vector<vector<T>>& vs) {
    for (auto v : vs) {
        print(v);
    }
    std::cout << std::endl;
}
