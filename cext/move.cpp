#include "move.h"

vector<vector<int>> combine(int n, int k)
{
	vector<vector<int>> result;
	int i = 0;
	vector<int> p(k, 0);
	while (i >= 0)
	{
		p[i]++;
		if (p[i] > n)
			--i;
		else if (i == k - 1)
			result.push_back(p);
		else
		{
			++i;
			p[i] = p[i - 1];
		}
	}
	return result;
}

int foo()
{
	return 0;
}

vector<vector<int>> getActions(vector<int>& handcards, vector<int>& last)
{
	vector<vector<int>> res;
	int totalCard = 0; // 手里的牌数目
	for (int num : last)
		totalCard += num;
	if (totalCard == 0)
	{
		vector<vector<bool>> records(4, vector<bool>(15, false));
		vector<int> lenDict = { 5, 3, 2 };
		// 核弹
		if (handcards[13] && handcards[14])
		{
			vector<int> tmp(15, 0);
			tmp[13] = 1;
			tmp[14] = 1;
			res.push_back(tmp);
		}
		// 单出：单、双、三、四 & 四带2单，2双
		for (int i = 0; i < 15; i++)
		{
			for (int j = 1; j <= handcards[i]; j++)
			{
				records[j - 1][i] = true;
				vector<int> tmp(15, 0);
				tmp[i] = j;
				res.push_back(tmp);
				if (j == 4)
				{ // 四带2单，2双
					for (int num = 1; num <= 2; num++)
					{ // 单双翅
						vector<int> container;
						for (int k = 0; k < 15; k++)
						{
							if (k != i && handcards[k] >= num)
							{
								container.push_back(k);
							}
						}
						if (container.size() < 2)
							break;
						vector<vector<int>> combinations = combine(container.size(), 2);
						for (vector<int> idxs : combinations)
						{
							vector<int> backup(tmp);
							for (int idx : idxs)
							{
								backup[container[idx - 1]] = num;
							}
							res.push_back(backup);
						}
					}
				}
			}
		}
		// 三带一，三带二
		for (int main = 0; main < 15; main++)
		{
			if (handcards[main] >= 3)
			{
				for (int i = 0; i < 15; i++)
				{
					if (i != main && records[0][i])
					{ // + 1
						vector<int> tmp(15, 0);
						tmp[main] = 3;
						tmp[i] = 1;
						res.push_back(tmp);
					}
					if (i != main && records[1][i])
					{ // + 2
						vector<int> tmp(15, 0);
						tmp[main] = 3;
						tmp[i] = 2;
						res.push_back(tmp);
					}
				}
			}
		}
		// 顺子：单、双、三 & 飞机带翅膀
		for (int t = 0; t < 3; t++)
		{
			int start = 0, cur = 0;
			while (cur < 12)
			{
				// 'A' index is 11
				while (cur < 12 && records[t][cur])
					cur++;
				if (cur - start >= lenDict[t])
				{
					// 手牌最多有20个
					for (int len = lenDict[t]; len <= (cur - start) && (t + 1) * len <= 20; len++)
					{
						for (int i = start; i + len <= cur; i++)
						{
							vector<int> tmp(15, 0);
							for (int j = i; j < i + len; j++)
							{
								tmp[j] = t + 1;
							}
							res.push_back(tmp);
							if (t == 2)
							{ // 飞机可以带1, 2翅膀
								for (int wing = 1; wing <= 2; wing++)
								{ // 单双翅
									if ((t + 1) * len + wing * len <= 20)
									{
										vector<int> container;
										for (int i = 0; i < 15; i++)
										{
											if (tmp[i] == 0 && handcards[i] >= wing)
											{
												container.push_back(i);
											}
										}
										if (int(container.size()) < len)
											break;
										vector<vector<int>> combinations = combine(container.size(), len);
										for (vector<int> idxs : combinations)
										{
											vector<int> backup(tmp);
											for (int idx : idxs)
											{
												backup[container[idx - 1]] = wing;
											}
											res.push_back(backup);
										}
									}
								}
							}
						}
					}
				}
				while (cur < 12 && !records[t][cur])
					cur++;
				start = cur;
			}
		}
	}
	else
	{
		// 全局数据
		int diffCard = 0;		  // 手里不同种类的牌数
		int maxCard = 0;		  // 手里的最大的牌: 0, 1, ... 14
		int maxCount = 0;		  // 手里最多的牌，他有多少个
		vector<int> maxCountCard; // 手里最多的牌形成的数组
		for (int i = 0; i < 15; i++)
		{
			if (last[i] != 0)
			{
				maxCard = i;
				diffCard += 1;
				if (last[i] > maxCount)
					maxCount = last[i];
			}
		}
		for (int i = 0; i < 15; i++)
		{
			if (last[i] == maxCount)
			{
				maxCountCard.push_back(i);
			}
		}
		// 让一步，要不起
		vector<int> none(15, 0);
		res.push_back(none);
		// --------------碾压规则------------------
		// 核弹碾压一切
		if (handcards[13] == 1 && handcards[14] == 1)
		{ // 核弹炸他！
			vector<int> tmp(15, 0);
			tmp[13] = 1;
			tmp[14] = 1;
			res.push_back(tmp);
		}
		if (totalCard == 2 && last[13] == 1 && last[14] == 1)
		{ // 核弹要不起
			return res;
		}
		// 炸弹碾压非核弹，非更大的炸弹以外的所有牌型
		if (diffCard == 1 && maxCount == 4)
		{
			for (int i = maxCard + 1; i < 15; i++)
			{
				if (handcards[i] == 4)
				{
					vector<int> tmp(15, 0);
					tmp[i] = 4;
					res.push_back(tmp);
				}
			}
		}
		else
		{
			for (int i = 0; i < 15; i++)
			{
				if (handcards[i] == 4)
				{
					vector<int> tmp(15, 0);
					tmp[i] = 4;
					res.push_back(tmp);
				}
			}
		}
		// --------------针对性规则------------------
		// 单出：1，2，3
		if (diffCard == 1)
		{
			if (maxCount < 4)
			{
				for (int i = maxCard + 1; i < 15; i++)
				{
					if (handcards[i] >= maxCount)
					{
						vector<int> tmp(15, 0);
						tmp[i] = maxCount;
						res.push_back(tmp);
					}
				}
			}
			return res;
		}
		// 三带一，三带二
		if ((totalCard == 4 || totalCard == 5) && diffCard == 2 && maxCount == 3)
		{
			int kicker = totalCard - 3;
			for (int main = maxCountCard[0] + 1; main < 15; main++)
			{
				if (handcards[main] >= 3)
				{
					for (int i = 0; i < 15; i++)
					{
						if (i != main && handcards[i] >= kicker)
						{ // 带1或2
							vector<int> tmp(15, 0);
							tmp[main] = 3;
							tmp[i] = kicker;
							res.push_back(tmp);
						}
					}
				}
			}
			return res;
		}
		// 顺子：1，2，3
		if (diffCard == maxCountCard.size())
		{
			int type = totalCard / diffCard;
			int start = maxCountCard[0] + 1;
			int cur = start;
			while (cur < 12)
			{
				// 'A' index is 11
				while (cur < 12 && handcards[cur] >= type)
					cur++;
				if (cur - start >= diffCard)
				{
					for (int i = start; i + diffCard <= cur; i++)
					{
						vector<int> tmp(15, 0);
						for (int j = i; j < i + diffCard; j++)
						{
							tmp[j] = type;
						}
						res.push_back(tmp);
					}
				}
				while (cur < 12 && handcards[cur] < type)
					cur++;
				start = cur;
			}
			return res;
		}
		// 四带俩1，四带俩2
		if (diffCard == 3 && maxCount == 4 && (totalCard == 6) || (totalCard == 8))
		{
			int kicker = (totalCard - 4) / 2;
			for (int i = maxCountCard[0] + 1; i < 15; i++)
			{
				if (handcards[i] == 4)
				{
					vector<int> tmp(15, 0);
					tmp[i] = 4;

					vector<int> container;
					for (int k = 0; k < 15; k++)
					{
						if (k != i && handcards[k] >= kicker)
						{
							container.push_back(k);
						}
					}
					if (container.size() < 2)
						continue;
					vector<vector<int>> combinations = combine(container.size(), 2);
					for (vector<int> idxs : combinations)
					{
						vector<int> backup(tmp);
						for (int idx : idxs)
						{
							backup[container[idx - 1]] = kicker;
						}
						res.push_back(backup);
					}
				}
			}
			return res;
		}
		// 飞机带一、二翅
		for (int wing = 1; wing <= 2; wing++)
		{
			if (maxCountCard.size() >= 2 && maxCount == 3 && totalCard == (3 + wing) * maxCountCard.size() && diffCard == 2 * maxCountCard.size())
			{
				int len = diffCard / 2;
				int start = maxCountCard[0];
				int cur = start;
				while (cur < 12)
				{
					// 'A' index is 11
					while (cur < 12 && handcards[cur] >= 3)
						cur++;
					if (cur - start >= len)
					{
						for (int i = start; i + len <= cur; i++)
						{
							vector<int> tmp(15, 0);
							for (int j = i; j < i + len; j++)
							{
								tmp[j] = 3;
							}
							vector<int> container;
							for (int i = 0; i < 15; i++)
							{
								if (tmp[i] == 0 && handcards[i] >= wing)
								{
									container.push_back(i);
								}
							}
							if (container.size() < 2)
								continue;
							vector<vector<int>> combinations = combine(container.size(), len);
							for (vector<int> idxs : combinations)
							{
								vector<int> backup(tmp);
								for (int idx : idxs)
								{
									backup[container[idx - 1]] = wing;
								}
								res.push_back(backup);
							}
						}
					}
					while (cur < 12 && handcards[cur] < 3)
						cur++;
					start = cur;
				}
				return res;
			}
		}
	}
	return res;
}