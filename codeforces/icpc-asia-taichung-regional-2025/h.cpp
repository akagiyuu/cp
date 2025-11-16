#include <bits/stdc++.h>

#define int long long

using namespace std;

const int MOD1 = 998244353;
const int ROOT1 = 3;
const int MOD2 = 1004535809;
const int ROOT2 = 3;
const int BASE1 = 9113823 % MOD1;
const int BASE2 = 9726637 % MOD2;

int mod_pow(int a, int e, int mod)
{
	int r = 1, x = a;
	while (e) {
		if (e & 1)
			r = (r * x) % mod;
		x = (x * x) % mod;
		e >>= 1;
	}
	return r;
}

void ntt(vector<int> &a, int mod, int root, bool invert)
{
	int n = a.size();
	int lg = 0;
	while ((1 << lg) < n)
		++lg;
	vector<int> rev(n);
	for (int i = 0; i < n; ++i) {
		rev[i] = 0;
		for (int j = 0; j < lg; ++j)
			if (i & (1 << j))
				rev[i] |= 1 << (lg - 1 - j);
	}
	for (int i = 0; i < n; ++i)
		if (i < rev[i])
			swap(a[i], a[rev[i]]);
	for (int len = 1; len < n; len <<= 1) {
		int wlen = mod_pow(root, (mod - 1) / (len << 1), mod);
		if (invert)
			wlen = mod_pow(wlen, mod - 2, mod);
		for (int i = 0; i < n; i += (len << 1)) {
			int w = 1;
			for (int j = 0; j < len; ++j) {
				int u = a[i + j];
				int v = (a[i + j + len] * w) % mod;
				int x = u + v;
				if (x >= mod)
					x -= mod;
				int y = u - v;
				if (y < 0)
					y += mod;
				a[i + j] = x;
				a[i + j + len] = y;
				w = (w * wlen) % mod;
			}
		}
	}
	if (invert) {
		int inv_n = mod_pow(n, mod - 2, mod);
		for (int &x : a)
			x = (int)(x * 1ll * inv_n % mod);
	}
}

vector<int> linear_convolution_mod(const vector<int> &a, const vector<int> &b, int mod, int root)
{
	int n = a.size();
	int m = b.size();
	int need = n + m - 1;
	int sz = 1;
	while (sz < need)
		sz <<= 1;
	vector<int> fa(sz), fb(sz);
	for (int i = 0; i < n; ++i)
		fa[i] = (a[i] % mod + mod) % mod;
	for (int i = 0; i < m; ++i)
		fb[i] = (b[i] % mod + mod) % mod;
	ntt(fa, mod, root, false);
	ntt(fb, mod, root, false);
	for (int i = 0; i < sz; ++i)
		fa[i] = (int)((fa[i] * 1ll * fb[i]) % mod);
	ntt(fa, mod, root, true);
	fa.resize(need);
	return fa;
}

vector<int> circular_convolution_mod(const vector<int> &a, const vector<int> &b, int mod, int root)
{
	int n = a.size();
	vector<int> lin = linear_convolution_mod(a, b, mod, root);
	vector<int> res(n);
	for (int i = 0; i < n; ++i) {
		int v = lin[i];
		if (i + n < (int)lin.size())
			v += lin[i + n];
		v %= mod;
		res[i] = v;
	}
	return res;
}

int rot_r(int j, int t, int k)
{
	if (t == 0)
		return j;
	return ((j >> t) | ((j & ((1ll << t) - 1ll)) << (k - t)));
}

