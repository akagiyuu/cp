#include <bits/stdc++.h>

using namespace std;

#define int long long
#define double long double

const double INF = 1e32;

double solve_quad(double a, double b, double c)
{
	if (a == 0) {
		if (b == 0)
			return INF;
		double x = -c / b;
		if (x >= 0)
			return x;
		return INF;
	}
	double delta = b * b - 4. * a * c;
	double x1 = (-b + sqrt(delta)) / (2. * a);
	double x2 = (-b - sqrt(delta)) / (2. * a);
	if (x1 > x2)
		swap(x1, x2);
	if (x1 >= 0)
		return x1;
	if (x2 >= 0)
		return x2;
	return INF;
}

double find_intersect(double x, double y, double u, double v)
{
	double a = u * u - v * v;
	double b = 2 * u * x;
	double c = x * x + y * y;
	return solve_quad(a, b, c);
}

double solve()
{
	double w, x1, x2, yc, u, v;
	cin >> w >> x1 >> x2 >> yc >> u >> v;

	double t0 = yc / v;
	double res = INF;

	double l = x1 + u * t0;
	double r = x2 + u * t0;

	if (l >= 0 || r <= 0)
		res = w / v;

	if (u > 0 && x1 < 0)
		res = min(res, max(t0, -x1 / u) + (w - yc) / v);

	if (u < 0 && x2 > 0)
		res = min(res, max(t0, -x2 / u) + (w - yc) / v);

	res = min(res, find_intersect(x1, yc, u, v) + (w - yc) / v);
	res = min(res, find_intersect(x2, yc, u, v) + (w - yc) / v);

	return res;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		cout << fixed << setprecision(6) << solve() << '\n';
}
