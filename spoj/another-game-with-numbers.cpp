#include <bits/stdc++.h>
// #include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

ll gcd(ll a, ll b)
{
	tie(a, b) = make_pair(max(a, b), min(a, b));
	while (b) {
		tie(a, b) = make_pair(b, a % b);
	}
    return a;
}

ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
}

void solve()
{
	ll n, k;
	cin >> n >> k;
	vector<ll> a(k);
	for (ll i = 0; i < k; i++) {
		cin >> a[i];
	}
	ll res = 0;
	for (ll mask = 1; mask < (1 << k); mask++) {
		ll count = 0;
		ll x = 1;
		for (ll i = 0; i < k; i++) {
			if ((mask >> i) & 1) {
				x = lcm(x, a[i]);
				count++;
			}
		}
		ll cur = n / x;
		if (count % 2 == 1)
			res += cur;
		else
			res -= cur;
	}
	res = n - res;
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
