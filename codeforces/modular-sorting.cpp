#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

void solve()
{
	int n, m, q;
	cin >> n >> m >> q;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	vector<int> cnt(m + 1, 0);
	for (int d1 = 1; d1 * d1 <= m; d1++) {
		if (m % d1 != 0)
			continue;
		int d2 = m / d1;
		for (int i = 1; i < n; i++) {
			cnt[d1] += (a[i] % d1) < (a[i - 1] % d1);
			if (d1 != d2)
				cnt[d2] += (a[i] % d2) < (a[i - 1] % d2);
		}
	}
	while (q--) {
		int type;
		cin >> type;
		if (type == 1) {
			int i, x;
			cin >> i >> x;
			i--;
			auto update = [&](int d) {
				if (i > 0) {
					cnt[d] -= (a[i] % d) < (a[i - 1] % d);
					cnt[d] += (x % d) < (a[i - 1] % d);
				}

				if (i < n - 1) {
					cnt[d] -= (a[i + 1] % d) < (a[i] % d);
					cnt[d] += (a[i + 1] % d) < (x % d);
				}
			};
			for (int d1 = 1; d1 * d1 <= m; d1++) {
				if (m % d1 != 0)
					continue;
				int d2 = m / d1;
				update(d1);
				if (d1 != d2)
					update(d2);
			}
			a[i] = x;
		} else {
			int k;
			cin >> k;
			int g = gcd(k, m);
			if (cnt[g] < m / g)
				cout << "YES\n";
			else
				cout << "NO\n";
		}
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
