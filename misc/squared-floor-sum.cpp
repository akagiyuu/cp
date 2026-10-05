// https://www.luogu.com.cn/problem/P5170

#include <bits/stdc++.h>
#include <cassert>

using namespace std;

#define int long long

const int MOD = 998244353;

struct mint {
	int n;
	mint(int _n)
	{
		n = _n % MOD;
	}
};

mint operator+(mint x, mint y)
{
	x.n += y.n;
	if (x.n >= MOD)
		x.n -= MOD;
	return x;
}
mint operator+(mint x, int y)
{
	return x + mint(y);
}
mint operator-(mint x, mint y)
{
	x.n -= y.n;
	if (x.n < 0)
		x.n += MOD;
	return x;
}
mint operator-(mint x, int y)
{
	return x - mint(y);
}
mint operator*(mint x, mint y)
{
	return mint(x.n * y.n);
}
mint operator*(int x, mint y)
{
	return mint(x * y.n);
}
mint pow(mint x, int e)
{
	mint r = mint{ 1 };
	while (e) {
		if (e & 1)
			r = r * x;
		x = x * x;
		e >>= 1;
	}
	return r;
}
mint operator/(mint x, int y)
{
	return x * pow(mint(y), MOD - 2);
}

vector<mint> squared_floor_sum(int a, int b, int c, int _n)
{
	if (_n < 0)
		return { mint{ 0 }, mint{ 0 }, mint{ 0 } };
	auto n = mint(_n);
	if (a == 0) {
		auto qb = mint(b / c);
		return { (n + 1) * qb, n * (n + 1) / 2 * qb, (n + 1) * qb * qb };
	}
	if (a >= c || b >= c) {
		auto qa = mint(a / c);
		auto qb = mint(b / c);
		auto prev = squared_floor_sum(a % c, b % c, c, _n);

		auto r0 = n * (n + 1) / 2 * qa;
		r0 = r0 + (n + 1) * qb;
		r0 = r0 + prev[0];

		auto r1 = n * (n + 1) * (2 * n + 1) / 6 * qa;
		r1 = r1 + n * (n + 1) / 2 * qb;
		r1 = r1 + prev[1];

		auto r2 = qa * qa * n * (n + 1) * (2 * n + 1) / 6;
		r2 = r2 + qb * qb * (n + 1);
		r2 = r2 + prev[2];
		r2 = r2 + 2 * qa * qb * n * (n + 1) / 2;
		r2 = r2 + 2 * qa * prev[1];
		r2 = r2 + 2 * qb * prev[0];

		return { r0, r1, r2 };
	}

	int _m = (a * _n + b) / c;
	mint m = mint(_m);
	auto prev = squared_floor_sum(c, c - b - 1, a, _m - 1);

	auto r0 = m * n - prev[0];

	auto r1 = m * n * (n + 1) / 2;
	r1 = r1 - (prev[2] + prev[0]) / 2;

	auto r2 = n * m * (m - 1);
	r2 = r2 - 2 * prev[1];
	r2 = r2 + r0;

	return { r0, r1, r2 };
}

void solve()
{
	int n, a, b, c;
	cin >> n >> a >> b >> c;
	auto res = squared_floor_sum(a, b, c, n);
	cout << res[0].n << ' ' << res[2].n << ' ' << res[1].n << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		solve();
}
