#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

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
		tree[v] = std::gcd(tree[2 * v], tree[2 * v + 1]);
	}

	int calc(int v, int tl, int tr, int l, int r)
	{
		if (l > r)
			return 0;
		if (tl == l && tr == r)
			return tree[v];

		int tmid = (tl + tr) / 2;
		return std::gcd(calc(2 * v, tl, tmid, l, min(tmid, r)),
				calc(2 * v + 1, tmid + 1, tr, max(tmid + 1, l), r));
	}

	int gcd(int l, int r)
	{
		return calc(1, 0, n - 1, l, r);
	}
};

void solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	for (int i = 0; i < n - 1; i++) {
		a[i] = abs(a[i + 1] - a[i]);
	}
	a.pop_back();
	n--;
	if (a.empty()) {
		cout << 1 << "\n";
		return;
	}

	SegmentTree s(a);

	int res = 1;
	int l = 0;
	for (int r = 0; r < n; r++) {
		while (l <= r && s.gcd(l, r) == 1)
			l++;
		res = max(res, r - l + 2);
	}
	cout << res << "\n";
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
