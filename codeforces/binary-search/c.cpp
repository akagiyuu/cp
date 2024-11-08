#include <bits/stdc++.h>
// #include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll n, t;
	cin >> n >> t;
	vector<ll> a(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
		if (i > 0)
			a[i] += a[i - 1];
	}
	ll max_book = 0;
	for (ll i = 0; i < n; i++) {
		ll left_sum = i == 0 ? 0 : a[i - 1];
		ll j = upper_bound(a.begin() + i, a.end(), t + left_sum) - a.begin();
		j--;
		max_book = max(max_book, j - i + 1);
	}
	cout << max_book;
}

int main()
{
	// CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
