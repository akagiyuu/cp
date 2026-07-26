#include <bits/stdc++.h>

using namespace std;

#define int long long
#define pi pair<int, int>

typedef complex<double> P;

const double INF = 1e19;

double sum_dist(P a, P b)
{
	return abs(a) + abs(b - a);
}

void solve()
{
	int n, m;
	double a, b;
	cin >> n >> m >> a >> b;
	vector<double> ya(n), yb(m), l(m);
	for (int i = 0; i < n; i++)
		cin >> ya[i];
	for (int i = 0; i < m; i++)
		cin >> yb[i];
	for (int i = 0; i < m; i++)
		cin >> l[i];

	double dist = INF;
	pi ans = { -1, -1 };
	for (int j = 0; j < m; j++) {
		double y0 = yb[j] * a / b;
		int i = lower_bound(ya.begin(), ya.end(), y0) - ya.begin();

		double cur = sum_dist(P(a, ya[i]), P(b, yb[j]));
		if (i > 0) {
			double d = sum_dist(P(a, ya[i - 1]), P(b, yb[j]));
			if (d < cur) {
				cur = d;
				i--;
			}
		}
		cur += l[j];

		if (cur < dist) {
			dist = cur;
			ans = { i + 1, j + 1 };
		}
	}
	cout << ans.first << " " << ans.second << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
