#include <bits/stdc++.h>

using namespace std;

#define int long long
#define double long double

struct Circle {
	int x, y, t;
};

int is_inside(const Circle &a, const Circle &b)
{
	int dx = a.x - b.x;
	int dy = a.y - b.y;
	int d = dx * dx + dy * dy;

	int dr = a.t - b.t;
	dr = dr * dr;
	if (d < dr)
		return 1;
	if (d == dr)
		return 2;
	return 0;
}

void solve()
{
	int n, q;
	cin >> n >> q;
	vector<Circle> c(n);
	for (int i = 0; i < n; i++)
		cin >> c[i].t >> c[i].x >> c[i].y;
	vector<double> a;
	vector<int> b;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			int tmp = is_inside(c[i], c[j]);
			if (tmp == 1)
				continue;
			if (tmp == 2) {
				b.push_back(max(c[i].t, c[j].t));
				continue;
			}

			int dx = c[i].x - c[j].x;
			int dy = c[i].y - c[j].y;
			double d = sqrtl(dx * dx + dy * dy);
			a.push_back((double)(d + c[i].t + c[j].t) / 2.);
		}
	}
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	while (q--) {
		int t;
		cin >> t;

		int res = 0;
		int i = lower_bound(a.begin(), a.end(), t) - a.begin() - 1;
		int j = upper_bound(a.begin(), a.end(), t) - a.begin() - 1;
		res += 2 * (i + 1);
		res += j - i;

		res += upper_bound(b.begin(), b.end(), t) - b.begin();

		cout << res << '\n';
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		solve();
}
