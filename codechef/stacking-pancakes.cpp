#include <bits/stdc++.h>
#include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;
const ll N = 1e5;

ll fact[N + 1], ifact[N + 1];

ll powmod(ll a, ll b)
{
	a %= MOD;
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
	if (n < k)
		return 0;
	return fact[n] * ifact[k] % MOD * ifact[n - k] % MOD;
}

struct Hash {
	size_t operator()(const pair<ll, ll> &a) const
	{
		hash<ll> f;
		return f(a.first) ^ f(a.second);
	}
};

ll cal(ll m, ll n, unordered_map<pair<ll, ll>, ll, Hash> &cache)
{
	if (m > n)
		return 0;
	if (m == 1)
		return 1;
	if (n == 1)
		return 0;
	auto key = make_pair(m, n);
	if (cache.find(key) != cache.end())
		return cache[key];
	ll val = cal(m, n - 1, cache) * m % MOD + cal(m - 1, n - 1, cache) % MOD;
	cache[key] = val;
	return val;
}

ll cal_naive(ll n, ll cur_max)
{
	if (n == 0)
		return 1;
	ll res = 0;
	for (ll i = 1; i <= cur_max + 1; i++) {
		res += cal_naive(n - 1, max(i, cur_max));
		res %= MOD;
	}
	return res;
}

void solve()
{
	ll n;
	cin >> n;
	unordered_map<pair<ll, ll>, ll, Hash> cache;
	ll res = 1;
    cpp_dump(n);
	for (ll m = 2; m <= n; m++) {
        ll cur = 0;
		for (ll i = 2; i <= n; i++) {
			cur += nCk(i - 2, m - 2) * powmod(m, n - i) % MOD;
            cur %= MOD;
			res += nCk(i - 2, m - 2) * powmod(m, n - i) % MOD;
			res %= MOD;
		}
        cpp_dump(m, cur);
	}
	cout << "Naive: " << cal_naive(n - 1, 1) << "\n";
	cout << "Recur: " << res << "\n";
}

int main()
{
	CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();
	int t;
	cin >> t;
	while (t--)
		solve();
}
