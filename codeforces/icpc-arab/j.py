def solve():
    n = int(input())
    a = []
    for c in input().split(" "):
        a.append(int(c))
    a.sort()

    s = 0
    for x in a:
        s += x
    m_i = (n - 1) // 2

    if n % 2 == 1:
        x = a[m_i - 1] * (n + 1) - s
        if x < a[m_i]:
            return x
        x = a[m_i] * (n + 1) - s
        return x
    else:
        x = a[m_i] * (n + 1) - s
        if x < a[m_i]:
            return x
        x = a[m_i + 1] * (n + 1) - s
        return x


t = int(input())
for i in range(t):
    print(solve())
