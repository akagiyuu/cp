#include <bits/stdc++.h>

using namespace std;

#define int long long

struct SegmentTree {
	int n;
	vector<int> tree;

	SegmentTree(const vector<int> &a)
	{
		n = a.size();
		tree.assign(4 * n, 0);
		build(1, 0, n - 1, a);
	}

	void build(int v, int tl, int tr, const vector<int> &a)
	{
		if (tl == tr) {
			tree[v] = a[tl];
			return;
		}

		int tmid = (tl + tr) / 2;
		build(2 * v, tl, tmid, a);
		build(2 * v + 1, tmid + 1, tr, a);
		tree[v] = tree[2 * v] ^ tree[2 * v + 1];
	}

	int calc(int v, int tl, int tr, int l, int r)
	{
		if (l > r)
			return 0;
		if (l == tl && r == tr)
			return tree[v];

		int tmid = (tl + tr) / 2;
		return calc(2 * v, tl, tmid, l, min(r, tmid)) ^ calc(2 * v + 1, tmid + 1, tr, max(tmid + 1, l), r);
	}

	int calc(int l, int r)
	{
		return calc(1, 0, n - 1, l, r);
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

	int l, r;
	while (q--) {
		cin >> l >> r;
		l--;
		r--;
		cout << s.calc(l, r) << "\n";
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