void solve()
{
	int k, t;
	string s;
	cin >> k >> t >> s;
	t %= k;
	int n = 1ll << k;
	vector<int> idx(n);
	for (int i = 0; i < n; ++i)
		idx[i] = rot_r(i, t, k);
	vector<int> pos(n);
	for (int j = 0; j < n; ++j)
		pos[idx[j]] = j;
	string s2 = s + s;
	const unsigned char *sc = (const unsigned char *)s2.c_str();
	vector<int> pow1_mod1(n), pow1_mod2(n);
	pow1_mod1[0] = 1;
	pow1_mod2[0] = 1;
	for (int i = 1; i < n; ++i) {
		pow1_mod1[i] = (int)(pow1_mod1[i - 1] * 1ll * BASE1 % MOD1);
		pow1_mod2[i] = (int)(pow1_mod2[i - 1] * 1ll * BASE2 % MOD2);
	}
	vector<int> A1(n), A2(n), Bd1(n), Bd2(n);
	for (int u = 0; u < n; ++u) {
		A1[u] = pow1_mod1[pos[u]];
		A2[u] = pow1_mod2[pos[u]];
		Bd1[u] = (int)sc[u];
		Bd2[u] = (int)sc[u];
	}
	vector<int> Brev1(n), Brev2(n);
	for (int u = 0; u < n; ++u) {
		Brev1[u] = Bd1[(n - u) % n];
		Brev2[u] = Bd2[(n - u) % n];
	}
	vector<int> conv1 = circular_convolution_mod(Brev1, A1, MOD1, ROOT1);
	vector<int> conv2 = circular_convolution_mod(Brev2, A2, MOD2, ROOT2);
	vector<unsigned long long> H1(n), H2(n);
	for (int i = 0; i < n; ++i) {
		unsigned long long x1 = (unsigned long long)conv1[i];
		unsigned long long x2 = (unsigned long long)conv2[i];
		H1[i] = (x1 << 32) ^ x2;
		H2[i] = ((x1 * 0x9ddfea08eb382d69ULL) ^ (x2 * 0xc2b2ae3d27d4eb4fULL)) + 1469598103934665603ULL;
	}
	auto char_at = [&](int i, int j) -> unsigned char { return (unsigned char)sc[i + idx[j]]; };
	auto equal_full = [&](int a, int b) -> bool { return H1[a] == H1[b] && H2[a] == H2[b]; };
	auto lcp = [&](int a, int b) -> int {
		if (a == b)
			return n;
		if (equal_full(a, b))
			return n;
		int lo = 0, hi = n;
		while (lo < hi) {
			int mid = (lo + hi + 1) >> 1;
			bool ok = true;
			int j = 0;
			for (; j + 7 < mid; j += 8) {
				if (char_at(a, j) != char_at(b, j)) {
					ok = false;
					break;
				}
				if (char_at(a, j + 1) != char_at(b, j + 1)) {
					ok = false;
					break;
				}
				if (char_at(a, j + 2) != char_at(b, j + 2)) {
					ok = false;
					break;
				}
				if (char_at(a, j + 3) != char_at(b, j + 3)) {
					ok = false;
					break;
				}
				if (char_at(a, j + 4) != char_at(b, j + 4)) {
					ok = false;
					break;
				}
				if (char_at(a, j + 5) != char_at(b, j + 5)) {
					ok = false;
					break;
				}
				if (char_at(a, j + 6) != char_at(b, j + 6)) {
					ok = false;
					break;
				}
				if (char_at(a, j + 7) != char_at(b, j + 7)) {
					ok = false;
					break;
				}
			}
			if (ok) {
				for (; j < mid; ++j) {
					if (char_at(a, j) != char_at(b, j)) {
						ok = false;
						break;
					}
				}
			}
			if (ok)
				lo = mid;
			else
				hi = mid - 1;
		}
		return lo;
	};
	auto less_than = [&](int a, int b) -> bool {
		if (a == b)
			return false;
		int L = lcp(a, b);
		if (L == n)
			return false;
		unsigned char ca = char_at(a, L);
		unsigned char cb = char_at(b, L);
		return ca < cb;
	};
	int best = 0;
	for (int i = 1; i < n; ++i)
		if (less_than(i, best))
			best = i;
	string out;
	out.resize(n);
	for (int j = 0; j < n; ++j)
		out[j] = (char)char_at(best, j);
	cout << out << '\n';
}

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	solve();
	return 0;
}
