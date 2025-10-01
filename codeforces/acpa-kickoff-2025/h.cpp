#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

ll binpow(ll a, ll b)
{
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
	ll n, s = 0;
	cin >> n;
	vector<ll> a(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
		s += a[i];
		s %= MOD;
	}

	ll res = 0;
	// for (ll step = 0; step < n; step++) {
	// 	for (ll start = 0; start < n; start++) {
	// 		set<ll> s;
	// 		ll current = start;
	// 		for (ll i = 0; i < n; i++) {
	// 			s.insert(current);
	// 			current = (current + step) % n;
	// 		}
	// 		// for (auto x : s) {
	// 		// 	res += x;
	// 		// 	res %= MOD;
	// 		// }
	// 		cpp_dump(start, step, s);
	// 	}
	// }
	for (ll step = 0; step < n; step++) {
        ll x = n / gcd(n, step);
        ll cur = s * x % MOD;
        res = (res + cur) % MOD;
	}
	res = res * inv(n * n % MOD) % MOD;
	cout << res << "\n";
}

int main()
{
	// CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		solve();
}
