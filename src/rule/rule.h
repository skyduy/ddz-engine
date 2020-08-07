#ifndef __CARD_RULE_H__
#define __CARD_RULE_H__

#include <vector>

typedef std::vector<uint16_t> CardVector;
typedef std::vector<uint16_t> CardList;

void combine(const CardList& options, size_t k, std::vector<CardList>& candidates);
std::vector<CardVector> getActions(CardVector& handcards, CardVector& last);

#endif
