#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

void solve()
{
	int n;
	cin >> n;
	vector<string> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	int one_cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			one_cnt += a[i][j] == '1';
		}
	}

	int max_diag_cnt = 0;
	for (int i = 0; i < n; i++) {
		int cur = 0;
		for (int j = 0; j < n; j++) {
			cur += a[(i + j) % n][j] == '1';
		}
		max_diag_cnt = max(max_diag_cnt, cur);
	}

	cout << one_cnt + n - 2 * max_diag_cnt << "\n";
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
