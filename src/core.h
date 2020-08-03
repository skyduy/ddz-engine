#pragma once
#include <vector>

using std::vector;

void combine(const vector<int>& options, int k, vector<vector<int>>& candidates);
vector<vector<int>> getActions(vector<int>& handcards, vector<int>& last);
