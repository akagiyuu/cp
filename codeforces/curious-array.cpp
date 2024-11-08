#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;
const ll N = 1e5 + 100;

ll fact[N + 1];
ll ifact[N + 1];

ll pow(ll a, ll b)
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

ll inv(ll b)
{
	ll a = MOD;
	b %= MOD;
	ll x = 1, y = 0, x1 = 0, y1 = 1;
	while (b) {
		ll q = a / b;
		tie(a, b) = make_pair(b, a % b);
		tie(x, x1) = make_pair(x1, x - x1 * q);
		tie(y, y1) = make_pair(y1, y - y1 * q);
	}
	return y;
}

void build()
{
	fact[0] = 1;
	for (ll i = 1; i <= N; i++) {
		fact[i] = fact[i - 1] * i % MOD;
	}

	ifact[N] = inv(fact[N]);
	for (ll i = N - 1; i >= 0; i--) {
		ifact[i] = ifact[i + 1] * (i + 1) % MOD;
	}
}

ll binomial_cof(ll n, ll k)
{
	if (n < k)
		return 0;
	return fact[n] * ifact[k] % MOD * ifact[n - k] % MOD;
}

void solve()
{
	ll n, m;
	cin >> n >> m;
	vector<vector<ll> > a(102, vector<ll>(n, 0));
	for (ll i = 0; i < n; i++) {
		cin >> a[0][i];
	}
	while (m--) {
		ll l, r, k;
		cin >> l >> r >> k;
		l--;
		r--;
		a[k + 1][l] = (a[k + 1][l] + 1) % MOD;
		if (r + 1 >= n)
			continue;
		for (ll i = 1; i <= k + 1; i++) {
			a[i][r + 1] = (a[i][r + 1] - binomial_cof(r - l + k + 1 - i, k + 1 - i)) % MOD;
		}
	}
	for (ll i = 100; i >= 1; i--) {
		a[i][0] = (a[i][0] + a[i + 1][0]) % MOD;
		for (ll j = 1; j < n; j++) {
			a[i][j] = (a[i][j] + a[i][j - 1] + a[i + 1][j]) % MOD;
		}
	}
	for (ll i = 0; i < n; i++) {
		a[0][i] = (a[0][i] + a[1][i]) % MOD;
		if (a[0][i] < 0)
			a[0][i] = (MOD + a[0][i]) % MOD;
		cout << a[0][i] << " ";
	}
	cout << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();
	solve();
}
