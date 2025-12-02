#include <bits/stdc++.h>
#include <complex>

#define int long long
#define double long double

using namespace std;

const double PI = acos(-1);

typedef complex<double> P;
typedef vector<P> G;

double cross(const P &a, const P &b)
{
	return imag(conj(a) * b);
}

double area(const G &g)
{
	int n = g.size();
	double A = 0;
	for (int i = 0; i < n; i++)
		A += cross(g[i], g[(i + 1) % n]);
	return fabsl(A / 2);
}

P rotate(P p, double ang)
{
	return p * P(cos(ang), sin(ang));
}

void solve()
{
	int n = 6;
	vector<double> edges(n);
	for (int i = 0; i < n; i++) {
		cin >> edges[i];
	}
	G g(6);
	g[0] = P(0, 0);
	g[n - 1] = P(0, edges[0]);
	double ang = 2.0L * PI / 3.0L;
	for (int i = 1; i < n - 1; i++) {
		g[i] = rotate(g[(i + n - 2) % n] - g[i - 1], ang);
		g[i] = g[i - 1] + g[i] / abs(g[i]) * edges[i];
	}

	int res = round(area(g) * 4.0L / sqrtl(3.0L));
	cout << res << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
