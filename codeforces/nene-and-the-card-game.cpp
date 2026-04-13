#include <bits/stdc++.h>

#define int long long

using namespace std;

void solve()
{
	int n;
	cin >> n;
	map<int, int> cnt;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		cnt[x]++;
	}
	int res = 0;
	for (auto [x, c] : cnt) {
		if (c == 2)
			res++;
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
