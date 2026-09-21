#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define int long long

template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct SegmentTree {
	int n;
	vector<int> t;
	
	SegmentTree(int _n) {
		n = _n;
		t.assign(4 * n, 0);
	}

	int _calc(int v, int tl, int tr, int l, int r) {
		if(l > r) return 0;
		if(tl == l && tr == r) return t[v];
		int tmid = (tl + tr) / 2;
		int x = _calc(2 * v, tl, tmid, l, min(tmid, r));
		int y = _calc(2 * v + 1, tmid + 1, tr, max(l, tmid + 1), r);
		return x + y;
	}
	int calc(int l, int r) {
		return _calc(1, 0, n - 1, l, r);
	}

	void _update(int v, int tl, int tr, int i, int x) {
		if(tl == tr && tl == i) {
			t[v] += x;
			return;
		}
		int tmid = (tl + tr) / 2;
		if(i <= tmid) _update(2 * v, tl, tmid, i, x);
		else _update(2 * v + 1, tmid + 1, tr, i, x);
		t[v] = t[2 * v] + t[2 * v + 1];
	}
	void update(int i, int x) {
		return _update(1, 0, n - 1, i, x);
	}
};

void solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	for(int i = 0; i < n; i++) cin >> a[i];
	ordered_set<int> s;
	for(int i = 0; i < n; i++) {
		s.insert(a[i]);
	}
	for(int i = 0; i < n; i++) {
		a[i] = s.order_of_key(a[i]);
	}

	SegmentTree st1(s.size()), st2(s.size());
	int cnt = 0;
	for(int i = n - 1; i >= 0; i--) {
		cnt += st2.calc(0, a[i] - 1);
		st2.update(a[i], st1.calc(0, a[i] - 1));
		st1.update(a[i], 1);
	}
	cout << cnt << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
