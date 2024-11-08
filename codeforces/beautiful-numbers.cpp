#include <bits/stdc++.h>

typedef long long ll;

const ll MOD = 1000000007;
const ll N = 1e6;

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

ll fact[N + 1], ifact[N + 1];

void build()
{
	fact[0] = 1;
	for (ll i = 1; i <= N; i++) {
		fact[i] = i * fact[i - 1];
		fact[i] %= MOD;
	}
	ifact[N] = pow(fact[N], MOD - 2);
	for (ll i = N - 1; i >= 0; i--) {
		ifact[i] = (ifact[i + 1] * (i + 1)) % MOD;
	}
}

ll n_choose_k(ll n, ll k)
{
	return fact[n] * ifact[k] % MOD * ifact[n - k] % MOD;
}

bool is_good(ll x, ll a, ll b)
{
	while (x > 0) {
		short digit = x % 10;
		if (digit != a && digit != b) {
			return false;
		}
		x /= 10;
	}
	return true;
}

void solve()
{
	ll a, b, n;
	cin >> a >> b >> n;

	ll res = 0;
	for (ll i = 0; i <= n; i++) {
		ll cur = i * a + (n - i) * b;
		if (!is_good(cur, a, b)) {
			continue;
		}
		res += n_choose_k(n, i);
		res %= MOD;
	}
	cout << res << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();

	solve();
}
