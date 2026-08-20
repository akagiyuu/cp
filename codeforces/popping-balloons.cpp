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

void solve()
{
	int n, m;
	cin >> n >> m;
	vector<int> a(n);
	vector<int> b(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	for (int i = 0; i < n; i++)
		cin >> b[i];

	SegmentTree seg(b);
	vector<int> prefix_b(n);
	prefix_b[0] = b[0];
	for (int i = 1; i < n; i++) {
		prefix_b[i] = prefix_b[i - 1] + b[i];
	}
	if (a[0] > m) {
		cout << -1 << "\n";
		return;
	}

	int sum = 0, max_time_b = 0, i = 0;
	while (i < n && sum <= m) {
		sum += a[i];
		i++;
	}
	if (i < n)
		sum -= a[i];
	i--;
	for (int x = 0; x <= i; x++)
		max_time_b += b[x];
	max_time_b--;
	int diff = m - max_time_b;
	if (diff <= 0) {
		cout << 0 << "\n";
		return;
	}

	i = 0;
	int cnt = 0;
	int l = 0;
	int time_b = m;
	int r = upper_bound(prefix_b.begin(), prefix_b.end(), time_b) - prefix_b.begin() - 1;
	if (r == -1) {
		cout << 0 << "\n";
		return;
	}
	vector<int> res;
	int additional_time = 0;
	auto orig_b = b;
	while (i < n && l <= r && m > 0) {
		int delta = min(m, min(a[i], b[l]));
		m -= delta;
		a[i] -= delta;
		if (a[i] == 0) {
			cnt++;
			i++;
		}

		r = upper_bound(prefix_b.begin(), prefix_b.end(), time_b) - prefix_b.begin() - 1;
		b[l] -= delta;
		if (b[l] == 0 && cnt > 0) {
			int mx = seg.get(l, r);
			if (mx == orig_b[l]) {
				time_b -= mx * cnt;
				diff -= mx * cnt;
				for (int x = 0; x < cnt; x++)
					res.push_back(prefix_b[l] + additional_time);
				additional_time += mx * cnt;
				cnt = 0;
			}
			b[l] += mx * cnt;
		}
		if (b[l] == 0) {
			l++;
		}
	}
	assert(cnt == 0);
	if (diff > 0) {
		cout << -1 << "\n";
		return;
	}
	cout << res.size() << "\n";
	for (auto x : res)
		cout << x << " ";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
