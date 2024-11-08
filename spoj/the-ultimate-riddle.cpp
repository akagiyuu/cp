#include <bits/stdc++.h>
// #include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const int N = 50;

vector<int> ps;

void build()
{
	array<int, N + 1> sieve;
    sieve.fill(0);
	for (ll i = 2; i <= N; i++) {
		if (sieve[i] == 0) {
			sieve[i] = i;
			ps.push_back(i);
		}
		for (auto p : ps) {
			int next = p * i;
			if (next > N)
				break;
			sieve[next] = p;
			if (p == sieve[i])
				break;
		}
	}
}

ll inv(ll a, ll m)
{
	ll original = m;
	ll x = 1, y = 0, x1 = 0, y1 = 1;
	while (m) {
		ll q = a / m;
		tie(a, m) = make_pair(m, a % m);
		tie(x, x1) = make_pair(x1, x - x1 * q);
		tie(y, y1) = make_pair(y1, y - y1 * q);
	}
	if (x < 0)
		x = (x % original + original) % original;
	return x;
}

ll cur_m = -1;
ll fact[N];
ll ifact[N];

void build_fact(ll m)
{
	fact[0] = 1;
	for (ll i = 1; i < m; i++) {
		fact[i] = fact[i - 1] * i % m;
	}
	ifact[m - 1] = inv(fact[m - 1], m);
	for (ll i = m - 2; i >= 0; i--) {
		ifact[i] = ifact[i + 1] * (i + 1) % m;
	}
}

ll nCk_prime(ll n, ll k, ll m)
{
	if (n < k)
		return 0;
	return fact[n] * ifact[k] % m * ifact[n - k] % m;
}

ll nCk_lucas(ll n, ll k, ll m)
{
	if (n < k)
		return 0;
	build_fact(m);
	ll res = 1;
	while (n) {
		res = res * nCk_prime(n % m, k % m, m) % m;
		n /= m;
		k /= m;
	}
	return res;
}

void solve()
{
	ll n, k, m;
	cin >> n >> k >> m;
	ll res = 0;
	for (auto p : ps) {
		if (m % p != 0)
			continue;
		ll r = nCk_lucas(n, k, p);
		res = (res + r * inv(m / p, p) % m * m / p % m) % m;
	}
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
	while (t--)
		solve();
}
