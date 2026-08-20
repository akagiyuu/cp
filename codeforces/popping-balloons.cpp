#include <bits/stdc++.h>
#include <cassert>

using namespace std;

#define int long long

const int MOD = 1000000007;

struct SegmentTree {
	int n;
	vector<int> t;

	SegmentTree(const vector<int> &a)
	{
		n = a.size();
		t.assign(4 * n, 0);
		_build(1, 0, n - 1, a);
	}

	void _build(int v, int tl, int tr, const vector<int> &a)
	{
		if (tl == tr) {
			t[v] = a[tl];
			return;
		}

		int tmid = (tl + tr) / 2;
		_build(2 * v, tl, tmid, a);
		_build(2 * v + 1, tmid + 1, tr, a);
		t[v] = max(t[2 * v], t[2 * v + 1]);
	}

	int _get(int v, int tl, int tr, int l, int r)
	{
		if (l > r)
			return 0;
		if (l == tl && r == tr)
			return t[v];

		int tmid = (tl + tr) / 2;

		int a = _get(2 * v, tl, tmid, l, min(r, tmid));
		int b = _get(2 * v + 1, tmid + 1, tr, max(tmid + 1, l), r);
		return max(a, b);
	}

	int get(int l, int r)
	{
		return _get(1, 0, n - 1, l, r);
	}
};

pair<bool, vector<int> > solve()
{
	int n, m;
	cin >> n >> m;
	vector<int> a(n);
	vector<int> b(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	for (int i = 0; i < n; i++)
		cin >> b[i];
	if (a[0] > m) {
		return { false, {} };
	}

	vector<int> prefix_a(n), prefix_b(n);
	prefix_a[0] = a[0];
	for (int i = 1; i < n; i++) {
		prefix_a[i] = prefix_a[i - 1] + a[i];
	}
	prefix_b[0] = b[0];
	for (int i = 1; i < n; i++) {
		prefix_b[i] = prefix_b[i - 1] + b[i];
	}

	int i = upper_bound(prefix_a.begin(), prefix_a.end(), m) - prefix_a.begin() - 1;

	SegmentTree seg(b);
	auto orig_b = b;
	int cur_t = 0, mx_t = m;
	int l = 0, r = upper_bound(prefix_b.begin(), prefix_b.end(), mx_t) - prefix_b.begin() - 1;
	int used = 0;
	vector<int> res;
	while (l <= r && cur_t < m) {
		int delta = min(m - cur_t, b[l]);
		cur_t += delta;
		b[l] -= delta;

		int cnt = upper_bound(prefix_a.begin(), prefix_a.end(), cur_t) - prefix_a.begin() - used;
		int mx = seg.get(l, min(r, i));
		if (cnt > 0 && mx == orig_b[l]) {
			b[l] += mx;
			mx_t -= mx;
			res.push_back(cur_t);
			used++;
			r = upper_bound(prefix_b.begin(), prefix_b.end(), mx_t) - prefix_b.begin() - 1;
		}
		if (b[l] == 0) {
			l++;
		}
	}
	if (i <= r)
		return { false, {} };
	return make_pair(true, res);
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	auto [ok, res] = solve();
	if (!ok)
		cout << -1 << "\n";
	else {
		cout << res.size() << "\n";
		for (auto x : res)
			cout << x << " ";
		cout << "\n";
	}
}
