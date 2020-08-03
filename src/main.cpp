#include "core.h"
#include "utils.h"

int main() {
    std::vector<int> handcards = {0, 2, 1, 2, 1, 1, 1, 1, 1, 3, 0, 2, 3, 1, 0};
    std::vector<int> lastcards = {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    auto res = getActions(handcards, lastcards);
    print(res);
    return 0;
}
