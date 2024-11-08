#include <bits/stdc++.h>
// #include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll n, k, s, t;
	cin >> n >> k >> s >> t;
	map<ll, ll> cars;
	for (ll i = 0; i < n; i++) {
		ll v, c;
		cin >> c >> v;
		ll pre_c = cars[v];
		if (pre_c == 0)
			cars[v] = c;
		else
			cars[v] = min(pre_c, c);
	}

	vector<ll> g(k);
	for (ll i = 0; i < k; i++) {
		cin >> g[i];
	}
	sort(g.begin(), g.end());
	g.push_back(s);
	k++;
	for (ll i = k - 1; i >= 1; i--) {
		g[i] -= g[i - 1];
	}
	sort(g.begin(), g.end());

	vector<ll> doubleg(k);
	vector<ll> prefix_g(k);
	ll max_g = 0;
	prefix_g[0] = g[0];
	for (ll i = 0; i < k; i++) {
		if (i > 0)
			prefix_g[i] = prefix_g[i - 1] + g[i];
		doubleg[i] = 2 * g[i];
		max_g = max(max_g, g[i]);
	}

	auto cal_min_time = [k, prefix_g, doubleg, max_g](ll v) {
		if (v < max_g)
			return LONG_LONG_MAX;
		// ll res = 0;
		// for (ll i = 0; i < k; i++) {
		// 	res += max(gi, 3 * gi - v);
		// }
		//       return res;
		ll i = lower_bound(doubleg.begin(), doubleg.end(), v) - doubleg.begin();
		ll res = prefix_g[k - 1];
		res += 2 * (prefix_g[k - 1] - (i == 0 ? 0 : prefix_g[i - 1]));
		res -= (k - i) * v;
		return res;
	};

	ll res = LONG_LONG_MAX;
	for (auto [v, c] : cars) {
		ll min_time = cal_min_time(v);
		if (min_time <= t)
			res = min(res, c);
	}
    if(res == LONG_LONG_MAX) res = -1;
	cout << res;
}

int main()
{
	// CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
