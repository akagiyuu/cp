#include <bits/stdc++.h>

typedef long long ll;

const ll MOD = 1000000007;

using namespace std;

pair<ll, ll> f(ll n)
{
	if (n == 0)
		return { 0, 1 };
	auto p = f(n >> 1);
	ll a = p.first * (2 * p.second % MOD - p.first + MOD) % MOD;
	ll b = p.first * p.first % MOD + p.second * p.second % MOD;
	if (n & 1)
		return { b, (a + b) % MOD };
	return { a, b };
}

ll pow(ll a, ll b)
{
	ll res = 1;
	while (b) {
		if (b % 2 == 1) {
			res = (res * a) % MOD;
		}
		a = (a * a) % MOD;
		b /= 2;
	}
	return res;
}

const ll N = 1e7;

ll fact[N + 1], ifact[N + 1];

void build()
{
	fact[0] = 1;
	for (ll i = 1; i <= N; i++) {
		fact[i] = fact[i - 1] * i % MOD;
	}
	ifact[N] = pow(fact[N], MOD - 2);
	for (ll i = N - 1; i >= 0; i--) {
		ifact[i] = ifact[i + 1] * (i + 1) % MOD;
	}
}

ll cal_fact(ll n)
{
	if (n <= N) {
		return fact[n];
	}
	ll v = fact[N];
	for (ll i = N + 1; i <= n; i++) {
		v = (v * i) % MOD;
	}
	return v;
}

ll cal_inv_fact(ll n)
{
	if (n <= N)
		return ifact[n];
	return pow(cal_fact(n), MOD - 2);
}

ll n_choose_k(ll n, ll k)
{
	return cal_fact(n) * cal_inv_fact(n - k) % MOD * cal_inv_fact(k) % MOD;
}

void solve()
{
	build();
	ll k, l, r;
	cin >> k >> l >> r;
	auto [cur, next] = f(l + 2);
	ll res = 0;
	for (ll i = l; i <= r; i++) {
		res = (res + n_choose_k(cur, k)) % MOD;
		tie(cur, next) = make_pair(next, (cur + next) % MOD);
	}
	cout << res << "\n";
}

int main()
{
	solve();
}
