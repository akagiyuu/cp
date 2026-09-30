#include <bits/stdc++.h>
#include <cassert>

using namespace std;

#define int long long

const int MOD = 1000000007;

int add(int x, int y)
{
	x += y;
	if (x >= MOD)
		x -= MOD;
	return x;
}
int sub(int x, int y)
{
	x -= y;
	if (x < 0)
		x += MOD;
	return x;
}

void solve()
{
	int k, l;
	cin >> k >> l;
	vector<vector<int> > a(k, vector<int>(k));
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			cin >> a[i][j];
		}
	}
	int n;
	cin >> n;
	vector<int> left(n), right(n);
	for (int i = 1; i < n; i++) {
		int p;
		cin >> p;
		left[i] = p - l;
		right[i] = p + l;
	}
	vector<int> dp(k, 1), ndp(k);
	for (int i = 0; i < n - 1; i++) {
		ndp.assign(k, 0);
		for (int j = 0; j < k; j++) {
			int l = lower_bound(a[j].begin(), a[j].end(), left[i + 1]) - a[j].begin();
			int r = upper_bound(a[j].begin(), a[j].end(), right[i + 1]) - a[j].begin() - 1;
			if (l > r)
				continue;
			if (l >= k)
				continue;
			ndp[l] = add(ndp[l], dp[j]);
			if (r < k - 1) {
				ndp[r + 1] = sub(ndp[r + 1], dp[j]);
			}
			// for (int x = l; x <= r; x++) {
			// 	ndp[x] = add(ndp[x], dp[j]);
			// }
		}
		for (int j = 1; j < k; j++)
			ndp[j] = add(ndp[j], ndp[j - 1]);
		dp = ndp;
	}
	int res = 0;
	for (auto x : dp)
		res = add(res, x);
	cout << res << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
