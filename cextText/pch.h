//
// pch.h
// Header for standard system include files.
//

#pragma once
#include<string>
#include<vector>

#include "gtest/gtest.h"

using std::string;
using std::vector;

string value2Card(int v);
bool print(vector<int>& card);
bool print(vector<vector<int>>& card);