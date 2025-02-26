#include <bits/stdc++.h>
// #include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

vector<pair<ll, ll> > fracs;

void build(ll n)
{
	fracs.clear();
	fracs.push_back(make_pair(1, n));

	auto pre = make_pair(0, 1);
	auto cur = fracs[0];
	while (true) {
		auto next = make_pair(((pre.second + n) / cur.second) * cur.first - pre.first,
				      ((pre.second + n) / cur.second) * cur.second - pre.second);
		pre = cur;
		cur = next;
		if (next.first >= next.second)
			break;
		fracs.push_back(next);
	}
}

pair<ll, ll> solve(ll n, ll k)
{
	if (n == 1) {
		return make_pair(k, 1);
	}
	build(n);
	ll length = fracs.size();
	ll frac_index = k % (length + 1) - 1;
	auto frac = frac_index >= 0 ? fracs[frac_index] : make_pair(0ll, 1ll);
	ll ll_part = k / (length + 1);
	frac.first += ll_part * frac.second;
	return frac;
}

int main()
{
	// CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	// next_level();
	// next_level();
	// cpp_dump(fracs);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	ll t;
	cin >> t;
	while (t--) {
		ll n, k;
		cin >> n >> k;
		auto res = solve(n, k);
		cout << res.first << " " << res.second << "\n";
	}
	//
	// ll pre_n = 0;
	// for (ll i = 0; i < t; i++) {
	// 	ll cur_n = inputs[i].first;
	// 	ll k = inputs[i].second;
	//
	// 	for (ll j = pre_n + 1; j <= cur_n; j++) {
	// 		for (ll k = 1; k < j; k++) {
	// 			if (gcd(k, j) != 1)
	// 				continue;
	// 			fracs.insert(Fraction{ .num = k, .denom = j });
	// 		}
	// 	}
	// 	ll length = fracs.size();
	// 	ll frac_index = k % (length + 1) - 1;
	// 	auto frac = frac_index >= 0 ? *next(fracs.begin(), frac_index) : Fraction{ .num = 0, .denom = 1 };
	// 	ll ll_part = k / (length + 1);
	// 	frac.num += ll_part * frac.denom;
	// 	cout << frac.num << " " << frac.denom << "\n";
	// }
}
