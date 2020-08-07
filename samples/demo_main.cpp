#include "common/utils.h"
#include "rule/rule.h"

int main() {
    CardVector handcards = {0, 2, 1, 2, 1, 1, 1, 1, 1, 3, 0, 2, 3, 1, 0};
    CardVector lastcards = {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::vector<CardVector> res = getActions(handcards, lastcards);
    print(res);
    return 0;
}
