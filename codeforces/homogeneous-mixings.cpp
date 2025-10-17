#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 998244353;
const ll root = 15311432;
const ll root_1 = 469870224;
const ll root_pw = 1 << 23;
const ll N = 1e6;
const ll M = 26;

ll fact[N], ifact[N];

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

void build()
{
	fact[0] = 1;
	for (ll i = 1; i < N; i++) {
		fact[i] = fact[i - 1] * i % MOD;
	}

	ifact[N - 1] = binpow(fact[N - 1], MOD - 2);
	for (ll i = N - 2; i >= 0; i--) {
		ifact[i] = ifact[i + 1] * (i + 1) % MOD;
	}
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
		ll n_1 = binpow(n, MOD - 2);
		for (ll &x : a)
			x = 1ll * x * n_1 % MOD;
	}
}
vector<ll> multiply(const vector<ll> &a, const vector<ll> &b, ll need)
{
	if (a.empty() || b.empty())
		return {};
	ll n = 1;
	while (n < need)
		n <<= 1;

	vector<ll> fa(n), fb(n);
	for (size_t i = 0; i < a.size(); ++i)
		fa[i] = a[i] % MOD;
	for (size_t i = 0; i < b.size(); ++i)
		fb[i] = b[i] % MOD;

	fft(fa, false);
	fft(fb, false);
	for (int i = 0; i < n; ++i)
		fa[i] = fa[i] * fb[i] % MOD;
	fft(fa, true);

	// fa.resize(need);

	return fa;
}

ll nCk(ll n, ll k)
{
	if (k < 0 || n < k) {
		return 0;
	}

	return fact[n] * ifact[k] % MOD * ifact[n - k] % MOD;
}

void solve()
{
	string s;
	cin >> s;
	ll n = s.size();
	array<ll, M> f;
	for (ll i = 0; i < M; i++) {
		f[i] = 0;
	}
	for (auto c : s) {
		f[c - 'a']++;
	}

	ll nf = 1;
	while (nf < n + 1)
		nf <<= 1;

	vector<ll> t(nf);
	t[0] = 1;
	fft(t, false);

	for (ll i = 0; i < M; i++) {
		ll c = f[i];
		if (c == 0)
			continue;
		vector<ll> a(nf);
		for (ll j = 1; j <= c; j++) {
			a[j] = nCk(c - 1, j - 1) * ifact[j] % MOD;
		}
		fft(a, false);
		for (ll i = 0; i < nf; i++) {
			t[i] = (t[i] * a[i]) % MOD;
		}
	}
	fft(t, true);
	for (ll i = 0; i < n + 1; i++) {
		t[i] = (t[i] * fact[i]) % MOD;
	}

	ll res = 0;
	for (ll i = 1; i <= n; i++) {
		if ((n - i) % 2 == 0) {
			res = (res + t[i]) % MOD;
		} else {
			res = (res - t[i] + MOD) % MOD;
		}
	}
	for (ll i = 0; i < M; i++) {
		res = (res * fact[f[i]]) % MOD;
	}
	res = (res * ifact[n]) % MOD;
	res = (1 - res + MOD) % MOD;
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
