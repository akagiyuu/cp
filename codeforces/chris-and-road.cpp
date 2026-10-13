#include <bits/stdc++.h>

using namespace std;

#define int long long
#define double long double

typedef complex<double> P;
typedef vector<P> G;

double dot(const P &a, const P &b)
{
	return real(conj(a) * b);
}

double solve()
{
	int n;
	double w, v, u;
	cin >> n >> w >> v >> u;
	G bus(n);
	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		bus[i] = P(x, y);
	}

	P d(-u, v);
	P M = bus[0], m = bus[0];
	for (int i = 1; i < n; i++) {
		if (dot(bus[i], d) > dot(M, d))
			M = bus[i];
		if (dot(bus[i], d) < dot(m, d))
			m = bus[i];
	}
	double x1 = M.real() - M.imag() * v / u;
	double x2 = m.real() - m.imag() * v / u;
	if (x1 >= 0 || x2 <= 0)
		return w / u;
	return x2 / v + w / u;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cout << fixed << setprecision(6) << solve() << '\n';
}
