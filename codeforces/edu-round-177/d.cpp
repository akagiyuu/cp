#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 998244353;

const ll N = 1e6;

ll fact[N + 1];
ll ifact[N + 1];

ll powmod(ll a, ll b)
{
	ll res = 1;
	while (b) {
		if (b & 1)
			res = res * a % MOD;

		a = a * a % MOD;
		b >>= 1;
	}
	return res;
}

void build()
{
	fact[0] = 1;
	for (ll i = 1; i <= N; i++) {
		fact[i] = fact[i - 1] * i % MOD;
	}

	ifact[N] = powmod(fact[N], MOD - 2);
	for (ll i = N - 1; i >= 0; i--) {
		ifact[i] = ifact[i + 1] * (i + 1) % MOD;
	}
}

ll count_sum_equal(ll target, vector<ll> &a)
{
	vector<ll> dp(target + 1, 0);
	dp[0] = 1;

	for (int x : a) {
		for (int s = target; s >= x; s--) {
			dp[s] = (dp[s] + dp[s - x]) % MOD;
		}
	}

	return dp[target];
}

void solve()
{
	vector<ll> a;
	ll temp;
	ll sum = 0;
	for (int i = 0; i < 26; i++) {
		cin >> temp;
		if (temp != 0) {
			a.push_back(temp);
			sum += temp;
		}
	}

	ll res = count_sum_equal(sum / 2, a);

	res = (res * fact[sum / 2]) % MOD;
	res = (res * fact[(sum + 1) / 2]) % MOD;

	for (auto x : a) {
		res = (res * ifact[x]) % MOD;
	}

	cout << res << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();

	int t;
	cin >> t;
	while (t--)
		solve();
}
