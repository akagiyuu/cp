#include <bits/stdc++.h>
#include <cmath>

#define int long long
#define double long double
#define fi first
#define se second

using namespace std;

const double EPS = 1e-8;

// pair<double, double> find_root(double a, double b, double c)
// {
// 	double delta = b * b - 4 * a * c;
// 	double rt_delta = sqrtl(delta);
// 	return {
// 		(-b - rt_delta) / (2.L * a),
// 		(-b + rt_delta) / (2.L * a),
// 	};
// }
// bool backtrack(int i, vector<pair<double, double> > &res)
// {
// 	int n = res.size();
// 	if (i == n)
// 		return true;
// 	if (res[i].fi - res[i - 1].fi >= -EPS && res[i].se - res[i - 1].se >= -EPS) {
// 		if (backtrack(i + 1, res))
// 			return true;
// 	}
// 	swap(res[i].fi, res[i].se);
// 	if (res[i].fi - res[i - 1].fi >= -EPS && res[i].se - res[i - 1].se >= -EPS) {
// 		if (backtrack(i + 1, res))
// 			return true;
// 	}
// 	return false;
// }

void solve()
{
	int n;
	cin >> n;
	vector<double> M(n), m(n);
	for (int i = 0; i < n; i++) {
		cin >> M[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> m[i];
	}
	for (int i = 1; i < n; i++) {
		m[i] += m[i - 1];
		M[i] += M[i - 1];
	}
	// for (int i = 0; i < n; i++) {
	// 	cout << sum[i] << " " << product[i] << "\n";
	// }

	vector<pair<double, double> > res(n);
	for (int i = 0; i < n; i++) {
		double x = m[i];
		double y = M[i];
		double delta = fabs((x + y) * (x + y) - 4 * y);
		res[i] = {
			(x + y + sqrtl(delta)) / 2.0L,
			(x + y - sqrtl(delta)) / 2.0L,
		};
	}
	// backtrack(1, res);
	for (int i = n - 1; i > 0; i--) {
		res[i].fi -= res[i - 1].fi;
		res[i].se -= res[i - 1].se;
	}

	for (int i = 0; i < n; i++) {
		cout << fixed << setprecision(10) << res[i].fi << " ";
	}
	cout << "\n";
	for (int i = 0; i < n; i++) {
		cout << fixed << setprecision(10) << res[i].se << " ";
	}
	cout << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
