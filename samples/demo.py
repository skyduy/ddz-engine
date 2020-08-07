import os
import sys

dir_path = os.path.dirname(os.path.realpath(__file__))

# On Windows: make sure you have install the ddz.dll file and rename it to
# ddz.pyd at specific location: ddz_bin_path
ddz_bin_path = os.path.realpath(os.path.join(dir_path, '..', 'out'))
sys.path.insert(0, ddz_bin_path)

import ddz
handcard = [0, 2, 1, 2, 1, 1, 1, 1, 1, 3, 0, 2, 3, 1, 0]
lastcard = [2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
res = ddz.get_actions(handcard, lastcard)
for choice in res:
    print(choice)
