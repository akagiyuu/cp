#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

void solve()
{
	int n, c;
	cin >> n >> c;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		a[i] -= c;
	}
	sort(a.begin(), a.end());
	int res = 0;
	int cnt = 0;
	int i = n - 1;
	while (i >= 0 && a[i] >= 0) {
		res += a[i];
		cnt++;
		i--;
	}
	int require = (n - 2 * cnt + 1) / 2;
	while (i >= 0 && require > 0) {
		res += a[i];
		require--;
		i--;
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
