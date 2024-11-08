#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

ll pow(ll a, ll b, ll mod)
{
	ll res = 1;
	while (b > 0) {
		if (b & 1) {
			res *= a;
			res %= mod;
		}
		a *= a;
		a %= mod;
		b /= 2;
	}
	return res;
}

void solve()
{
	ll n, mod;
	cin >> n >> mod;
	vector<ll> ws(n);
	for (ll i = 0; i < n; i++) {
		cin >> ws[i];
	}
	vector<vector<ll> > dp(n, vector<ll>(n));
	for (ll i = n - 1; i >= 0; i--) {
		dp[i][i] = ws[i] % mod;
		for (ll j = i - 1; j >= 0; j--) {
			dp[j][i] = pow(ws[j] % mod, dp[j + 1][i], mod);
		}
	}
	ll q;
	cin >> q;
	while (q--) {
		ll left, right;
		cin >> left >> right;
		left--;
		right--;
		cout << dp[left][right] << "\n";
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
