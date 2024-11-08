#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;
const ll N = 1e7;

ll fact[N + 1];
ll ifact[N + 1];

ll pow(ll a, ll b)
{
	a %= MOD;
	b %= MOD - 1;
	ll res = 1;
	while (b) {
		if (b & 1)
			res = res * a % MOD;

		a = a * a % MOD;
		b >>= 1;
	}
	return res;
}

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

ll binomial(ll n, ll k)
{
	return fact[n] * ifact[k] % MOD * ifact[n - k] % MOD;
}

void solve()
{
	ll n, a, b, d;
	while (cin >> n) {
		cin >> a >> b >> d;
		ll res = binomial(n, a) * pow(binomial(b, d), a) % MOD;
		cout << res << "\n";
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();
	solve();
}
