#include "core.h"

inline void reset(vector<uint16_t>& v) {
    std::fill(v.begin(), v.end(), 0);
}

// select k-combination from options to candidates
void combine(const CardList& options, size_t k, vector<CardList>& candidates) {
    size_t n = options.size();
    int i = 0;
    CardList candidate(k, 0);
    vector<size_t> index(k, 0);
    while (i >= 0) {
        index[i]++;
        if (index[i] > n) {
            --i;
        } else if (i == k - 1) {
            reset(candidate);
            for (int j = 0; j < k; j++) {
                candidate[j] = options[index[j] - 1];
            }
            candidates.push_back(candidate);
        } else {
            ++i;
            index[i] = index[size_t(i) - 1];
        }
    }
}

vector<CardVector> getActions(CardVector& handcards, CardVector& last) {
    vector<CardVector> res;
    CardVector choice(15, 0);
    int totalCard = 0; // 手里的牌数目
    for (int num : last) totalCard += num;
    if (totalCard == 0) {
        vector<int> lenDict = {5, 3, 2};
        // 核弹
        if (handcards[13] && handcards[14]) {
            reset(choice);
            choice[13] = choice[14] = 1;

            res.push_back(choice);
        }
        // 单出：单、双、三、四 & 四带2单，2双
        for (int i = 0; i < 15; i++) {
            for (int j = 1; j <= handcards[i]; j++) {
                reset(choice);
                choice[i] = j;
                res.push_back(choice);
                if (j == 4) {                            // 四带2单，2双
                    for (int num = 1; num <= 2; num++) { // 单双翅
                        CardList container;
                        for (int k = 0; k < 15; k++) {
                            if (k != i && handcards[k] >= num) {
                                container.push_back(k);
                            }
                        }
                        if (container.size() < 2) break;
                        vector<CardList> candidates;
                        combine(container, 2, candidates);
                        for (CardList candidate : candidates) {
                            CardVector backup(choice);
                            for (int c : candidate) {
                                backup[c] = num;
                            }
                            res.push_back(backup);
                        }
                    }
                }
            }
        }
        // 三带一，三带二
        for (int main = 0; main < 15; main++) {
            if (handcards[main] >= 3) {
                for (int i = 0; i < 15; i++) {
                    if (i != main && handcards[i] != 0) { // + 1
                        reset(choice);
                        choice[main] = 3;
                        choice[i] = 1;
                        res.push_back(choice);
                    }
                    if (i != main && handcards[i] > 1) { // + 2
                        reset(choice);
                        choice[main] = 3;
                        choice[i] = 2;
                        res.push_back(choice);
                    }
                }
            }
        }
        // 顺子：单、双、三 & 飞机带翅膀
        for (int t = 0; t < 3; t++) {
            int start = 0, cur = 0;
            while (cur < 12) {
                // 'A' index is 11
                while (cur < 12 && handcards[cur] > t) cur++;
                if (cur - start >= lenDict[t]) {
                    // 手牌最多有20个
                    for (int len = lenDict[t]; len <= (cur - start) && (t + 1) * len <= 20; len++) {
                        for (int i = start; i + len <= cur; i++) {
                            reset(choice);
                            for (int j = i; j < i + len; j++) {
                                choice[j] = t + 1;
                            }
                            res.push_back(choice);
                            if (t == 2) {                               // 飞机可以带1, 2翅膀
                                for (int wing = 1; wing <= 2; wing++) { // 单双翅
                                    if ((t + 1) * len + wing * len <= 20) {
                                        CardList container;
                                        for (int i = 0; i < 15; i++) {
                                            if (choice[i] == 0 && handcards[i] >= wing) {
                                                container.push_back(i);
                                            }
                                        }
                                        if (int(container.size()) < len) break;
                                        vector<CardList> candidates;
                                        combine(container, len, candidates);
                                        for (CardList candidate : candidates) {
                                            CardVector backup(choice);
                                            for (int c : candidate) {
                                                backup[c] = wing;
                                            }
                                            res.push_back(backup);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                while (cur < 12 && handcards[cur] <= t) cur++;
                start = cur;
            }
        }
    } else {
        // 全局数据
        int diffCard = 0;         // 手里不同种类的牌数
        int maxCard = 0;          // 手里的最大的牌: 0, 1, ... 14
        int maxCount = 0;         // 手里最多的牌，他有多少个
        vector<int> maxCountCard; // 手里最多的牌形成的数组
        for (int i = 0; i < 15; i++) {
            if (last[i] != 0) {
                maxCard = i;
                diffCard += 1;
                if (last[i] > maxCount) maxCount = last[i];
            }
        }
        for (int i = 0; i < 15; i++) {
            if (last[i] == maxCount) {
                maxCountCard.push_back(i);
            }
        }
        // 让一步，要不起
        CardVector none(15, 0);
        res.push_back(none);
        // --------------碾压规则------------------
        // 核弹碾压一切
        if (handcards[13] == 1 && handcards[14] == 1) { // 核弹炸他！
            reset(choice);
            choice[13] = 1;
            choice[14] = 1;
            res.push_back(choice);
        }
        if (totalCard == 2 && last[13] == 1 && last[14] == 1) { // 核弹要不起
            return res;
        }
        // 炸弹碾压非核弹，非更大的炸弹以外的所有牌型
        if (diffCard == 1 && maxCount == 4) {
            for (int i = maxCard + 1; i < 15; i++) {
                if (handcards[i] == 4) {
                    reset(choice);
                    choice[i] = 4;
                    res.push_back(choice);
                }
            }
        } else {
            for (int i = 0; i < 15; i++) {
                if (handcards[i] == 4) {
                    reset(choice);
                    choice[i] = 4;
                    res.push_back(choice);
                }
            }
        }
        // --------------针对性规则------------------
        // 单出：1，2，3
        if (diffCard == 1) {
            if (maxCount < 4) {
                for (int i = maxCard + 1; i < 15; i++) {
                    if (handcards[i] >= maxCount) {
                        reset(choice);
                        choice[i] = maxCount;
                        res.push_back(choice);
                    }
                }
            }
            return res;
        }
        // 三带一，三带二
        if ((totalCard == 4 || totalCard == 5) && diffCard == 2 && maxCount == 3) {
            int kicker = totalCard - 3;
            for (int main = maxCountCard[0] + 1; main < 15; main++) {
                if (handcards[main] >= 3) {
                    for (int i = 0; i < 15; i++) {
                        if (i != main && handcards[i] >= kicker) { // 带1或2
                            reset(choice);
                            choice[main] = 3;
                            choice[i] = kicker;
                            res.push_back(choice);
                        }
                    }
                }
            }
            return res;
        }
        // 顺子：1，2，3
        if (diffCard == maxCountCard.size()) {
            int type = totalCard / diffCard;
            int start = maxCountCard[0] + 1;
            int cur = start;
            while (cur < 12) {
                // 'A' index is 11
                while (cur < 12 && handcards[cur] >= type) cur++;
                if (cur - start >= diffCard) {
                    for (int i = start; i + diffCard <= cur; i++) {
                        reset(choice);
                        for (int j = i; j < i + diffCard; j++) {
                            choice[j] = type;
                        }
                        res.push_back(choice);
                    }
                }
                while (cur < 12 && handcards[cur] < type) cur++;
                start = cur;
            }
            return res;
        }
        // 四带俩1，四带俩2
        if ((diffCard == 3 && maxCount == 4 && totalCard == 6) || (totalCard == 8)) {
            int kicker = (totalCard - 4) / 2;
            for (int i = maxCountCard[0] + 1; i < 15; i++) {
                if (handcards[i] == 4) {
                    reset(choice);
                    choice[i] = 4;

                    CardList container;
                    for (int k = 0; k < 15; k++) {
                        if (k != i && handcards[k] >= kicker) {
                            container.push_back(k);
                        }
                    }
                    if (container.size() < 2) continue;
                    vector<CardList> candidates;
                    combine(container, 2, candidates);
                    for (CardList candidate : candidates) {
                        CardVector backup(choice);
                        for (int c : candidate) {
                            backup[c] = kicker;
                        }
                        res.push_back(backup);
                    }
                }
            }
            return res;
        }
        // 飞机带一、二翅
        for (int wing = 1; wing <= 2; wing++) {
            if (maxCountCard.size() >= 2 && maxCount == 3 &&
                totalCard == (3 + size_t(wing)) * maxCountCard.size() &&
                diffCard == 2 * maxCountCard.size()) {
                int len = diffCard / 2;
                int start = maxCountCard[0];
                int cur = start;
                while (cur < 12) {
                    // 'A' index is 11
                    while (cur < 12 && handcards[cur] >= 3) cur++;
                    if (cur - start >= len) {
                        for (int i = start; i + len <= cur; i++) {
                            reset(choice);
                            for (int j = i; j < i + len; j++) {
                                choice[j] = 3;
                            }
                            CardList container;
                            for (int i = 0; i < 15; i++) {
                                if (choice[i] == 0 && handcards[i] >= wing) {
                                    container.push_back(i);
                                }
                            }
                            if (container.size() < 2) continue;
                            vector<CardList> candidates;
                            combine(container, len, candidates);
                            for (CardList candidate : candidates) {
                                CardVector backup(choice);
                                for (int c : candidate) {
                                    backup[c] = wing;
                                }
                                res.push_back(backup);
                            }
                        }
                    }
                    while (cur < 12 && handcards[cur] < 3) cur++;
                    start = cur;
                }
                return res;
            }
        }
    }
    return res;
}
