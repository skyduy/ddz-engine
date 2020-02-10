//
// pch.cpp
// Include the standard header and generate the precompiled header.
//

#include "pch.h"
#include <iostream>
using std::cout;
using std::endl;

void print(const vector<int>& v)
{
	for (int i : v) {
		cout << i << ' ';
	}
	cout << endl;
}

void print(const vector<vector<int>>& vs)
{
	for (auto v : vs) {
		print(v);
	}
	cout << endl;
}