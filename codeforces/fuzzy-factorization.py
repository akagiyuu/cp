from math import log, ceil


def solve():
    print(1)

    x = float(input())
    for base in [2, 3, 5, 7, 11]:
        lg = log(x, base)
        right = lg
        left = lg + log(1 - 1e-9, base)
        if right >= ceil(left):
            print(2, ceil(left))
            return


solve()
