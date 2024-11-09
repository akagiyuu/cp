#include <bits/stdc++.h>
// #include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;
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

ll nCk(ll n, ll k)
{
	return fact[n] * ifact[k] % MOD * ifact[n - k] % MOD;
}

void solve()
{
	ll k;
	cin >> k;
	vector<ll> color_count(k);
	for (ll i = 0; i < k; i++) {
		cin >> color_count[i];
	}
	ll res = 1;
	ll ball_count = color_count[0];
	for (ll i = 1; i < k; i++) {
		res = res * nCk(color_count[i] - 1 + ball_count, ball_count) % MOD;
		ball_count += color_count[i];
	}
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
