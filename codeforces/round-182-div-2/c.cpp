#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 998244353;

void solve()
{
	ll n;
	cin >> n;
	vector<ll> a(n);
	vector<ll> b(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (ll i = 0; i < n; i++) {
		cin >> b[i];
	}

	vector<array<ll, 2> > dp(n, { 0, 0 });
	dp[0] = { 1, 1 };
	for (ll i = 1; i < n; i++) {
		if (a[i] >= a[i - 1] && b[i] >= b[i - 1]) {
			dp[i][0] = (dp[i][0] + dp[i - 1][0]) % MOD;
			dp[i][1] = (dp[i][1] + dp[i - 1][1]) % MOD;
		}
		if (a[i] >= b[i - 1] && b[i] >= a[i - 1]) {
			dp[i][0] = (dp[i][0] + dp[i - 1][1]) % MOD;
			dp[i][1] = (dp[i][1] + dp[i - 1][0]) % MOD;
		}
	}

	cout << (dp[n - 1][0] + dp[n - 1][1]) % MOD << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		solve();
}
