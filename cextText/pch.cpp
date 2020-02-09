//
// pch.cpp
// Include the standard header and generate the precompiled header.
//
#include "pch.h"
using std::to_string;
using std::cout;
using std::endl;

string value2Card(int v)
{
	string c;
	switch (v)
	{
	case 8:
		c = "J";
		break;
	case 9:
		c = "Q";
		break;
	case 10:
		c = "K";
		break;
	case 11:
		c = "A";
		break;
	case 12:
		c = "2";
		break;
	case 13:
		c = "小";
		break;
	case 14:
		c = "大";
		break;
	default:
		c = to_string(v + 3);
		break;
	}
	return c;
}

bool print(vector<int>& card)
{
	int flag = false;
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < card[i]; j++)
		{
			flag = true;
			cout << value2Card(i) << ' ';
		}
	}
	return flag;
}

bool print(vector<vector<int>>& card) {
	for (vector<int> i : card)
	{
		bool res = print(i);
		if (res == false)
			cout << "要不起";
		cout << endl;
	}
	return true;
}