from decimal import Decimal, getcontext

EPS = Decimal(1e-64)


def linear2(a, b, c, d, e, f):
    det = a * e - b * d
    if det == 0:
        return 0, 0, False
    x = e * c - b * f
    y = f * a - c * d
    return x / det, y / det, True


def quad(a, b, c):
    delta = b * b - Decimal(4) * a * c
    if delta < -EPS:
        return 0, 0, False
    if delta > 0:
        delta = delta.sqrt()
    else:
        delta = 0
    return (
        (-b + delta) / (Decimal(2) * a),
        (-b - delta) / (Decimal(2) * a),
        True,
    )


def dist(a, b, c, d, e, f):
    dx = a - d
    dy = b - e
    dz = c - f
    return dx * dx + dy * dy + dz * dz


def solve():
    [x1, y1, z1] = [Decimal(x) for x in input().split()]
    [p1, q1] = [Decimal(x) for x in input().split()]
    [x2, y2, z2] = [Decimal(x) for x in input().split()]
    [p2, q2] = [Decimal(x) for x in input().split()]

    dx = x1 - x2
    dy = y1 - y2

    if (dx * p1 + dy * q1) == 0 and (dx * p2 + dy * q2) == 0:
        return 2

    x, y, ok = linear2(p1, q1, x1 * p1 + y1 * q1, p2, q2, x2 * p2 + y2 * q2)
    if not ok:
        return 4
    t = (x - x1) * (x - x2) + (y - y1) * (y - y2)
    z3, z4, ok = quad(1, -(z1 + z2), z1 * z2 + t)
    if not ok:
        return 4

    if dist(x, y, z3, x1, y1, z1) > 0 and dist(x, y, z3, x2, y2, z2) > 0:
        return 3
    if dist(x, y, z4, x1, y1, z1) > 0 and dist(x, y, z4, x2, y2, z2) > 0:
        return 3

    return 4


t = int(input())
for _ in range(t):
    print(solve())
