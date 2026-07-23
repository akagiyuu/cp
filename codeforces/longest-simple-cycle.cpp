#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

void solve()
{
	int n;
	cin >> n;
	vector<int> c(n), a(n), b(n);
	for (int i = 0; i < n; i++)
		cin >> c[i];
	int _tmp;
	cin >> _tmp;
	for (int i = 0; i < n - 1; i++)
		cin >> a[i];
	a[n - 1] = 1;
	cin >> _tmp;
	for (int i = 0; i < n - 1; i++)
		cin >> b[i];
	b[n - 1] = n;

	vector<int> dp(n);
	dp[n - 2] = abs(a[n - 1] - b[n - 2]) + abs(a[n - 2] - b[n - 2]) + 2;
	for (int i = n - 3; i >= 0; i--) {
		if (i == 0 || a[i + 1] == b[i + 1]) {
			dp[i] = c[i + 1] - 1
		} else {
			cur += x - 1;
			cur += c[i] - y;
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
