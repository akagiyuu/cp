#include <bits/stdc++.h>
#include <cassert>

using namespace std;

#define int long long

const int MOD = 998244353;

int add(int x, int y)
{
	x += y;
	if (x >= MOD)
		x -= MOD;
	return x;
}
int sub(int x, int y)
{
	x -= y;
	if (x < 0)
		x += MOD;
	return x;
}
int powmod(int x, int e)
{
	if (x == 1)
		return 1;
	int r = 1;
	while (e) {
		if (e & 1)
			r = r * x % MOD;
		x = x * x % MOD;
		e >>= 1;
	}
	return r;
}
int inverse(int x)
{
	return powmod(x, MOD - 2);
}

void solve()
{
	int d, n, m;
	cin >> d >> n >> m;
	vector<int> l(n), p(m);
	for (int i = 0; i < n; i++)
		cin >> l[i];
	for (int i = 0; i < m; i++)
		cin >> p[i];
	sort(p.begin(), p.end());
	vector<int> cnt(d);
	for (auto L : l)
		cnt[L]++;

	auto f = [&](int L, int mask) {
		int res = LLONG_MAX;
		for (int j = 0; j < m; j++) {
			if ((mask >> j) & 1) {
				res = min(res, abs(L - p[j]));
			}
		}
		return res;
	};

	vector<vector<int> > pref(m, vector<int>(d, 1));
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < d; j++) {
			pref[i][j] = powmod(abs(j - p[i]), cnt[j]);
			if (j > 0)
				pref[i][j] = pref[i][j] * pref[i][j - 1] % MOD;
		}
	}

	vector<int> g(1ll << m, 1);
	for (int mask = 1; mask < (1ll << m); mask++) {
		vector<int> sub;
		for (int i = 0; i < m; i++)
			if ((mask >> i) & 1)
				sub.push_back(i);
		int sz = sub.size();
		for (int i = 0; i < sz; i++) {
			int l = 0, r = d - 1;
			if (i + 1 < sz)
				r = (p[sub[i]] + p[sub[i + 1]]) / 2;
			if (i > 0)
				l = (p[sub[i]] + p[sub[i - 1]]) / 2 + 1;

			g[mask] = g[mask] * pref[sub[i]][r] % MOD;
			if (l > 0)
				g[mask] = g[mask] * inverse(pref[sub[i]][l - 1]) % MOD;
		}
	}

	set<int> tmp;
	tmp.insert(0);
	for (int i = 0; i < m; i++) {
		tmp.insert(p[i]);
		for (int j = i + 1; j < m; j++) {
			tmp.insert((p[i] + p[j]) / 2);
			tmp.insert((p[i] + p[j]) / 2 + 1);
		}
	}
	vector<int> mid(tmp.begin(), tmp.end());
	int sz = mid.size();
	vector<int> val(sz);
	vector<int> scale(sz);
	for (int i = 0; i < sz; i++) {
		int L = mid[i];

		for (int mask = 1; mask < (1ll << m); mask++) {
			int cur = f(L, mask) * g[mask] % MOD;

			if (__builtin_popcount(mask) % 2 == 1)
				val[i] = sub(val[i], cur);
			else
				val[i] = add(val[i], cur);
		}

		for (int mask = 1; mask < (1ll << m); mask++) {
			int cur = f(L + 1, mask) * g[mask] % MOD;

			if (__builtin_popcount(mask) % 2 == 1)
				scale[i] = sub(scale[i], cur);
			else
				scale[i] = add(scale[i], cur);
		}
		scale[i] = sub(scale[i], val[i]);
	}

	int q;
	cin >> q;
	while (q--) {
		int L;
		cin >> L;
		int res = powmod(d + 1, n + 1);
		for (int i = 0; i < sz; i++) {
			if (i == sz - 1 || (mid[i] <= L && L < mid[i + 1])) {
				res = add(res, val[i]);
				res = add(res, scale[i] * (L - mid[i]) % MOD);
				break;
			}
		}
		cout << res << '\n';
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
