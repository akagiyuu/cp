#include <bits/stdc++.h>
// #include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;
const ll N = 34;

__int128 catalan[N + 1];

void build()
{
	catalan[0] = 1;
	for (ll i = 1; i <= N; i++) {
		catalan[i] = (4 * i - 2) * catalan[i - 1] / (i + 1);
	}
}

struct Hash {
	size_t operator()(const pair<ll, ll> &a) const
	{
		return hash<ll>()(a.first) ^ hash<ll>()(a.second);
	}
};

ll cal(ll n, ll h, unordered_map<pair<ll, ll>, ll, Hash> &cache)
{
	if (n < h)
		return 0;
	if (h == 0)
		return catalan[n];
	if (n == h)
		return 1ll << (n - 1);
	auto key = make_pair(n, h);
	if (cache.find(key) != cache.end())
		return cache[key];
	ll res = 0;
	for (ll i = 0; i < n; i++) {
		res += cal(i, h - 1, cache) * (2 * (ll)catalan[n - 1 - i] - cal(n - 1 - i, h - 1, cache));
	}
	cache[key] = res;
	return res;
}

void solve()
{
	ll n, h;
	cin >> n >> h;
	unordered_map<pair<ll, ll>, ll, Hash> cache;
	cout << cal(n, h, cache);
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
