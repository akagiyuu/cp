#include <bits/stdc++.h>

#define int long long

using namespace std;

struct pt {
	int x, y, cost;
};

int dist(const pt &a, const pt &b)
{
	return abs(a.x - b.x) + abs(a.y - b.y);
}

void solve()
{
	int n;
	cin >> n;
	vector<pt> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i].x;
	}
	for (int i = 0; i < n; i++) {
		cin >> a[i].y;
	}
	for (int i = 0; i < n; i++) {
		cin >> a[i].cost;
	}
	int total_cost = 0;
	for (int i = 0; i < n; i++) {
		total_cost += a[i].cost;
	}
	int max_x = 0;
	int min_x = LONG_LONG_MAX;
	int max_y = 0;
	int min_y = LONG_LONG_MAX;
	for (int i = 0; i < n; i++) {
		max_x = max(max_x, a[i].x);
		min_x = min(min_x, a[i].x);
		max_y = max(max_y, a[i].y);
		min_y = min(min_y, a[i].y);
	}
	int res = 2 * (max_x - min_x) + 2 * (max_y - min_y);
	for (int i = 0; i < n; i++) {
		res = max(res, total_cost - a[i].cost);
	}
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			int cur = total_cost + 2 * dist(a[i], a[j]) - a[i].cost - a[j].cost;
			res = max(res, cur);
		}
	}
	cout << res << "\n";
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
