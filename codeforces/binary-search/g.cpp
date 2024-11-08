#include <bits/stdc++.h>
// #include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll n;
	cin >> n;
	vector<ll> a(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}
	sort(a.begin(), a.end());

	ll min_ops = LONG_LONG_MAX;
	for (ll j = 1; j < n; j++) {
		ll k = lower_bound(a.begin() + j, a.end(), a[j - 1] + a[j]) - a.begin();
		k--;
		ll cur_ops = n - (2 + k - j);
		min_ops = min(min_ops, cur_ops);
	}
	cout << min_ops << "\n";
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
