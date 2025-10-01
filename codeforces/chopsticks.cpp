#include <bits/stdc++.h>
#include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 998244353;
const ll N = 1e7;

ll fact[N], ifact[N];

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

void build()
{
	fact[0] = 1;
	for (ll i = 1; i < N; i++) {
		fact[i] = fact[i - 1] * i % MOD;
	}
	ifact[N - 1] = binpow(fact[N - 1], MOD - 2);
	for (ll i = N - 2; i >= 0; i--) {
		ifact[i] = ifact[i + 1] * (i + 1) % MOD;
	}
}

ll nCk(ll n, ll k)
{
	if (k < 0 || k > n)
		return 0;
	return (fact[n] * ifact[k]) % MOD * ifact[n - k] % MOD;
}

ll solve()
{
	build();
	ll n, m, s = 0;
	cin >> n >> m;
	vector<ll> k(m);
	for (ll i = 0; i < m; i++) {
		cin >> k[i];
		s += k[i];
	}
    cpp_dump(k);

	ll res = 0;
	for (ll i = 0; i < m; i++) {
		for (ll j = 1; j <= k[i]; j += 2) {
			res += nCk(k[i], j) * nCk(s - k[i], 2 * n - j) % MOD;
			res %= MOD;
		}
	}
	return res * binpow(2, MOD - 2) % MOD;
}

int main()
{
	CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cout << solve() << "\n";
}
