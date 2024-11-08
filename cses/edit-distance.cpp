#include <bits/stdc++.h>
// #include "/home/yuu/Code/competitive_programming/cpp-dump/cpp-dump.hpp"

typedef long long ll;

const ll MOD = 1000000007;

using namespace std;

void solve()
{
	string a, b;
	cin >> a >> b;
	int n = a.length();
	int m = b.length();

	vector<vector<int> > dp(n + 1, vector<int>(m + 1, INT_MAX));
	dp[0][0] = 0;
	for (int i = 1; i <= n; i++) {
		dp[i][0] = i;
	}
	for (int j = 1; j <= m; j++) {
		dp[0][j] = j;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			dp[i][j] = dp[i - 1][j - 1] + (a[i - 1] == b[j - 1] ? 0 : 1);
			dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
			dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);
		}
	}

	cout << dp[n][m];
}

int main()
{
	solve();
}
