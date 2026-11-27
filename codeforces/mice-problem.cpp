#include <bits/stdc++.h>

using namespace std;

#define int long long
#define double long double

const double INF = 1e32;

double solve()
{
	int n;
	int x1, y1, x2, y2;
	cin >> n >> x1 >> y1 >> x2 >> y2;

	double l = 0, r = INF;
	for (int i = 0; i < n; i++) {
		int rx, ry, vx, vy;
		cin >> rx >> ry >> vx >> vy;
		if (vx == 0 && vy == 0) {
			if (x1 < rx && rx < x2 && y1 < ry && ry < y2)
				continue;
			return -1;
		}
		if (vx == 0 && (rx <= x1 || x2 <= rx)) {
			return -1;
		}
		if (vy == 0 && (ry <= y1 || y2 <= ry)) {
			return -1;
		}

		if (vx != 0) {
			double l1 = (double)(x1 - rx) / (double)vx;
			double r1 = (double)(x2 - rx) / (double)vx;
			if (l1 > r1)
				swap(l1, r1);
			l = max(l, l1);
			r = min(r, r1);
		}

		if (vy != 0) {
			double l2 = (double)(y1 - ry) / (double)vy;
			double r2 = (double)(y2 - ry) / (double)vy;
			if (l2 > r2)
				swap(l2, r2);
			l = max(l, l2);
			r = min(r, r2);
		}
	}
	if (l >= r)
		return -1;
	return l;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cout << fixed << setprecision(10) << solve() << '\n';
}
