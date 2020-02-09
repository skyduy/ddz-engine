from pprint import pprint
import cext  # type: ignore

HANDCARDS = [0, 0, 0, 0, 0, 1, 1, 3, 3, 3, 3, 3, 1, 1]
ALL_CARDS = [4] * 13 + [1, 1]
NO_CARDS = [0] * 15
LAST_CARDS = [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0]

print(len(cext.get_actions(ALL_CARDS, NO_CARDS)))
print('--')
print(len(cext.get_actions(HANDCARDS, NO_CARDS)))
print('--')
pprint(cext.get_actions(HANDCARDS, LAST_CARDS))
