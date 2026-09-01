#include <bits/stdc++.h>

using namespace std;

#define int long long
#define pi pair<int, int>

struct Piece {
	int len;
	bool b0, b1;
};

struct State {
	int col;
	int run;
	vector<int> M;
};

bool Mgreater(const vector<int> &A, const vector<int> &B)
{
	int n = min(A.size(), B.size());
	for (int i = 0; i < n; i++) {
		if (A[i] != B[i])
			return A[i] > B[i];
	}
	return A.size() > B.size();
}

bool dominates(const State &A, const State &B)
{
	if (A.run < B.run)
		return false;
	int n = max(A.M.size(), B.M.size());
	for (int i = 0; i < n; i++) {
		int a = i < A.M.size() ? A.M[i] : 0;
		int b = i < B.M.size() ? B.M[i] : 0;
		if (a < b)
			return false;
	}
	return true;
}

vector<int> insert(const vector<int> &M, int v)
{
	vector<int> res = M;
	auto it = lower_bound(res.begin(), res.end(), v, greater<int>());
	res.insert(it, v);
	return res;
}

void solve()
{
	int n, m;
	cin >> n >> m;
	vector<pi> a(n), b(m);

	for (int i = 0; i < n; i++)
		cin >> a[i].first >> a[i].second;
	for (int i = 0; i < m; i++)
		cin >> b[i].first >> b[i].second;

	vector<tuple<int, int, int> > ev;
	for (auto p : a)
		ev.push_back({ p.first, p.second, 0 });
	for (auto p : b)
		ev.push_back({ p.first, p.second, 1 });
	sort(ev.begin(), ev.end());

	vector<int> res;

	int i = 0;
	int sz = ev.size();
	while (i < sz) {
		int curR = get<1>(ev[i]);
		vector<tuple<int, int, int> > comp;
		comp.push_back(ev[i]);
		int j = i + 1;
		while (j < sz && get<0>(ev[j]) <= curR) {
			curR = max(curR, get<1>(ev[j]));
			comp.push_back(ev[j]);
			j++;
		}
		i = j;

		vector<pi> c0, c1;
		for (auto [l, r, c] : comp) {
			if (c == 0)
				c0.push_back({ l, r });
			else
				c1.push_back({ l, r });
		}
		sort(c0.begin(), c0.end());
		sort(c1.begin(), c1.end());

		if (c1.empty()) {
			for (auto [l, r] : c0)
				res.push_back(r - l + 1);
			continue;
		}
		if (c0.empty()) {
			for (auto [l, r] : c1)
				res.push_back(r - l + 1);
			continue;
		}

		vector<int> pts;
		for (auto [l, r] : c0) {
			pts.push_back(l);
			pts.push_back(r);
		}
		for (auto [l, r] : c1) {
			pts.push_back(l);
			pts.push_back(r);
		}
		sort(pts.begin(), pts.end());
		pts.erase(unique(pts.begin(), pts.end()), pts.end());

		vector<int> bp;
		for (auto [l, r] : c0) {
			bp.push_back(l);
			bp.push_back(r + 1);
		}
		for (auto [l, r] : c1) {
			bp.push_back(l);
			bp.push_back(r + 1);
		}
		sort(bp.begin(), bp.end());
		bp.erase(unique(bp.begin(), bp.end()), bp.end());

		auto black_in = [](vector<pi> &v, int x, int y) {
			for (auto [l, r] : v)
				if (l <= x && y <= r)
					return true;
			return false;
		};

		vector<Piece> pcs;
		for (size_t k = 0; k + 1 < bp.size(); k++) {
			int x = bp[k], y = bp[k + 1] - 1;
			if (y < x)
				continue;
			bool h0 = black_in(c0, x, y);
			bool h1 = black_in(c1, x, y);
			if (!h0 && !h1)
				continue;
			pcs.push_back({ y - x + 1, h0, h1 });
		}

		vector<State> states;
		states.push_back({ -1, 0, {} });

		for (auto pc : pcs) {
			vector<State> raw;
			for (auto st : states) {
				for (int c = 0; c < 2; c++) {
					bool avail = (c == 0) ? pc.b0 : pc.b1;
					if (!avail)
						continue;
					if (st.col == c) {
						raw.push_back({ c, st.run + pc.len, st.M });
					} else {
						vector<int> nxM = st.M;
						if (st.run > 0)
							nxM = insert(st.M, st.run);
						raw.push_back({ c, pc.len, nxM });
					}
				}
			}
			vector<State> merged;
			for (auto cand : raw) {
				bool placed = false;
				for (auto &m : merged) {
					if (m.col == cand.col && m.run == cand.run) {
						if (Mgreater(cand.M, m.M))
							m.M = cand.M;
						placed = true;
						break;
					}
				}
				if (!placed)
					merged.push_back(cand);
			}
			vector<State> pruned;
			for (int x = 0; x < merged.size(); x++) {
				bool isDominated = false;
				for (int y = 0; y < merged.size(); y++) {
					if (x == y)
						continue;
					if (dominates(merged[y], merged[x]) &&
					    !(merged[x].run == merged[y].run && (merged[x].M == merged[y].M))) {
						isDominated = true;
						break;
					}
				}
				if (!isDominated)
					pruned.push_back(merged[x]);
			}
			states = pruned;
		}

		vector<int> best;
		bool first = true;
		for (auto st : states) {
			auto M = st.M;
			if (st.run > 0)
				M = insert(M, st.run);
			if (first || Mgreater(M, best)) {
				best = M;
				first = false;
			}
		}
		for (int x : best)
			res.push_back(x);
	}

	sort(res.rbegin(), res.rend());
	cout << res.size() << "\n";
	for (auto x : res)
		cout << x << " ";
	cout << "\n";
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
