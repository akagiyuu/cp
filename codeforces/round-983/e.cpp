#include <bits/stdc++.h>
#include <cpp-dump.hpp>

typedef long long ll;

const ll MOD = 1000000007;

using namespace std;

const double EPS = 1e-9;
const int INF = 2; // it doesn't actually have to be infinity or a big number

int gauss(vector<vector<double> > a, vector<double> &ans)
{
	int n = (int)a.size();
	int m = (int)a[0].size() - 1;

	vector<int> where(m, -1);
	for (int col = 0, row = 0; col < m && row < n; ++col) {
		int sel = row;
		for (int i = row; i < n; ++i)
			if (abs(a[i][col]) > abs(a[sel][col]))
				sel = i;
		if (abs(a[sel][col]) < EPS)
			continue;
		for (int i = col; i <= m; ++i)
			swap(a[sel][i], a[row][i]);
		where[col] = row;

		for (int i = 0; i < n; ++i)
			if (i != row) {
				double c = a[i][col] / a[row][col];
				for (int j = col; j <= m; ++j)
					a[i][j] -= a[row][j] * c;
			}
		++row;
	}

	ans.assign(m, 0);
	for (int i = 0; i < m; ++i)
		if (where[i] != -1)
			ans[i] = a[where[i]][m] / a[where[i]][i];
	for (int i = 0; i < n; ++i) {
		double sum = 0;
		for (int j = 0; j < m; ++j)
			sum += ans[j] * a[i][j];
		if (abs(sum - a[i][m]) > EPS)
			return 0;
	}

	for (int i = 0; i < m; ++i)
		if (where[i] == -1)
			return INF;
	return 1;
}

void solve()
{
	int n;
	cin >> n;
	vector<double> vs(n);
	for (int i = 0; i < n; i++) {
		cin >> vs[i];
	}
	vector<vector<double> > a(n, vector<double>(n + 1, 0));
	for (int i = 0; i < n; i++) {
		a[i][(i + 1) % n] = -1;
		a[i][(i + 2) % n] = -1;
		a[i][i] = 1;
		a[i][(i + n - 1) % n] = 1;
		a[i][n] = vs[(i + 1) % n] - vs[i];
	}
    cpp_dump(a);
    vector<double> res;
    gauss(a, res);
    cpp_dump(res);
}

int main()
{
	CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		solve();
}
