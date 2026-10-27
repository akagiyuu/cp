#include <bits/stdc++.h>

using namespace std;

void solve()
{
	int n, m, q;
	cin >> n >> m >> q;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	vector<int> cnt(m + 1, 0);
	vector<int> divisor;
	for (int d1 = 1; d1 * d1 <= m; d1++) {
		if (m % d1 != 0)
			continue;
		int d2 = m / d1;
		divisor.push_back(d1);
		if (d1 != d2)
			divisor.push_back(d2);
	}

	for (auto d : divisor) {
		for (int i = 1; i < n; i++) {
			cnt[d] += (a[i] % d) < (a[i - 1] % d);
		}
	}
	while (q--) {
		int type;
		cin >> type;
		if (type == 1) {
			int i, x;
			cin >> i >> x;
			i--;
			for (auto d : divisor) {
				if (i > 0) {
					cnt[d] -= (a[i] % d) < (a[i - 1] % d);
					cnt[d] += (x % d) < (a[i - 1] % d);
				}

				if (i < n - 1) {
					cnt[d] -= (a[i + 1] % d) < (a[i] % d);
					cnt[d] += (a[i + 1] % d) < (x % d);
				}
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
