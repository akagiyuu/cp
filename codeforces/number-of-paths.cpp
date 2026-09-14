#include <bits/stdc++.h>

using namespace std;

#define int long long

typedef complex<double> cd;
const double PI = acos(-1.0);
const int N = 1ll << 17;
vector<cd> roots;
void init_fft()
{
	roots.resize(N >> 1);
	const double angle = 2.0 * PI / N;
	const cd step(cos(angle), sin(angle));
	roots[0] = cd(1.0, 0.0);
	for (int i = 1; i < N / 2; ++i)
		roots[i] = roots[i - 1] * step;
}
void fft(vector<cd> &a, bool invert)
{
	int n = a.size();
	int lg = __builtin_ctz(n);
	vector<int> rev(n);
	for (int i = 1; i < n; ++i)
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (lg - 1));
	for (int i = 0; i < n; ++i) {
		int j = rev[i];
		if (i < j)
			swap(a[i], a[j]);
	}
	for (int len = 2; len <= n; len <<= 1) {
		const int step = N / len;
		const int half = len >> 1;
		for (int i = 0; i < n; i += len) {
			for (int j = 0; j < half; ++j) {
				cd w = roots[j * step];
				if (invert)
					w = conj(w);
				cd u = a[i + j];
				cd v = a[i + j + half] * w;
				a[i + j] = u + v;
				a[i + j + half] = u - v;
			}
		}
	}
	if (invert)
		for (int i = 0; i < n; i++)
			a[i] /= n;
}
vector<cd> multiply(const vector<int> &a, const vector<int> &b)
{
	int N = a.size() + b.size() - 1;
	int sz = 1;
	while (sz < N)
		sz <<= 1;
	vector<cd> c(sz);
	for (int i = 0; i < a.size(); i++)
		c[i].real(a[i]);
	for (int i = 0; i < b.size(); i++)
		c[i].imag(b[i]);
	fft(c, false);
	vector<cd> d(sz);
	for (int i = 0; i < sz; i++) {
		auto x = c[i], y = conj(c[(sz - i) % sz]);
		d[i] = (x * x - y * y) * cd(0.0, -0.25);
	}
	fft(d, true);
	return d;
}

int n;
vector<vector<int> > adj;
vector<bool> removed;
vector<int> sz, res;
int calc_sz(int u, int p)
{
	sz[u] = 1;
	for (auto v : adj[u]) {
		if (v != p && !removed[v])
			sz[u] += calc_sz(v, u);
	}
	return sz[u];
}
int find_centroid(int u, int p, int total)
{
	for (auto v : adj[u]) {
		if (v != p && !removed[v] && sz[v] > total / 2)
			return find_centroid(v, u, total);
	}
	return u;
}
void build_dist(int u, int p, int d, vector<int> &cnt)
{
	if (d >= cnt.size())
		cnt.resize(d + 1, 0);
	cnt[d]++;
	for (auto v : adj[u]) {
		if (v != p && !removed[v])
			build_dist(v, u, d + 1, cnt);
	}
}
void process_centroid(int c)
{
	vector<int> cnt = { 1 };
	for (auto v : adj[c]) {
		if (removed[v])
			continue;
		vector<int> cur_cnt;
		build_dist(v, c, 1, cur_cnt);
		auto r = multiply(cnt, cur_cnt);
		if (r.size() > n)
			r.resize(n);
		while (!r.empty() && llround(real(r.back())) == 0)
			r.pop_back();
		for (int i = 0; i < r.size(); i++) {
			res[i] += llround(real(r[i]));
		}
		if (cnt.size() < cur_cnt.size())
			cnt.resize(cur_cnt.size(), 0);
		for (int i = 0; i < cur_cnt.size(); i++) {
			cnt[i] += cur_cnt[i];
		}
	}
}
void decompose(int u)
{
	int total = calc_sz(u, -1);
	int c = find_centroid(u, -1, total);
	removed[c] = true;
	process_centroid(c);
	for (auto v : adj[c]) {
		if (!removed[v])
			decompose(v);
	}
}

void solve()
{
	cin >> n;
	adj.assign(n, {});
	removed.assign(n, false);
	sz.assign(n, 0);
	res.assign(n, 0);
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	decompose(0);
	for (int i = 1; i < n; i++)
		cout << res[i] << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init_fft();
	solve();
}
