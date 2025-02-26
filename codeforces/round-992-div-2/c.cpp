#include <bits/stdc++.h>
#include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

ll cal(vector<ll> &a)
{
	ll res = 0;

	ll n = a.size();
	for (ll i = 0; i < n; i++) {
		ll cur = a[i];
		res += cur;

		for (ll j = i + 1; j < n; j++) {
			cur = min(cur, a[j]);
			res += cur;
		}
	}

	return res;
}

void test(vector<ll> &a)
{
	vector<vector<ll> > all;
	do {
		all.push_back(a);
	} while (next_permutation(a.begin(), a.end()));

	vector<pair<ll, ll> > vals;
	map<ll, ll> vals2;
	for (ll i = 0; i < all.size(); i++) {
        ll res = cal(all[i]);
		vals.push_back(make_pair(i, res));
		vals2[res]++;
	}

	sort(vals.begin(), vals.end(), [](pair<ll, ll> a, pair<ll, ll> b) {
		if (a.second == b.second) {
			return a.first < b.first;
		}

		return a.second < b.second;
	});

	for (ll i = 0; i < all.size(); i++) {
		cpp_dump(all[vals[i].first]);
		cpp_dump(vals[i].second);
	}

	for (auto const &[key, val] : vals2) {
		std::cout << key // string (key)
			  << ':' << val // string's value
			  << std::endl;
	}
}

void solve()
{
}

int main()
{
	CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	vector<ll> a = { 1, 2, 3, 4, 5 };
	test(a);
	// int t;
	// cin >> t;
	// while (t--)
	// 	solve();
}
