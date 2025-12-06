#include <bits/stdc++.h>

#define int long long

using namespace std;

void solve()
{
	int n;
	cin >> n;
	vector<string> g(n);
	for (int i = 0; i < n; i++) {
		cin >> g[i];
	}
	int res = LONG_LONG_MAX;

	int cnt = 0;
	for (int i = 0; i < n; i++) {
		bool ok = true;
		for (int j = 0; j < n; j++) {
			if (g[i][j] == '#') {
				ok = false;
				break;
			}
		}
		if (!ok)
			cnt++;
	}
	res = min(res, cnt);

	cnt = 0;
	for (int j = 0; j < n; j++) {
		bool ok = true;
		for (int i = 0; i < n; i++) {
			if (g[i][j] == '#') {
				ok = false;
				break;
			}
		}
		if (!ok)
			cnt++;
	}
	res = min(res, cnt);

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
