#include <bits/stdc++.h>
// #include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

short decode(ll a)
{
	short state = 0;
	while (a > 0) {
		short digit = a % 10;
		state = state | (1 << digit);
		a /= 10;
	}
	return state;
}

ll nC2(ll n)
{
	if (n < 2)
		return 0;
	return n * (n - 1) / 2;
}

void solve()
{
	ll n, x;
	cin >> n;
	vector<short> states(n);
	for (ll i = 0; i < n; i++) {
		cin >> x;
		states[i] = decode(x);
	}
	ll res = 0;
	for (ll mask = 1; mask < (1 << 10); mask++) {
		ll count = 0;
		for (ll i = 0; i < n; i++) {
			if ((mask & states[i]) == mask) {
				count++;
			}
		}
		short bit_count = __builtin_popcount(mask);
		if (bit_count % 2 == 1) {
			res += nC2(count);
		} else {
			res -= nC2(count);
		}
	}
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
