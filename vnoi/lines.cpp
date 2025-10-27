#include <bits/stdc++.h>
#include <cassert>
#include <cmath>

#define endl '\n'
#define int long long
#define double long double
const double PI = acos(-1);
const double THREDHOLD = 0.2;
const int N = 16;

using namespace std;

void solve()
{
	int n, q, tmp;
	cin >> n >> q;
	vector<pair<double, double> > b(n);
	cin >> b[0].first;
	b[0].second = 1;

	for (int i = 1; i < n; i++) {
		cin >> b[i].second >> b[i].first;
	}
	cin >> tmp;
	for (int i = n - 1; i >= 1; i--) {
		b[i].first -= b[i - 1].first;
	}
	map<double, double> raw;
	for (int i = 1; i < n; i++) {
		raw[b[i].second] += b[i].first;
	}
	vector<pair<double, double> > cnt(raw.begin(), raw.end());
	array<double, N> raw_coef;
	for (int i = 0; i < N; i++) {
		if (i == 0)
			raw_coef[i] = 1.0;
		else
			raw_coef[i] = raw_coef[i - 1] * (2.0L * i - 1.0L) / (2.0L * i);
	}

	vector<array<double, N> > coef(cnt.size());
	for (int j = 0; j < (int)cnt.size(); j++) {
		for (int i = 0; i < N; i++) {
			coef[j][i] = 0;
		}
	}

	for (int j = 0; j < (int)cnt.size(); j++) {
		auto [nj, dx] = cnt[j];
		double inv = 1.0 / powl(nj, 2);
		double cur = dx;

		for (int i = 0; i < N; i++) {
			coef[j][i] += cur;
			// coef[j][i] *= raw_coef[i];
			cur *= inv;
		}
	}
	for (int j = (int)cnt.size() - 2; j >= 0; j--) {
		for (int i = 0; i < N; i++) {
			coef[j][i] += coef[j + 1][i];
		}
	}

	while (q--) {
		double x1, x2, y1, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		double dx = x2 - x1;
		double dy = y2 - y1;
		double h = hypot(dx, dy);
		auto s = dy / h;
		s = fabsl(s);
		auto s_sq = s * s;

		double min_ni = s / THREDHOLD;
		int start = upper_bound(cnt.begin(), cnt.end(), make_pair(min_ni, 0),
					[](const pair<double, double> &a, const pair<double, double> &b) {
						return a.first < b.first;
					}) -
			    cnt.begin();

		double res = (b[0].first - x1) / sqrtl(1 - s_sq);
		auto cur = 1.0;
		if (start < (int)cnt.size()) {
			for (int i = 0; i < N; i++) {
				res += cur * coef[start][i] * raw_coef[i];
				cur *= s_sq;
			}
		}

		for (int i = 0; i < start; i++) {
			auto [ni, dx] = cnt[i];
			double tmp = ni * ni - s_sq;
			assert(tmp > 0);

			res += dx * (ni / sqrtl(tmp));
		}
		cout << setprecision(10) << res << "\n";
	}
}

#define TASK "test"

signed main()
{
	ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	if (fopen("input.txt", "r")) {
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	}
	solve();
	return 0;
}
