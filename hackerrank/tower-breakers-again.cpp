#include <bits/stdc++.h>
// #include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;
const ll N = 1e6;

vector<ll> divisors[N + 1];

void build()
{
	for (ll i = 2; i <= N; i++) {
		for (ll j = i; j <= N; j += i) {
			divisors[j].push_back(i);
		}
	}
}

int mex(set<ll> const &a)
{
	int result = 0;
	while (a.count(result))
		++result;
	return result;
}

ll cal_grunt(ll key, unordered_map<ll, ll> &cache)
{
	if (cache.find(key) != cache.end()) {
		return cache[key];
	}
	if (divisors[key].size() == 0) {
		return 0;
	}
	set<ll> state;
	for (auto d : divisors[key]) {
		if (d % 2 == 0)
			state.insert(0);
		else
			state.insert(cal_grunt(key / d, cache));
	}
	ll res = mex(state);
	cache[key] = res;
	return res;
}

void solve()
{
	ll n, x;
	cin >> n;
	ll res = 0;
	for (ll i = 0; i < n; i++) {
		cin >> x;
		unordered_map<ll, ll> cache;
		res ^= cal_grunt(x, cache);
	}
	if (res > 0) {
		cout << "1\n";
	} else {
		cout << "2\n";
	}
}

int main()
{
	// CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	build();

	int t;
	cin >> t;
	while (t--)
		solve();
}
