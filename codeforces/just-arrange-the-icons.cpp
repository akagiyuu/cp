#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

void solve()
{
	int n;
	cin >> n;
	map<int, int> pre_cnt;
	for (int i = 0; i < n; i++) {
		int c;
		cin >> c;
		pre_cnt[c]++;
	}

	int m = LLONG_MAX;
	map<int, int> cnt;
	for (auto [_, c] : pre_cnt) {
		m = min(m, c);
		cnt[c]++;
	}
	for (int s = m + 1; s >= 2; s--) {
		bool ok = true;
		for (auto [x, _] : cnt) {
			if (((x + s - 1) / s) > (x / (s - 1))) {
				ok = false;
				break;
			}
		}
		if (!ok)
			continue;

		int res = 0;
		for (auto [x, c] : cnt) {
			res += c * ((x + s - 1) / s);
		}
		cout << res << "\n";
		return;
	}

	int res = 0;
	for (auto [x, c] : cnt) {
		res += c * x;
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
