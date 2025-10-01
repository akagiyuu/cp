#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 998244353;
const ll N = 1e6;

ll binpow(ll a, ll b)
{
	a %= MOD;
	ll res = 1;
	while (b) {
		if (b & 1)
			res = (res * a) % MOD;
		a = (a * a) % MOD;
		b >>= 1;
	}
	return res;
}

ll inv(ll a)
{
	return binpow(a, MOD - 2);
}

void solve()
{
	ll n, m;
	cin >> n >> m;
	vector<vector<array<ll, 3> > > segments(m + 1);
	vector<ll> dp(m + 1);
	dp[0] = 1;
	ll l, r, p, q;
	for (ll i = 0; i < n; i++) {
		cin >> l >> r >> p >> q;
		segments[r].push_back({ l - 1, p, q });
		dp[0] *= (q - p) * inv(q) % MOD;
		dp[0] %= MOD;
	}
	for (ll r = 1; r <= m; r++) {
		for (auto [l, p, q] : segments[r]) {
			dp[r] += dp[l] * p % MOD * inv(q - p) % MOD;
			dp[r] %= MOD;
		}
	}
	cout << dp[m] << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
