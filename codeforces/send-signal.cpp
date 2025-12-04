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

	bool has_greater = true;
	int cnt = 0;

	auto get_tier = [&](int x) {
		if (x < d1)
			return 0;
		if (x == d1)
			return 1;
		if (x < d2)
			return 2;
		if (x == d2)
			return 3;
		return 4;
	};

	for (int i = 0; i < n - 1; i++) {
		auto x = a[i] - b[i];
		auto y = a[i + 1] - a[i] - (b[i + 1] - b[i]);

		double A = norm(y), B = 2.0L * dot(x, y), C = norm(x);
		auto f = [&](double x) { return A * x * x + B * x + C; };

		double l = 0.L;
		double mid = -B / (2.0L * A);
		double r = 1.L;
		if (mid <= l || mid >= r) {
			continue;
			double fl = f(l), fr = f(r);
			auto tl = get_tier(fl), tr = get_tier(fr);
		}
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
