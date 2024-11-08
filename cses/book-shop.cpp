#include <bits/stdc++.h>
// #include "/home/yuu/Code/competitive_programming/cpp-dump/cpp-dump.hpp"

typedef long long ll;

const ll MOD = 1000000007;

using namespace std;

void solve()
{
	int n, x;
	cin >> n >> x;
	vector<ll> h(n);
	for (int i = 0; i < n; i++) {
		cin >> h[i];
	}

	vector<ll> s(n);
	for (int i = 0; i < n; i++) {
		cin >> s[i];
	}

	vector<ll> dp(x + 1, 0);

	dp[0] = 0;
	for (int j = 0; j < n; j++) {
		for (int i = x; i >= 0; i--) {
			if (i >= h[j]) {
				dp[i] = max(dp[i], dp[i - h[j]] + s[j]);
			}
		}
	}

	// cpp_dump(dp);
	cout << dp[x];
}

int main()
{
	solve();
}
