#include <bits/stdc++.h>
#include <cpp-dump.hpp>

typedef unsigned __int128 ll;

const ll MOD = 1000000007;

using namespace std;

ll f(ll x, ll c, ll mod)
{
	return (x * x % mod + c) % mod;
}

ll pollard_rho(ll n, ll x0 = 2, ll c = 1)
{
	ll x = x0;
	ll y = x0;
	ll g = 1;
	while (g == 1) {
		x = f(x, c, n);
		y = f(y, c, n);
		y = f(y, c, n);
		g = gcd(x > y ? y - x : x - y, n);
	}
	return g;
}

vector<ll> build(ll n)
{
	vector<ll> sieve(n + 1, 0);
	vector<ll> ps;

	for (ll i = 2; i <= n; i++) {
		if (sieve[i] == 0) {
			sieve[i] = i;
			ps.push_back(i);
		}
		for (auto p : ps) {
			if (i * p > n) {
				break;
			}
			sieve[i * p] = p;
			if (sieve[i] == p) {
				break;
			}
		}
	}
	return sieve;
}

map<long long, long long> factorize(ll n, vector<ll> &sieve)
{
	map<long long, long long> res;
	while (n > 0) {
		ll factor = sieve[n];
		ll count = 0;
		while (n % factor == 0) {
			count++;
			n /= factor;
		}
		res[factor] = count;
	}
	return res;
}

void solve(vector<ll> &sieve)
{
	long long n;
	cin >> n;
	cpp_dump(factorize((ll)n, sieve));
}

int main()
{
	CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	vector<ll> sieve = build(77145199750673);

	// int t;
	// cin >> t;
	// while (t--)
	while (true)
		solve(sieve);
}
