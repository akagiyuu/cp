#include <bits/stdc++.h>

using namespace std;

#define int long long
#define ii pair<int, int>
#define fi first
#define se second

const int MOD = 998244353;

struct mint {
	int n;
	mint(int _n)
	{
		n = _n % MOD;
	}
	mint()
	{
	}
};
mint operator+(mint x, mint y)
{
	x.n += y.n;
	if (x.n >= MOD)
		x.n -= MOD;
	return x;
}
mint operator-(mint x, mint y)
{
	x.n -= y.n;
	if (x.n < 0)
		x.n += MOD;
	return x;
}
mint operator*(mint x, mint y)
{
	return mint(x.n * y.n);
}
mint pow(mint x, int e)
{
	mint r = 1;
	while (e) {
		if (e & 1)
			r = r * x;
		x = x * x;
		e >>= 1;
	}
	return r;
}
mint operator/(mint x, mint y)
{
	return x * pow(y, MOD - 2);
}

int solve()
{
	int n, m;
	cin >> n >> m;
	vector<vector<int> > a(n, vector<int>(m));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> a[i][j];
	int r, c;
	cin >> r >> c;
	r--;
	c--;

	vector<ii> ids;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			ids.push_back({ i, j });
	sort(ids.begin(), ids.end(), [&](const ii &x, const ii &y) { return a[x.fi][x.se] < a[y.fi][y.se]; });

	vector<pair<mint, mint> > s(n * m), ss(n * m);
	s[0] = ids[0];
	ss[0] = { s[0].fi * s[0].fi, s[0].se * s[0].se };
	for (int k = 1; k < n * m; k++) {
		auto [_i, _j] = ids[k];
		mint i = _i;
		mint j = _j;
		s[k] = { s[k - 1].fi + i, s[k - 1].se + j };
		ss[k] = { ss[k - 1].fi + i * i, ss[k - 1].se + j * j };
	}

	vector<mint> f(n * m, 0);
	vector<mint> sf(n * m, 0);
	int l = -1;
	for (int k = 0; k < n * m; k++) {
		auto [_i, _j] = ids[k];
		mint i = _i;
		mint j = _j;
		while (a[ids[l + 1].fi][ids[l + 1].se] < a[_i][_j])
			l++;
		if (l == -1)
			continue;

		f[k] = f[k] + sf[l];
		f[k] = f[k] + ss[l].fi + ss[l].se;
		f[k] = f[k] - mint(2) * i * s[l].fi - mint(2) * j * s[l].se;
		f[k] = f[k] / mint(l + 1);
		f[k] = f[k] + i * i + j * j;
		if (_i == r && _j == c)
			return f[k].n;
		sf[k] = sf[k - 1] + f[k];
	}
	return 0;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cout << solve() << '\n';
}
