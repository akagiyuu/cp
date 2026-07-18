#include <bits/stdc++.h>

using namespace std;

#define int long long
#define pi pair<int, int>
#define fi first
#define se second

const int MOD = 1000000007;

struct SegmentTree {
	int n;
	vector<int> tree;

	SegmentTree(const vector<int> &a)
	{
		n = a.size();
		tree.assign(4 * n, LLONG_MAX);
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
		tree[v] = min(tree[2 * v], tree[2 * v + 1]);
	}

	int _calc(int v, int tl, int tr, int l, int r)
	{
		if (tl == l && tr == r) {
			return tree[v];
		}

		int tmid = (tl + tr) / 2;

		int a = _calc(2 * v, tl, tmid, l, min(r, tmid));
		int b = _calc(2 * v + 1, tmid + 1, tr, max(tmid + 1, l), r);
		return min(a, b);
	}

	int calc(int l, int r)
	{
		return _calc(1, 0, n - 1, l, r);
	}

	void _update(int v, int tl, int tr, int i, int value)
	{
		if (i < tl || i > tr)
			return;
		if (tl == tr) {
			tree[v] = value;
			return;
		}

		int tmid = (tl + tr) / 2;
		_update(2 * v, tl, tmid, i, value);
		_update(2 * v + 1, tmid + 1, tr, i, value);
		tree[v] = min(tree[2 * v], tree[2 * v + 1]);
	}

	void update(int i, int value)
	{
		_update(1, 0, n - 1, i, value);
	}
};

void solve()
{
	int n;
	cin >> n;
	vector<int> wall_ls(n), wall_rs(n);
	vector<vector<int> > doors;
	for (int i = 0; i < n; i++) {
		int k;
		cin >> k >> wall_ls[i] >> wall_rs[i];
		doors.push_back(vector<int>(k));
		for (int j = 0; j < k; j++)
			cin >> doors[i][j];
	}

	vector<pi> lefts;
	vector<int> sums(n), rights(n);
	for (int i = 0; i < n; i++) {
		int s = wall_ls[i];
		for (auto d : doors[i]) {
			lefts.push_back({ i, s });
			s += d;
		}
		lefts.push_back({ i, s });
		sums[i] = s - wall_ls[i];
		rights[i] = wall_rs[i] - sums[i];
		// cout << rights[i] << " ";
	}
	// cout << "\n";
	sort(lefts.begin(), lefts.end(), [](const pi &a, const pi &b) { return a.se < b.se; });
	// for (auto [i, l] : lefts) {
	// 	cout << "{ " << i << ", " << l << " }\n";
	// }

	SegmentTree rs(rights);

	vector<bool> contain(n, false);
	int missing = n;
	int k = 0;
	while (missing > 0) {
		auto [i, l] = lefts[k];
		rs.update(i, wall_rs[i] - sums[i] + l - wall_ls[i]);
		// cout << i << " " << l << rs.calc(0, n - 1) << "\n";

		if (!contain[i])
			missing--;
		contain[i] = true;
		k++;
	}

	int res = max(0ll, rs.calc(0, n - 1) - lefts[k - 1].se);
	int m = lefts.size();
	for (; k < m; k++) {
		auto [i, l] = lefts[k];
		// cout << i << " " << l << rs.calc(0, n - 1) << "\n";
		rs.update(i, wall_rs[i] - sums[i] + l - wall_ls[i]);
		res = max(res, rs.calc(0, n - 1) - l);
	}

	cout << res << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
