#include <bits/stdc++.h>
#include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

ll solve()
{
	ll n, t;
	cin >> n >> t;
	vector<ll> a(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}
	vector<ll> prefix(n);
	prefix[0] = a[0];
	for (ll i = 1; i < n; i++) {
		prefix[i] = prefix[i - 1] + a[i];
	}
	for (ll i = -1; i <= n - 2; i++) {
	}
	return n;
}

int main()
{
	CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cout << solve();
}
