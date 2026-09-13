#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

void solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	for (int j = 1; j < n - 1; j++) {
		if (a[0] + a[j] <= a[n - 1]) {
			cout << 1 << ' ' << j + 1 << ' ' << n << '\n';
			return;
		}
	}
	cout << -1 << '\n';
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
