#include <bits/stdc++.h>
#include <cpp-dump.hpp>

typedef long long ll;

const ll MOD = 1e2;

using namespace std;

ll cal_f(ll n)
{
	ll a = 0;
	ll b = 1;
	for (ll i = 2; i <= n; i++) {
		ll c = (a + b) % MOD;
		a = b;
		b = c;
	}
    return b;
}

ll f()
{
	ll a = 0;
	ll b = 1;
	for (ll i = 2;; i++) {
		ll c = (a + b) % MOD;
		a = b;
		b = c;
		if (a == 0 && b == 1)
			return i - 1;
	}
}

void solve()
{
	set<ll> f;
	f.insert(0);
	f.insert(1);
	ll a = 1;
	ll b = 1;
	ll i = 3;
	while (true) {
		ll c = (a + b) % MOD;
		a = b;
		b = c;
		if (f.find(c) != f.end()) {
			cout << i << "->" << c << "\n";
			break;
		}
		i += 1;
		f.insert(c);
	}
}

int main()
{
	CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	// ios_base::sync_with_stdio(false);
	// cin.tie(NULL);
	// cout.tie(NULL);

	auto p = cal_f(15000000000000);
	cout << p << "\n";
	// solve();
}
