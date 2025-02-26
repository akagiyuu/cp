#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 998244353;
const ll CACHE_POW = (1ll << 63) % MOD;

ll powmod(ll a, ll b)
{
	a %= MOD;

	ll res = 1;
	while (b) {
		if (b & 1) {
			res = res * a % MOD;
			a = a * a % MOD;
		}

		b >>= 1;
	}

	return res;
}

ll pow2(ll exp)
{
	return powmod(CACHE_POW, exp / 63) * ((1ll << (exp % 63)) % MOD) % MOD;
}

void solve()
{
	ll n;
	cin >> n;

	vector<ll> prefix_first(n);
	vector<ll> prefix_second(n);

	for (ll i = 0; i < n; i++) {
		cin >> prefix_first[i];
		if (i != 0)
			prefix_first[i] += prefix_first[i - 1];
	}
	for (ll i = 0; i < n; i++) {
		cin >> prefix_second[i];
		if (i != 0)
			prefix_second[i] += prefix_second[i - 1];
	}

	auto get_def = [prefix_first, prefix_second](ll l, ll r) {
		ll m1 = l == 0 ? prefix_first[r] : prefix_first[r] - prefix_first[l - 1];
		ll m2 = l == 0 ? prefix_second[r] : prefix_second[r] - prefix_second[l - 1];

		if (m1 == m2)
			return 0ll;

		return min(m1, m2);
	};

	ll res = 0;
	for (ll l = 0; l < n; l++) {
		for (ll r = 0; r < n; r++) {
			ll remaining = n - (r - l + 1);
			if (l > 0)
				remaining--;
			if (r < n - 1)
				remaining--;

			res += pow2(remaining) * get_def(l, r);
		}
	}

	cout << res << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
