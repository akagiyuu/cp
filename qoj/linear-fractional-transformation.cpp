#include <bits/stdc++.h>
#include <cassert>

using namespace std;

#define int long long
#define double long double
#define cd complex<double>

const int N = 3;
const double EPS = 1e-8;

vector<cd> find(vector<vector<cd> > &A)
{
	int n = A.size();
	int m = A[0].size() - 1;

	vector<int> where(m, -1);
	for (int col = 0, row = 0; col < m && row < n; col++) {
		int sel = row;
		for (int i = row; i < n; i++)
			if (abs(A[i][col]) > abs(A[sel][col]))
				sel = i;

		if (abs(A[sel][col]) < EPS)
			continue;
		for (int i = col; i <= m; i++)
			swap(A[sel][i], A[row][i]);

		where[col] = row;
		for (int i = 0; i < n; i++) {
			if (i == row)
				continue;

			auto c = A[i][col] / A[row][col];
			for (int j = col; j <= m; j++)
				A[i][j] -= A[row][j] * c;
		}
		row++;
	}

	bool ok = true;
	vector<cd> coef(m, 0);
	for (int i = 0; i < m; i++)
		if (where[i] != -1)
			coef[i] = A[where[i]][m] / A[where[i]][i];
	for (int i = 0; i < n; i++) {
		cd sum = 0;
		for (int j = 0; j < m; j++)
			sum += coef[j] * A[i][j];
		if (abs(sum - A[i][m]) > EPS) {
			ok = false;
			break;
		}
	}
	if (ok)
		return coef;

	return {};
}

cd solve()
{
	vector<cd> x(N), y(N);
	for (int i = 0; i < N; i++) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		x[i] = cd(a, b);
		y[i] = cd(c, d);
	}
	int x0, y0;
	cin >> x0 >> y0;
	cd z0(x0, y0);

	vector<vector<cd> > A;
	for (int i = 0; i < N; i++)
		A.push_back({ x[i], 1, -y[i], x[i] * y[i] });
	auto coef = find(A);
	if (!coef.empty()) {
		cd a = coef[0], b = coef[1], c = coef[2];

		return (a * z0 + b) / (z0 + c);
	}

	A.clear();
	for (int i = 0; i < N - 1; i++)
		A.push_back({ x[i], 1, y[i] });
	coef = find(A);
	assert(!coef.empty());
	cd a = coef[0], b = coef[1];

	return a * z0 + b;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--) {
		auto res = solve();
		cout << fixed << setprecision(10) << res.real() << ' ' << res.imag() << '\n';
	}
}
