#include <bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 1e7;

void solve()
{
	int n, m, q;
	cin >> n >> m >> q;
	vector<string> grid(n);
	for (int i = 0; i < n; i++) {
		cin >> grid[i];
	}
	vector<int> cnt(MAX + 1, 0);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (isdigit(grid[i][j])) {
				cnt[grid[i][j] - '0']++;
			}
		}
	}

	auto next = [&](int i, int j, int di, int dj) { return make_pair(i + di, j + dj); };
	auto prev_idx = [&](int i, int j, int di, int dj) { return make_pair(i - di, j - dj); };
	auto is_valid = [&](int i, int j) { return 0 <= i && i < n && 0 <= j && j < m; };

	for (int di = -1; di <= 1; di++) {
		for (int dj = -1; dj <= 1; dj++) {
			if (di == 0 && dj == 0)
				continue;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					if (!isdigit(grid[i][j]))
						continue;
					int cur = grid[i][j] - '0';
					auto [k, l] = next(i, j, di, dj);
					while (is_valid(k, l) && isdigit(grid[k][l])) {
						cur = 10 * cur + grid[k][l] - '0';
						if (cur > MAX)
							break;
						cnt[cur]++;
						tie(k, l) = next(k, l, di, dj);
					}
					if (cur > MAX)
						continue;
					if (!is_valid(k, l))
						continue;
					int prev = cur;
					char ops = grid[k][l];
					cur = 0;
					int eval = 0;
					tie(k, l) = next(k, l, di, dj);
					for (; is_valid(k, l); tie(k, l) = next(k, l, di, dj)) {
						char c = grid[k][l];
						if (isdigit(grid[k][l])) {
							cur = 10 * cur + c - '0';
							int cur_eval;
							if (ops == '+') {
								cur_eval = eval + prev + cur;
							}
							if (ops == '*') {
								cur_eval = eval + prev * cur;
							}
							if (cur_eval > MAX)
								break;
							cnt[cur_eval]++;
							continue;
						}
						auto [kprev, lprev] = prev_idx(k, l, di, dj);
						if (grid[kprev][lprev] == '+' || grid[kprev][lprev] == '*') {
							break;
						}
						if (ops == '+') {
							eval += prev;
							prev = cur;
						}
						if (ops == '*') {
							prev *= cur;
						}

						ops = c;
						cur = 0;
					}
				}
			}
		}
	}

	while (q--) {
		int x;
		cin >> x;
		cout << cnt[x] << "\n";
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
