#include <bits/stdc++.h>

using namespace std;

#define int long long

int solve()
{
	int x1, y1, z1, p1, q1;
	cin >> x1 >> y1 >> z1 >> p1 >> q1;

	int x2, y2, z2, p2, q2;
	cin >> x2 >> y2 >> z2 >> p2 >> q2;

	int dx = x2 - x1;
	int dy = y2 - y1;
	if (dx * p1 + dy * q1 == 0 && dx * p2 + dy * q2 == 0)
		return 2;

	int det = p1 * q2 - q1 * p2;
	if (det == 0)
		return 4;

	int c1 = x1 * p1 + y1 * q1;
	int c2 = x2 * p2 + y2 * q2;
	int x = c1 * q2 - q1 * c2;
	int y = p1 * c2 - c1 * p2;

	int t = (x - x1 * det) * (x - x2 * det) + (y - y1 * det) * (y - y2 * det);
	int dz = z1 - z2;
	int delta = dz * dz * det * det - 4 * t;
	if (delta < 0)
		return 4;

	bool at1 = (x == x1 * det && y == y1 * det);
	bool at2 = (x == x2 * det && y == y2 * det);
	if (at1 || at2)
		return z1 != z2 ? 3 : 4;

	return 3;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		cout << solve() << '\n';
}
