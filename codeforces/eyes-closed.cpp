#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 1e5 + 7;

struct SegTree {
	int n;
	double a[N], sum[4 * N], lzM[4 * N], lzA[4 * N];

	void apply(int k, int len, double m, double b)
	{
		sum[k] = sum[k] * m + b * len;
		lzM[k] = lzM[k] * m;
		lzA[k] = lzA[k] * m + b;
	}

	void push(int k, int l, int r)
	{
		int mid = (l + r) / 2;
		apply(2 * k, mid - l + 1, lzM[k], lzA[k]);
		apply(2 * k + 1, r - mid, lzM[k], lzA[k]);
		lzM[k] = 1;
		lzA[k] = 0;
	}

	void build(int k, int l, int r)
	{
		lzM[k] = 1;
		lzA[k] = 0;
		if (l == r) {
			sum[k] = a[l];
			return;
		}
		int mid = (l + r) / 2;
		build(2 * k, l, mid);
		build(2 * k + 1, mid + 1, r);
		sum[k] = sum[2 * k] + sum[2 * k + 1];
	}

	void update(int k, int l, int r, int ql, int qr, double m, double b)
	{
		if (ql <= l && r <= qr) {
			apply(k, r - l + 1, m, b);
			return;
		}
		push(k, l, r);
		int mid = (l + r) / 2;
		if (ql <= mid)
			update(2 * k, l, mid, ql, qr, m, b);
		if (qr > mid)
			update(2 * k + 1, mid + 1, r, ql, qr, m, b);
		sum[k] = sum[2 * k] + sum[2 * k + 1];
	}

	double query(int k, int l, int r, int ql, int qr)
	{
		if (ql <= l && r <= qr)
			return sum[k];
		push(k, l, r);
		int mid = (l + r) / 2;
		double res = 0;
		if (ql <= mid)
			res += query(2 * k, l, mid, ql, qr);
		if (qr > mid)
			res += query(2 * k + 1, mid + 1, r, ql, qr);
		return res;
	}

	void init(int n_, const vector<double> &v)
	{
		n = n_;
		for (int i = 1; i <= n; i++)
			a[i] = v[i];
		build(1, 1, n);
	}

	void update(int l, int r, double A, double B)
	{
		update(1, 1, n, l, r, A, B);
	}

	double query(int l, int r)
	{
		return query(1, 1, n, l, r);
	}
};

SegTree t;
void solve()
{
	int n, q;
	cin >> n >> q;
	vector<double> a(n + 1);
	for (int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		a[i] = x;
	}
	t.init(n, a);
	while (q--) {
		int type;
		cin >> type;
		if (type == 1) {
			int l1, r1, l2, r2;
			cin >> l1 >> r1 >> l2 >> r2;

			double s1 = r1 - l1 + 1;
			double s2 = r2 - l2 + 1;
			double m1 = t.query(l1, r1) / s1;
			double m2 = t.query(l2, r2) / s2;

			t.update(l1, r1, (1 - 1. / s1), m2 / s1);
			t.update(l2, r2, (1 - 1. / s2), m1 / s2);
		} else {
			int l, r;
			cin >> l >> r;
			double res = t.query(l, r);
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
