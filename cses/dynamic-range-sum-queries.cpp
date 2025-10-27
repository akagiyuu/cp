#include <bits/stdc++.h>

using namespace std;

#define int long long

struct SegmentTree {
	int n;
	vector<int> tree;

	SegmentTree(vector<int> &a)
	{
		n = a.size();
		tree.assign(4 * n, 0);
		build(1, 0, n - 1, a);
	}

	void build(int v, int tl, int tr, vector<int> &a)
	{
		if (tl == tr) {
			tree[v] = a[tl];
			return;
		}

		int tmid = (tl + tr) / 2;
		build(2 * v, tl, tmid, a);
		build(2 * v + 1, tmid + 1, tr, a);
		tree[v] = tree[2 * v] + tree[2 * v + 1];
	}

	int sum(int v, int tl, int tr, int l, int r)
	{
		if (l > r)
			return 0;

		if (tl == l && tr == r)
			return tree[v];

		int tmid = (tl + tr) / 2;

		return sum(2 * v, tl, tmid, l, min(tmid, r)) + sum(2 * v + 1, tmid + 1, tr, max(tmid + 1, l), r);
	}

	int sum(int l, int r)
	{
		return sum(1, 0, n - 1, l, r);
	}

	void update(int v, int tl, int tr, int i, int x)
	{
		if (tl == tr) {
			tree[v] = x;
			return;
		}
		int tmid = (tl + tr) / 2;
		if (i <= tmid)
			update(2 * v, tl, tmid, i, x);
		else
			update(2 * v + 1, tmid + 1, tr, i, x);
		tree[v] = tree[2 * v] + tree[2 * v + 1];
	}

	void update(int i, int x)
	{
		update(1, 0, n - 1, i, x);
	}
};

void solve()
{
	int n, q;
	cin >> n >> q;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	SegmentTree s(a);

	while (q--) {
		int type;
		cin >> type;
		if (type == 1) {
			int i, x;
			cin >> i >> x;
			i--;
			s.update(i, x);
		}
		if (type == 2) {
			int l, r;
			cin >> l >> r;
			l--;
			r--;
			cout << s.sum(l, r) << "\n";
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
