#include <bits/stdc++.h>
// #include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1e8 + 7;
const ll N = 2e6;

ll powmod(ll a, ll b)
{
	ll res = 1;
	while (b) {
		if (b & 1)
			res = res * a % MOD;
		a = a * a % MOD;
		b >>= 1;
	}
	return res;
}

ll fact[N + 1], ifact[N + 1];
void build()
{
	fact[0] = 1;
	for (ll i = 1; i <= N; i++) {
		fact[i] = fact[i - 1] * i % MOD;
	}
	ifact[N] = powmod(fact[N], MOD - 2);
	for (ll i = N - 1; i >= 0; i--) {
		ifact[i] = ifact[i + 1] * (i + 1) % MOD;
	}
}

ll catalan(ll n)
{
	return fact[2 * n] * ifact[n] % MOD * ifact[n + 1] % MOD;
}

bool is_perfect(ll n)
{
	ll count = -1;
	for (ll i = 2; i * i <= n; i++) {
		if (n % i != 0)
			continue;
		ll c = 0;
		while (n % i == 0) {
			c++;
			n /= i;
		}
		if (count == -1) {
			count = c;
			continue;
		}
		if (count != c)
			return false;
	}
	if (n > 1) {
		return false;
	}
	return count > 1;
}

void solve()
{
	ll a, b;
	cin >> a >> b;
	ll count = 0;
	for (ll i = a; i <= b; i++) {
		if (is_perfect(i))
			count++;
	}
	ll res = count == 0 ? 0 : catalan(count);
	cout << res << "\n";
}

int main()
{
	// CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();
	int t;
	cin >> t;
	for (ll i = 1; i <= t; i++) {
		cout << "Case " << i << ": ";
		solve();
	}
}
