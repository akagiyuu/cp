#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

void solve()
{
	int n, m;
	cin >> n >> m;

	vector<int> cnt(m + 2, 0);
	vector<int> suffix(m + 2, 0);
	vector<int> ans(m + 2, 0);

	int total = 0;

	for (int i = 1; i <= n; i++) {
		int x;
		cin >> x;

		cnt[x]++;
		total += x;
	}

	for (int x = m; x >= 1; x--) {
		suffix[x] = suffix[x + 1] + cnt[x];
	}

	for (int k = 1; k <= m; k++) {
		ans[k] = total;
	}

	for (int k = 1; ; k++) {
		int C = (1LL << k);

		if (C > m)
			break;

		vector<int> value(m + 1, 0);

		for (int q = 1; q < C; q++) {
			int limit = m / q;

			for (int x = 1; x <= limit; x++) {
				value[x] += suffix[q * x];
			}
		}

		for (int x = 1; x <= m / C; x++) {
			value[x] += cnt[C * x];
		}

		int best = 0;

		for (int x = 1; x <= m; x++) {
			best = max(best, value[x]);
		}

		ans[k] = best;
	}

	cout << ans[1] << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int t;
	cin >> t;

	while (t--)
		solve();
}
