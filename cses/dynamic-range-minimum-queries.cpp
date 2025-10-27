#include <bits/stdc++.h>

using namespace std;

#define int long long

struct SegmentTree {
	int n;
	vector<int> tree;

	SegmentTree(const vector<int> &a)
	{
		n = a.size();
		tree.assign(4 * n, LONG_LONG_MAX);
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
		tree[v] = std::min(tree[2 * v], tree[2 * v + 1]);
	}

	int min(int v, int tl, int tr, int l, int r)
	{
		if (l > r)
			return LONG_LONG_MAX;
		if (l == tl && r == tr) {
			return tree[v];
		}

		int tmid = (tl + tr) / 2;
		auto left = min(2 * v, tl, tmid, l, std::min(tmid, r));
		auto right = min(2 * v + 1, tmid + 1, tr, max(tmid + 1, l), r);

		return std::min(left, right);
	}

	int min(int l, int r)
	{
		return min(1, 0, n - 1, l, r);
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

		tree[v] = std::min(tree[2 * v], tree[2 * v + 1]);
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
	int type;
	while (q--) {
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
			cout << s.min(l, r) << "\n";
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
