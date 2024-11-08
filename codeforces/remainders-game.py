from math import lcm

def solve():
    [n, k] = input().split(" ")
    k = int(k)
    cs = input().split(" ")
    l = int(cs[0])
    if l % k == 0:
        return True
    for i in range(1, len(cs)):
        l = lcm(l, int(cs[i]))
        if l % k == 0:
            return True
    return False

if solve():
    print("Yes")
else:
    print("No")
