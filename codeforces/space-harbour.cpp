#include <bits/stdc++.h>

using namespace std;

#define int long long

struct pt {
	int x, v;
};

bool operator<(const pt &a, const pt &b)
{
	return a.x < b.x;
}

void solve()
{
	int n, m, q;
	cin >> n >> m >> q;
	vector<pt> a(m);
	for (int i = 0; i < m; i++) {
		cin >> a[i].x;
		a[i].x--;
	}
	for (int i = 0; i < m; i++) {
		cin >> a[i].v;
	}
	set<pt> h(a.begin(), a.end());

	auto calc_cost = [&](const pt &prev, const pt &cur) {
		int res = 0;
		int cnt = cur.x - prev.x - 1;
		res = cnt * (cnt + 1) / 2 * prev.v;
		return res;
	};

	while (q--) {
		int t;
		cin >> t;
		if (t == 1) {
			pt cur;
			cin >> cur.x >> cur.v;
			cur.x--;
			h.insert(cur);
		} else {
			int l, r;
			cin >> l >> r;
			l--;
			r--;
			int res = 0;
			auto it = h.lower_bound(pt{ .x = l, .v = 0 });
			auto prev = *it;
			if (it != h.begin()) {
				it--;
				auto prev2 = *it;
				it++;

				int right = min(r, prev.x - 1);
				int cnt = right - l + 1;
				res += cnt * prev.x * prev2.v;
				int sum = right * (right + 1) / 2 - l * (l - 1) / 2;
				res -= sum * prev2.v;
			}
			if (prev.x > r) {
				cout << res << '\n';
				continue;
			}

			it++;
			while (it != h.end() && it->x <= r) {
				auto cur = *it;
				res += calc_cost(prev, cur);
				prev = cur;
				it++;
			}
			if (it != h.end()) {
				auto cur = *it;
				int left = cur.x - r;
				int right = cur.x - prev.x - 1;
				int sum = right * (right + 1) / 2 - left * (left - 1) / 2;
				res += sum * prev.v;
			}
			cout << res << "\n";
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
