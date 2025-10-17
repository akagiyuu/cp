#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 998244353;
const ll root = 15311432;
const ll root_1 = 469870224;
const ll root_pw = 1 << 23;

ll binpow(ll a, ll b)
{
	ll res = 1;
	while (b) {
		if (b & 1)
			res = (res * a) % MOD;
		a = (a * a) % MOD;
		b >>= 1;
	}
	return res;
}

ll inv(ll a)
{
	return binpow(a, MOD - 2);
}

void fft(vector<ll> &a, bool invert)
{
	ll n = a.size(), L = __builtin_ctz(n);

	vector<ll> rev(n);
	for (ll i = 0; i < n; i++) {
		rev[i] = (rev[i >> 1] | (i & 1) << L) >> 1;
		if (i < rev[i])
			swap(a[i], a[rev[i]]);
	}

	for (ll len = 2; len <= n; len <<= 1) {
		ll wlen = invert ? root_1 : root;
		for (ll i = len; i < root_pw; i <<= 1)
			wlen = (ll)(1LL * wlen * wlen % MOD);

		for (ll i = 0; i < n; i += len) {
			ll w = 1;
			for (ll j = 0; j < len / 2; j++) {
				ll u = a[i + j];
				ll v = 1ll * a[i + j + len / 2] * w % MOD;
				a[i + j] = u + v < MOD ? u + v : u + v - MOD;
				a[i + j + len / 2] = u - v >= 0 ? u - v : u - v + MOD;
				w = 1ll * w * wlen % MOD;
			}
		}
	}

	if (invert) {
		ll n_1 = inv(n);
		for (ll &x : a)
			x = 1ll * x * n_1 % MOD;
	}
}
vector<ll> multiply(vector<ll> const &a, vector<ll> const &b)
{
	vector<ll> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	ll n = 1;
	while (n < a.size() + b.size())
		n <<= 1;
	fa.resize(n);
	fb.resize(n);

	fft(fa, false);
	fft(fb, false);
	for (int i = 0; i < n; i++)
		fa[i] = (fa[i] * fb[i]) % MOD;
	fft(fa, true);

	return fa;
}

void solve()
{
	ll n;
	cin >> n;
	vector<ll> a(2 * n - 1), x(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[n - 1 - i];
	}
	for (ll i = 0; i < n; i++) {
		cin >> a[i + n - 1];
	}
	for (ll i = 0; i < n; i++) {
		cin >> x[n - 1 - i];
	}
	auto p = multiply(a, x);
	for (ll i = 0; i < n; i++) {
		cout << p[2 * n - 2 - i] << "\n";
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
