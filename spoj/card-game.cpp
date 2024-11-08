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

ll nCk(ll n, ll k)
{
	return fact[n] * ifact[k] % MOD * ifact[n - k] % MOD;
}

void solve()
{
	int n, k;
	cin >> n >> k;
	vector<ll> a(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}
	sort(a.begin(), a.end());

	ll res = 0;
	for (ll i = k - 1; i < n; i++) {
		ll cur = a[i] % MOD * nCk(i, k - 1) % MOD;
		res = (res + cur) % MOD;
	}
	cout << res << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();
	int t;
	cin >> t;
	for (ll i = 1; i <= t; i++) {
		cout << "Case #" << i << ": ";
		solve();
	}
}
