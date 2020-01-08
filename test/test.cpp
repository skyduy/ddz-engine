#include "pch.h"
#include <vector>
#include <istream>
#include <string>
#include "../core.h"

using namespace std;
vector<vector<int>> res;

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

bool print(vector<int> &card)
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

bool print(vector<vector<int>> &card)
{
	for (vector<int> i : card)
	{
		bool res = print(i);
		if (res == false)
			cout << "要不起";
		cout << endl;
	}
	return true;
}

TEST(getActionsTest, 主动_手持54张牌_主动出牌13550种)
{
	vector<int> handcards;
	for (int i = 0; i < 13; i++)
		handcards.push_back(4);
	handcards.push_back(1);
	handcards.push_back(1);
	vector<int> none;
	res = getActions(handcards, none);
	EXPECT_EQ(res.size(), 13550);
}

TEST(getActionsTest, 主动_手持20张春天牌_主动出牌368种)
{
	vector<int> handcards = {0, 0, 0, 0, 0, 1, 1, 3, 3, 3, 3, 3, 1, 1, 1};
	vector<int> none;
	res = getActions(handcards, none);
	EXPECT_EQ(res.size(), 368);
}

TEST(getActionsTest, 被动_要不起)
{
	vector<int> handcards = {0, 2, 1, 2, 1, 1, 1, 1, 1, 3, 0, 2, 3, 1, 0};
	vector<int> lastcards = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0};
	res = getActions(handcards, lastcards);
	EXPECT_EQ(res.size(), 1);
}

TEST(getActionsTest, 被动_对方核弹_要不起)
{
	vector<int> handcards = {0, 2, 1, 2, 1, 1, 1, 1, 1, 3, 0, 2, 3, 1, 0};
	vector<int> lastcards = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1};
	res = getActions(handcards, lastcards);
	EXPECT_EQ(res.size(), 1);
}

TEST(getActionsTest, 被动_我方核弹_炸他)
{
	vector<int> handcards = {1, 1, 1, 2, 1, 1, 1, 1, 1, 3, 0, 2, 3, 1, 1};
	vector<int> lastcards = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0};
	res = getActions(handcards, lastcards);
	vector<int> ans = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1};
	EXPECT_EQ(res.size(), 2);
	EXPECT_EQ(res[1], ans);
}

TEST(getActionsTest, 被动_炸弹炸他)
{
	vector<int> handcards = {0, 4, 1, 2, 1, 1, 1, 1, 1, 3, 0, 2, 3, 1, 0};
	vector<int> lastcards = {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0};
	res = getActions(handcards, lastcards);
	vector<int> ans = {0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	EXPECT_EQ(res[1], ans);
}

TEST(getActionsTest, 被动_炸弹被压_要不起)
{
	vector<int> handcards = {1, 1, 1, 2, 1, 1, 1, 1, 1, 3, 0, 4, 0, 0, 0};
	vector<int> lastcards = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0};
	res = getActions(handcards, lastcards);
	EXPECT_EQ(res.size(), 1);
}

