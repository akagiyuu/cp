#include <bits/stdc++.h>

#define int long long
#define double long double

using namespace std;

typedef complex<double> P;

double dot(const P &a, const P &b)
{
	return real(conj(a) * b);
}

int solve()
{
	int n;
	cin >> n;
	double d1, d2;
	cin >> d1 >> d2;
	d1 *= d1;
	d2 *= d2;
	vector<P> a(n), b(n);
	for (int i = 0; i < n; i++) {
		double x, y;
		cin >> x >> y;
		a[i] = P(x, y);

		cin >> x >> y;
		b[i] = P(x, y);
	}

	vector<double> dist;

	for (int i = 0; i < n - 1; i++) {
		auto x = a[i] - b[i];
		auto y = a[i + 1] - a[i] - (b[i + 1] - b[i]);

		double A = norm(y), B = 2.0L * dot(x, y), C = norm(x);
		auto f = [&](double x) { return A * x * x + B * x + C; };
		double mid = -B / (2.0L * A);
		dist.push_back(f(0.L));
		if (0.L < mid && mid < 1.L) {
			dist.push_back(f(mid));
		}
		dist.push_back(f(1.L));
	}

	bool has_greater = true;
	int cnt = 0;
	for (auto d : dist) {
		if (d <= d1) {
			cnt += has_greater;
			has_greater = false;
		}
		if (d > d2)
			has_greater = true;
	}

	return cnt;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cout << solve() << "\n";
}
