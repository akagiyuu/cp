#include <bits/stdc++.h>

#define int long long

using namespace std;
const int NBIT = 64;
const int MOD = 1e9 + 7;

vector<int> build(int k)
{
	int max_sum = k * (k + 1) / 2;
	vector<int> dp(max_sum + 1, 0);
	dp[0] = 1;
	for (int i = 1; i <= k; i++) {
		for (int w = max_sum; w >= i; w--) {
			dp[w] += dp[w - i];
		}
	}
	return dp;
}

void solve()
{
	int n, k, x;
	cin >> n >> k >> x;
	auto dp = build(k);
	int res = 1;
	for (int i = 0; i <= NBIT; i++) {
		if (!((x >> i) & 1))
			continue;
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
