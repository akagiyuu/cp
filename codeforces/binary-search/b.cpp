#include <algorithm>
#include <bits/stdc++.h>
// #include <cpp-dump.hpp>

using namespace std;

typedef unsigned long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll n, q;
	cin >> n >> q;
	vector<ll> a(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}
	vector<ll> ms(n);
	ms[0] = a[0];
	for (ll i = 1; i < n; i++) {
		ms[i] = max(ms[i - 1], a[i]);
	}
	vector<ll> prefix(n);
	prefix[0] = a[0];
	for (ll i = 1; i < n; i++) {
		prefix[i] = prefix[i - 1] + a[i];
	}
	while (q--) {
		ll l;
		cin >> l;
        ll j = upper_bound(ms.begin(), ms.end(), l) - ms.begin();
        if(j == 0) {
            cout << 0 << " ";
            continue;
        }
        j--;
        cout << prefix[j] << " ";
	}
    cout << "\n";
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
