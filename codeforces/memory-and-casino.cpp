#include <bits/stdc++.h>

using namespace std;

#define int long long
#define double long double

struct SegTree {
	int n;
	vector<double> p, f;
	SegTree(const vector<double> &a)
	{
		n = a.size();
		p.resize(4 * n);
		f.resize(4 * n);
		build(1, 0, n - 1, a);
	}
	void build(int id, int tl, int tr, const vector<double> &a)
	{
		if (tl == tr) {
			p[id] = (1 - a[tl]) / a[tl];
			f[id] = 1 + p[id];
			return;
		}
		int tmid = (tl + tr) / 2;
		build(2 * id, tl, tmid, a);
		build(2 * id + 1, tmid + 1, tr, a);
		p[id] = p[2 * id] * p[2 * id + 1];
		f[id] = f[2 * id] + p[2 * id] * (f[2 * id + 1] - 1);
	}
	pair<double, double> get(int id, int tl, int tr, int l, int r)
	{
		if (l > r)
			return { 1, 1 };
		if (tl == l && tr == r)
			return { p[id], f[id] };
		int tmid = (tl + tr) / 2;
		auto [pl, fl] = get(2 * id, tl, tmid, l, min(tmid, r));
		auto [pr, fr] = get(2 * id + 1, tmid + 1, tr, max(l, tmid + 1), r);
		return { pl * pr, fl + pl * (fr - 1) };
	}
	pair<double, double> get(int l, int r)
	{
		return get(1, 0, n - 1, l, r);
	}
	void update(int id, int tl, int tr, int i, double v)
	{
		if (tl == tr) {
			p[id] = (1 - v) / v;
			f[id] = 1 + p[id];
			return;
		}
		int tmid = (tl + tr) / 2;
		if (i <= tmid)
			update(2 * id, tl, tmid, i, v);
		else
			update(2 * id + 1, tmid + 1, tr, i, v);
		p[id] = p[2 * id] * p[2 * id + 1];
		f[id] = f[2 * id] + p[2 * id] * (f[2 * id + 1] - 1);
	}
	void update(int i, double v)
	{
		update(1, 0, n - 1, i, v);
	}
};

void solve()
{
	int n, q;
	cin >> n >> q;
	vector<double> p(n);
	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;
		p[i] = (double)a / b;
	}
	SegTree t(p);

	while (q--) {
		int type;
		cin >> type;
		if (type == 1) {
			int i, a, b;
			cin >> i >> a >> b;
			i--;
			p[i] = (double)a / b;
			t.update(i, p[i]);
		} else {
			int l, r;
			cin >> l >> r;
			l--;
			r--;

			// double res = 1;
			// for (int i = l; i <= r; i++) {
			// 	double cur = 1;
			// 	for (int j = l; j <= i; j++)
			// 		cur *= (1 - p[j]) / p[j];
			// 	res += cur;
			// }
			auto [_, res] = t.get(l, r);
			res = 1. / res;
			if (isnan(res))
				res = 0;

			cout << fixed << setprecision(10) << res << '\n';
		}
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
