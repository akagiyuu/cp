#include <bits/stdc++.h>
#include <cassert>

#define int long long
#define double long double

using namespace std;

const double PI = acos(-1);
const double EPS = 1e-8;

typedef complex<double> P;
struct L : vector<P> {
	L(const P &a, const P &b)
	{
		push_back(a);
		push_back(b);
	}
	L()
	{
	}
};
typedef vector<P> G;

double cross(const P &a, const P &b)
{
	return imag(conj(a) * b);
}

P rotate(P p, double angle)
{
	return p * P(cosl(angle), sinl(angle));
}

P crosspoint(const L &l, const L &m)
{
	double A = cross(l[1] - l[0], m[1] - m[0]);
	double B = cross(l[1] - l[0], l[1] - m[0]);
	if (abs(A) < EPS && abs(B) < EPS)
		return m[0];
	return m[0] + B / A * (m[1] - m[0]);
}

double area(const G &g)
{
	int n = g.size();
	double A = 0;
	for (int i = 0; i < n; i++) {
		A += cross(g[i], g[(i + 1) % n]);
	}
	return fabsl(A / 2.0L);
}

void solve()
{
	int n;
	cin >> n;
	double r;
	cin >> r;
	double base_angle = 2.0L * PI / (double)n;
	int cnt = (n - 1) / 2;
	double adj_angle = base_angle * (double)cnt;
	P a1(0, r);
	auto a2 = rotate(a1, -adj_angle - base_angle);
	auto b1 = rotate(a1, base_angle);
	auto b2 = rotate(b1, -adj_angle);

	auto c = crosspoint(L(a1, a2), L(b1, b2));
	double res = area({ a1, c, b1 });
	res = 0.5L * sinl(base_angle) * r * r - res;
	res *= (double)n;
	cout << fixed << setprecision(10) << res << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
