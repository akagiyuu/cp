#include <bits/stdc++.h>

using namespace std;

#define int long long

struct Data {
	int cnt, cnt_l, cnt_r;
};
Data merge(const Data &a, const Data &b)
{
	int x = min(a.cnt_l, b.cnt_r);
	return Data{
		a.cnt + b.cnt + x,
		a.cnt_l + b.cnt_l - x,
		a.cnt_r + b.cnt_r - x,
	};
}

struct SegmentTree {
	int n;
	vector<Data> t;

	SegmentTree(const vector<Data> &a)
	{
		n = a.size();
		t.assign(4 * n, Data{ 0, 0, 0 });
		build(1, 0, n - 1, a);
	}
	void build(int v, int tl, int tr, const vector<Data> &a)
	{
		if (tl == tr) {
			t[v] = a[tl];
			return;
		}

		int tmid = (tl + tr) / 2;
		build(2 * v, tl, tmid, a);
		build(2 * v + 1, tmid + 1, tr, a);
		t[v] = merge(t[2 * v], t[2 * v + 1]);
	}
	Data _calc(int v, int tl, int tr, int l, int r)
	{
		if (l > r)
			return Data{ 0, 0, 0 };
		if (tl == l && tr == r)
			return t[v];

		int tmid = (tl + tr) / 2;
		return merge(_calc(2 * v, tl, tmid, l, min(tmid, r)),
			     _calc(2 * v + 1, tmid + 1, tr, max(l, tmid + 1), r));
	}
	Data calc(int l, int r)
	{
		return _calc(1, 0, n - 1, l, r);
	}
};

void solve()
{
	string s;
	cin >> s;
	int n = s.size();
	vector<Data> a(n);
	for (int i = 0; i < n; i++) {
		a[i] = (s[i] == '(') ? Data{ 0, 1, 0 } : Data{ 0, 0, 1 };
	}
	SegmentTree seg(a);

	int q;
	cin >> q;
	while (q--) {
		int l, r;
		cin >> l >> r;
		l--;
		r--;
		auto x = seg.calc(l, r);
		// cout << x.cnt << ' ' << x.cnt_l << ' ' << x.cnt_r << '\n';
		cout << 2 * x.cnt << '\n';
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
