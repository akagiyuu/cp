#include <bits/stdc++.h>
#include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;
const ll b = 12;

void solve()
{
	ll n;
	cin >> n;
	vector<ll> a(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}
	ll res = 0;
	for (ll i = 0; i < n; i++) {
		for (ll j = i + 1; j < n; j++) {
			res += __lg(a[i] ^ a[j]);

			// cpp_dump(a[i], a[j], __lg(a[i] ^ a[j]));
		}
	}
    cpp_dump(res);
}

int main()
{
	CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		solve();
}
