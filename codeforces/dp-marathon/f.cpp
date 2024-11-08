#include <bits/stdc++.h>
// #include "/home/yuu/Code/competitive_programming/cpp-dump/cpp-dump.hpp"

typedef long long ll;

const ll MOD = 998244353;

using namespace std;

const int N = 1e6;
ll fact[N + 5];
ll ifact[N + 5];

ll pow(ll b, ll p)
{
	ll result = 1;
	while (p > 0) {
		if (p % 2 == 1) {
			result *= b;
			result %= MOD;
		}
		p /= 2;
		b *= b;
		b %= MOD;
	}

	return result;
}

const ll cached = (1ll << 62) % MOD;

ll pow_2(ll p)
{
	ll quotient = pow(cached, p / 62);
	ll remainder = (1ll << (p % 62)) % MOD;
	return (quotient * remainder) % MOD;
}

void build()
{
	fact[0] = 1;
	for (ll i = 1; i <= N; i++) {
		fact[i] = (fact[i - 1] * i) % MOD;
	}
	ifact[N] = pow(fact[N], MOD - 2);
	for (ll i = N - 1; i >= 0; i--) {
		ifact[i] = (ifact[i + 1] * (i + 1)) % MOD;
	}
}

ll binomial(ll n, ll k)
{
	return (fact[n] * ifact[n - k] * ifact[k]) % MOD;
}

void solve()
{
	ll n, k;
	cin >> n >> k;
	ll a = min(n - k / 2, k / 2);
	ll b = max(n - k / 2, k / 2);
	cout << (pow_2(n - k / 2 + 1) * binomial(b + 1, a)) % MOD;
}

int main()
{
	build();
	solve();
}
