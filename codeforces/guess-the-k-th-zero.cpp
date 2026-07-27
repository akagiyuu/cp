#include <bits/stdc++.h>

using namespace std;

#define int long long
#define pi pair<int, int>
#define fi first
#define se second

struct SegmentTree {
	int n;
	vector<int> t;

	SegmentTree(int _n)
	{
		n = _n;
		t.assign(4 * n, 0);
	}

	int _sum(int v, int tl, int tr, int l, int r)
	{
		if (l > r)
			return 0;
		if (tl == l && tr == r)
			return t[v];

		int tmid = (tl + tr) / 2;

		int left = _sum(2 * v, tl, tmid, l, min(tmid, r));
		int right = _sum(2 * v + 1, tmid + 1, tr, max(tmid + 1, l), r);
		return left + right;
	}

	int sum(int l, int r)
	{
		return _sum(1, 1, n, l, r);
	}

	void _update(int v, int tl, int tr, int i, int value)
	{
		if (tl == tr) {
			t[v] = value;
			return;
		}

		int tmid = (tl + tr) / 2;
		if (i <= tmid)
			_update(2 * v, tl, tmid, i, value);
		else
			_update(2 * v + 1, tmid + 1, tr, i, value);
		t[v] = t[2 * v] + t[2 * v + 1];
	}

	void update(int i, int value)
	{
		_update(1, 1, n, i, value);
	}
};

int sum(int l, int r, map<pi, int> &cache, SegmentTree &additional)
{
	auto it = cache.find({ l, r });
	if (it != cache.end()) {
		return it->se + additional.sum(l, r);
	}
	cout << "? " << l << " " << r << endl;
	int s;
	cin >> s;
	cache[{ l, r }] = s;

	return s;
}

void solve()
{
	int n, t;
	cin >> n >> t;

	SegmentTree additional(n);
	map<pi, int> cache;

	while (t--) {
		int k;
		cin >> k;
		int cnt = n - sum(1, n, cache, additional);
		int l = 1, r = n;
		while (l < r) {
			int mid = (l + r) / 2;
			int cur = mid - l + 1 - sum(l, mid, cache, additional);
			if (k <= cur) {
				r = mid;
				cnt = cur;
			} else {
				k -= cur;
				l = mid + 1;
				cnt = cnt - cur;
			}
		}
		additional.update(l, 1);
		cout << "! " << l << endl;
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