TEST(getActionsTest, 被动_单张_压他)
{
	vector<int> handcards = {0, 2, 1, 2, 1, 1, 1, 1, 1, 3, 0, 2, 3, 1, 0};
	vector<int> lastcards = {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	res = getActions(handcards, lastcards);
	EXPECT_EQ(res.size(), 11 + 1);
}

TEST(getActionsTest, 被动_两张_压死)
{
	vector<int> handcards = {0, 2, 1, 2, 1, 1, 1, 1, 1, 3, 0, 2, 3, 1, 0};
	vector<int> lastcards = {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	res = getActions(handcards, lastcards);
	EXPECT_EQ(res.size(), 5 + 1);
}

TEST(getActionsTest, 被动_三张_大你)
{
	vector<int> handcards = {0, 2, 1, 2, 1, 1, 1, 1, 1, 3, 0, 2, 3, 1, 0};
	vector<int> lastcards = {0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	res = getActions(handcards, lastcards);
	EXPECT_EQ(res.size(), 2 + 1);
}

TEST(getActionsTest, 被动_炸弹压炸弹)
{
	vector<int> handcards = {0, 2, 1, 2, 1, 1, 1, 0, 1, 1, 0, 4, 1, 0, 0};
	vector<int> lastcards = {0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	res = getActions(handcards, lastcards);
	EXPECT_EQ(res.size(), 1 + 1);
}

TEST(getActionsTest, 被动_三带一_压死)
{
	vector<int> handcards = {0, 2, 1, 2, 1, 1, 1, 0, 1, 1, 0, 3, 1, 0, 0};
	vector<int> lastcards = {0, 0, 0, 0, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	res = getActions(handcards, lastcards);
	EXPECT_EQ(res.size(), 9 + 1);
}

TEST(getActionsTest, 被动_三带二_压死)
{
	vector<int> handcards = {0, 2, 1, 2, 1, 1, 1, 0, 1, 1, 0, 3, 1, 0, 0};
	vector<int> lastcards = {0, 0, 0, 0, 0, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0};
	res = getActions(handcards, lastcards);
	EXPECT_EQ(res.size(), 2 + 1);
}

TEST(getActionsTest, 被动_顺子_管上)
{
	vector<int> handcards = {0, 2, 1, 2, 1, 1, 0, 1, 1, 1, 1, 3, 1, 0, 0};
	vector<int> lastcards = {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	res = getActions(handcards, lastcards);
	EXPECT_EQ(res.size(), 2 + 1);
}

TEST(getActionsTest, 被动_连顺_大你)
{
	vector<int> handcards = {0, 2, 1, 2, 2, 2, 2, 0, 1, 1, 0, 0, 1, 0, 0};
	vector<int> lastcards = {0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	res = getActions(handcards, lastcards);
	EXPECT_EQ(res.size(), 2 + 1);
}

TEST(getActionsTest, 被动_凸翅飞机_压死)
{
	vector<int> handcards = {0, 3, 3, 3, 3, 1, 0, 0, 0, 0, 0, 3, 0, 0, 0};
	vector<int> lastcards = {3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	res = getActions(handcards, lastcards);
	EXPECT_EQ(res.size(), 3 + 1);
}

TEST(getActionsTest, 被动_四带俩单张_压死)
{
	vector<int> handcards = {0, 2, 1, 2, 2, 2, 4, 0, 1, 1, 0, 0, 1, 0, 0};
	vector<int> lastcards = {0, 1, 1, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	res = getActions(handcards, lastcards);
	EXPECT_EQ(res.size(), 1 + 1 + 28);
}

TEST(getActionsTest, 被动_四带俩2)
{
	vector<int> handcards = {0, 2, 1, 2, 2, 2, 2, 0, 1, 4, 0, 0, 1, 0, 0};
	vector<int> lastcards = {0, 2, 2, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	res = getActions(handcards, lastcards);
	EXPECT_EQ(res.size(), 1 + 1 + 10);
}

TEST(getActionsTest, 被动_单翅飞机_压死)
{
	vector<int> handcards = {0, 2, 1, 3, 3, 3, 3, 0, 1, 1, 0, 0, 1, 0, 0};
	vector<int> lastcards = {0, 1, 3, 3, 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0};
	res = getActions(handcards, lastcards);
	EXPECT_EQ(res.size(), 1 + 20 + 20);
}

TEST(getActionsTest, 被动_双翅飞机_管上)
{
	vector<int> handcards = {0, 2, 1, 3, 3, 3, 3, 0, 1, 2, 0, 0, 1, 0, 0};
	vector<int> lastcards = {0, 2, 3, 3, 3, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0};
	res = getActions(handcards, lastcards);
	EXPECT_EQ(res.size(), 1 + 2);
}