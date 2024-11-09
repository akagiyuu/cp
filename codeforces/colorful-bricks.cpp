#include <bits/stdc++.h>
// #include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 998244353;
const ll N = 1e6;

ll powmod(ll a, ll b)
{
	ll res = 1;
	while (b) {
		if (b & 1)
			res = res * a % MOD;
		b >>= 1;
		a = a * a % MOD;
	}
	return res;
}

ll fact[N + 1];
ll ifact[N + 1];

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

ll nCk(ll n, ll k)
{
	if (n < k)
		return 0;
	return fact[n] * ifact[k] % MOD * ifact[n - k] % MOD;
}

void solve()
{
	ll n, m, k;
	cin >> n >> m >> k;
	ll res = m * powmod(m - 1, k) % MOD * nCk(n - 1, k) % MOD;
	cout << res;
}

int main()
{
	// CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();
	solve();
}
