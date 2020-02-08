import cext
from pprint import pprint

handcards = [0,0,0,0,0,1,1,3,3,3,3,3,1,1]
all_cards = [4] * 13 + [1,1]
no_cards = [0] * 15

print(len(cext.get_actions(all_cards, no_cards)))
print(len(cext.get_actions(handcards, no_cards)))

last_cards = [1,0,0,0,0,0,0,0,0,0,3,0,0,0,0]
pprint(cext.get_actions(handcards, last_cards))
