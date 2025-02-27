#include <bits/stdc++.h>
// #include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

int mex(set<ll> const &a)
{
	ll result = 0;
	while (a.count(result))
		++result;
	return result;
}

template <> struct std::hash<pair<ll, ll> > {
	size_t operator()(const pair<ll, ll> &a) const
	{
		auto f = hash<ll>();
		return f(a.first) ^ f(a.second);
	}
};

ll g(pair<ll, ll> key, unordered_map<pair<ll, ll>, ll> &cache)
{
	if (cache.find(key) != cache.end())
		return cache[key];
	set<ll> state;
	for (auto [dx, dy] : { make_pair(-2, 1), make_pair(-2, -1), make_pair(1, -2), make_pair(-1, -2) }) {
		ll next_x = key.first + dx;
		ll next_y = key.second + dy;
		if (next_x < 1 || next_x > 15 || next_y < 1 || next_y > 15)
			continue;
        state.insert(g(make_pair(next_x, next_y), cache));
	}
	ll res = mex(state);
	cache[key] = res;
	return res;
}

unordered_map<pair<ll, ll>, ll> cache;

void solve()
{
	ll n;
	cin >> n;
	ll res = 0;
	pair<ll, ll> x;
	for (ll i = 0; i < n; i++) {
		cin >> x.first >> x.second;
		res ^= g(x, cache);
	}
	if (res > 0)
		cout << "First\n";
	else
		cout << "Second\n";
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
