#include <bits/stdc++.h>

typedef long long ll;

const ll MOD = 1000000007;
const ll N = 1e7;

using namespace std;

ll pow(ll a, ll b)
{
	ll res = 1;
	while (b > 0) {
		if (b % 2 == 1) {
			res *= a;
			res %= MOD;
		}
		a *= a;
		a %= MOD;
		b /= 2;
	}
	return res;
}

ll gcd(ll a, ll b, ll &x, ll &y)
{
	ll x1 = 0, y1 = 1;
	while (b > 0) {
		ll q = a / b;
		tie(x, x1) = make_pair(x1, x - q * x1);
		tie(y, y1) = make_pair(y1, y - q * y1);
		tie(a, b) = make_pair(b, a - q * b);
	}
	return a;
}

ll inverse(ll a)
{
	ll x = 1, y = 0;
	gcd(a, MOD, x, y);
	return x;
}

ll fact[N + 1];
ll ifact[N + 1];

void build()
{
	fact[0] = 1;
	for (ll i = 1; i <= N; i++) {
		fact[i] = fact[i - 1] * i % MOD;
	}
	ifact[N] = inverse(fact[N]);
	for (ll i = N - 1; i >= 0; i--) {
		ifact[i] = ifact[i + 1] * (i + 1) % MOD;
	}
}

ll lagrange_interpolation(vector<ll> &ys, ll x)
{
	ll n = ys.size();
	if (x < n) {
		return ys[x];
	}

	vector<ll> prefix(n);
	prefix[0] = 1;
	for (ll i = 1; i < n; i++) {
		prefix[i] = prefix[i - 1] * (x - (i - 1)) % MOD;
	}

	vector<ll> suffix(n);
	suffix[n - 1] = 1;
	for (ll i = n - 2; i >= 0; i--) {
		suffix[i] = suffix[i + 1] * (x - (i + 1)) % MOD;
	}

	ll res = 0;
	for (ll i = 0; i < n; i++) {
		ll cur = ys[i] % MOD;
		cur = cur * prefix[i] % MOD;
		cur = cur * suffix[i] % MOD;
		cur = cur * ifact[n - i - 1] % MOD;
		cur = cur * ifact[i] % MOD;
		if ((n - i + 1) % 2 == 1) {
			cur = MOD - cur;
		}
		cur %= MOD;
		res = (res + cur) % MOD;
	}
	return (res + MOD) % MOD;
}

void solve()
{
	ll n, k;
	cin >> n >> k;
	vector<ll> sums(k + 2);
	ll res = 0;
	for (ll i = 1; i <= k + 2; i++) {
		res += pow(i, k);
		res %= MOD;
		sums[i - 1] = res;
	}
	cout << lagrange_interpolation(sums, n - 1) << "\n";
}

int main()
{
	build();
	solve();
}
