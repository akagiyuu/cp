#include <bits/stdc++.h>

using namespace std;

#define int long long
#define pi pair<int, int>
#define fi first
#define se second

void solve()
{
	int n;
	cin >> n;
	vector<pi> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i].fi >> a[i].se;
	}
	if (n <= 2) {
		cout << 0 << '\n';
		return;
	}
	int res = n * (n - 1) * (n - 2) / 6;
	map<pi, int> cnt;
	for (int i = 0; i < n; i++) {
		cnt.clear();
		for (int j = i + 1; j < n; j++) {
			int dx = a[j].fi - a[i].fi;
			int dy = a[j].se - a[i].se;
			if (dx < 0) {
				dx = -dx;
				dy = -dy;
			}
			if (dy == 0) {
				dx = 1;
			} else if (dx == 0) {
				dy = 1;
			} else {
				int g = gcd(dx, dy);
				dx /= g;
				dy /= g;
			}
			cnt[{ dx, dy }]++;
		}
		for (auto [_, c] : cnt) {
			res -= c * (c - 1) / 2;
		}
	}
	cout << res << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
