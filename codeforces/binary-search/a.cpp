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
	ll sum = 0;
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
		sum += a[i];
	}
    if(n == 1 || n == 2) {
        cout << -1 << "\n";
        return;
    }
	sort(a.begin(), a.end());
	for (ll i = 0; i < n; i++) {
		a[i] = 2 * n * a[i] - sum;
	}
	ll mid = n / 2;
    ll res = max(a[mid] + 1, 0ll);
	cout << res << "\n";
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
