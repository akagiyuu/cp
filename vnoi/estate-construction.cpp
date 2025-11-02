#include <bits/stdc++.h>
#include <cassert>
#include <numeric>
// #include <cpp-dump.hpp>

using namespace std;

#define int long long
const int MOD = 1000000007;
const int N = 1e7;

int binpow(int a, int b)
{
	int res = 1;
	while (b) {
		if (b & 1)
			res = (res * a) % MOD;
		a = (a * a) % MOD;
		b >>= 1;
	}
	return res;
}

int sum[N];

void build(int k)
{
	sum[0] = 0;
	for (int i = 1; i < N; i++) {
		sum[i] = sum[i - 1] + binpow(i, k);
		sum[i] %= MOD;
	}
}

int sum_range(int l, int r)
{
	if (l == 0)
		return sum[r];
	else
		return (sum[r] - sum[l - 1] + MOD) % MOD;
}

struct Event {
	int i;
	int type;
	int j1, j2;

	bool operator<(Event const &o) const
	{
		if (i != o.i)
			return i < o.i;
		if (type != o.type)
			return type < o.type;
		if (j1 != o.j1)
			return j1 < o.j1;
		return j2 < o.j2;
	}
};

struct SegmentTree {
	int n, k;
	vector<int> tree;
	vector<int> y;

	SegmentTree(const vector<int> y, int k)
	{
		this->k = k;
		this->y = y;
		n = y.size() - 1;
		tree.assign(4 * n, 0);
		build(1, 0, n - 1);
	}

	void build(int v, int tl, int tr)
	{
		if (tl == tr) {
			int sum = 0;
			for (int i = y[tl]; i <= y[tl + 1]; i++) {
				sum += binpow(i, k);
				sum %= MOD;
			}
			tree[v] = sum;
			return;
		}

		int tmid = (tl + tr) / 2;
		build(2 * v, tl, tmid);
		build(2 * v + 1, tmid + 1, tr);
        tree[v] = tree[2 * v]
	}
};

int calc_segments(const multiset<pair<int, int> > &segments)
{
	int res = 0;
	auto cur = *segments.begin();
	for (auto s : segments) {
		if (s.first <= cur.second) {
			cur.second = max(cur.second, s.second);
		} else {
			res += sum_range(cur.first, cur.second);
			res %= MOD;
			cur = s;
		}
	}
	res += sum_range(cur.first, cur.second);
	res %= MOD;
	return res;
}

void solve()
{
	int n, k, i1, j1, i2, j2;
	cin >> n >> k;
	build(k);

	vector<Event> e;
	for (int i = 0; i < n; i++) {
		cin >> i1 >> j1 >> i2 >> j2;
		e.push_back(Event{
			.i = i1,
			.type = 1,
			.j1 = j1,
			.j2 = j2,
		});
		e.push_back(Event{
			.i = i2 + 1,
			.type = -1,
			.j1 = j1,
			.j2 = j2,
		});
	}
	sort(e.begin(), e.end());

	int ie = 0;
	int m = e.size();
	int res = 0;
	multiset<pair<int, int> > segments;
	while (ie < m) {
		int cur_i = e[ie].i;
		while (ie < m && e[ie].i == cur_i) {
			if (e[ie].type == 1) {
				segments.insert({ e[ie].j1, e[ie].j2 });
			} else {
				segments.erase({ e[ie].j1, e[ie].j2 });
			}
			ie++;
		}
		if (ie == m)
			break;
		if (segments.empty())
			continue;
		int next_i = e[ie].i;
		int sr = sum_range(cur_i, next_i - 1);
		int sc = calc_segments(segments);
		// cpp_dump(cur_i, next_i, segments);
		// cpp_dump(sr, sc);
		res += sr * sc % MOD;
		res %= MOD;
	}
	cout << res << "\n";
}

signed main()
{
	// CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
