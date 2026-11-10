#include <bits/stdc++.h>

using namespace std;

#define int long long

const int P = 2e4;
const int SCALE = 1ll << 13;

void solve()
{
	int n, m;
	cin >> n >> m;
	vector<vector<pair<char, int> > > a(n, vector<pair<char, int> >(m));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> a[i][j].first;
			if (a[i][j].first == '-')
				continue;
			cin >> a[i][j].second;
		}
	}

	vector<int> p(n);
	vector<vector<vector<int> > > penalties(n, vector<vector<int> >(m + 1));
	for (int x = 0; x < n; x++) {
		int cnt = 0;
		for (int j = 0; j < m; j++)
			cnt += a[x][j].first == '?';
		p[x] = SCALE / (1ll << cnt);

		for (int mask = 0; mask < (1ll << m); mask++) {
			int pen = 0;
			bool ok = true;
			for (int j = 0; j < m; j++) {
				if ((mask >> j) & 1) {
					if (a[x][j].first == '-') {
						ok = false;
						break;
					}
					pen += a[x][j].second;
				} else {
					if (a[x][j].first == '+') {
						ok = false;
						break;
					}
				}
			}
			if (!ok)
				continue;
			int s = __builtin_popcount(mask);
			penalties[x][s].push_back(pen);
		}
		for (int s = 0; s <= m; s++)
			sort(penalties[x][s].begin(), penalties[x][s].end());
	}

	vector<vector<int> > f(n, vector<int>(m + 1, 0));
	for (int x = 0; x < n; x++) {
		for (int s = 0; s <= m; s++) {
			f[x][s] = penalties[x][s].size();
			if (s > 0)
				f[x][s] += f[x][s - 1];
		}
	}
	vector<int> g(m + 1, 0);
	for (int x = 0; x < n; x++) {
		for (int s = 0; s <= m; s++) {
			g[s] = g[s] + f[x][s] * p[x];
		}
	}

	vector<vector<int> > cnt_pens(m + 1, vector<int>(m * P + 1, 0));
	vector<vector<int> > suf_pens(m + 1, vector<int>(m * P + 1, 0));
	for (int x = 0; x < n; x++) {
		for (int s = 0; s <= m; s++) {
			for (auto pen : penalties[x][s])
				suf_pens[s][pen] += p[x];
		}
	}
	for (int s = 0; s <= m; s++)
		for (int pen = m * P - 1; pen >= 0; pen--)
			suf_pens[s][pen] += suf_pens[s][pen + 1];

	vector<int> prob(n);
	for (int x = n - 1; x >= 0; x--) {
		for (int sx = 1; sx <= m; sx++) {
			int cur = g[sx - 1] - f[x][sx - 1] * p[x];
			prob[x] += penalties[x][sx].size() * p[x] * cur;
		}

		int cur = 0;
		for (int s = 0; s <= m; s++) {
			int sz = penalties[x][s].size();
			int sum = 0;
			int sum2 = 0;
			int cnt = 1;
			for (int i = sz - 1; i >= 0; i--) {
				int pen = penalties[x][s][i];
				cur += cnt_pens[s][pen];

				if (i > 0 && pen == penalties[x][s][i - 1]) {
					cnt++;
					sum2 += p[x];
					continue;
				}

				if (pen + 1 <= m * P)
					cur += cnt * (suf_pens[s][pen + 1] - sum);
				sum += sum2;
				sum += p[x];
				sum2 = 0;
				cnt = 1;
			}
		}
		prob[x] += cur * p[x];

		for (int s = 0; s <= m; s++) {
			for (auto pen : penalties[x][s]) {
				cnt_pens[s][pen] += p[x];
			}
		}
	}

	for (int x = 0; x < n; x++) {
		auto num = prob[x];
		num = n * SCALE * SCALE - num;
		int denom = SCALE * SCALE;
		int g = __gcd(num, denom);
		cout << num / g << '/' << denom / g << '\n';
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
