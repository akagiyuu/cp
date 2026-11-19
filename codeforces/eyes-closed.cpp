#include <bits/stdc++.h>

using namespace std;

#define int long long

struct SegTree {
	int n;
	vector<double> tree, lazy_mul, lazy_add;

	SegTree(const vector<double> &a)
	{
		n = a.size();
		tree.assign(4 * n, 0);
		lazy_mul.assign(4 * n, 1);
		lazy_add.assign(4 * n, 0);
		build(1, 0, n - 1, a);
	}

	void build(int id, int tl, int tr, const vector<double> &a)
	{
		if (tl == tr) {
			tree[id] = a[tl];
			return;
		}
		int tmid = (tl + tr) / 2;
		build(2 * id, tl, tmid, a);
		build(2 * id + 1, tmid + 1, tr, a);
		tree[id] = tree[2 * id] + tree[2 * id + 1];
	}

	void apply(int id, int tl, int tr, double a, double b)
	{
		tree[id] = a * tree[id] + b * (tr - tl + 1);
		lazy_mul[id] = a * lazy_mul[id];
		lazy_add[id] = a * lazy_add[id] + b;
	}

	void push(int id, int tl, int tr)
	{
		if (tl == tr)
			return;

		int tmid = (tl + tr) / 2;
		apply(2 * id, tl, tmid, lazy_mul[id], lazy_add[id]);
		apply(2 * id + 1, tmid + 1, tr, lazy_mul[id], lazy_add[id]);

		lazy_mul[id] = 1;
		lazy_add[id] = 0;
	}

	double get(int id, int tl, int tr, int l, int r)
	{
		if (l > r)
			return 0;
		if (tl == l && tr == r)
			return tree[id];

		push(id, tl, tr);

		int tmid = (tl + tr) / 2;
		double x = get(2 * id, tl, tmid, l, min(r, tmid));
		double y = get(2 * id + 1, tmid + 1, tr, max(l, tmid + 1), r);
		return x + y;
	}

	double get(int l, int r)
	{
		return get(1, 0, n - 1, l, r);
	}

	void update(int id, int tl, int tr, int l, int r, double a, double b)
	{
		if (l > r)
			return;
		if (tl == l && tr == r) {
			apply(id, tl, tr, a, b);
			return;
		}

		push(id, tl, tr);

		int tmid = (tl + tr) / 2;
		update(2 * id, tl, tmid, l, min(r, tmid), a, b);
		update(2 * id + 1, tmid + 1, tr, max(l, tmid + 1), r, a, b);

		tree[id] = tree[2 * id] + tree[2 * id + 1];
	}

	void update(int l, int r, double a, double b)
	{
		update(1, 0, n - 1, l, r, a, b);
	}
};

void solve()
{
	int n, q;
	cin >> n >> q;
	vector<double> a(n);
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		a[i] = x;
	}
	SegTree t(a);
	while (q--) {
		int type;
		cin >> type;
		if (type == 1) {
			int l1, r1, l2, r2;
			cin >> l1 >> r1 >> l2 >> r2;
			l1--;
			r1--;
			l2--;
			r2--;

			double s1 = r1 - l1 + 1;
			double s2 = r2 - l2 + 1;
			double m1 = t.get(l1, r1) / s1;
			double m2 = t.get(l2, r2) / s2;

			t.update(l1, r1, 1 - 1. / s1, m2 / s1);
			t.update(l2, r2, 1 - 1. / s2, m1 / s2);
		} else {
			int l, r;
			cin >> l >> r;
			l--;
			r--;
			double res = t.get(l, r);
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
