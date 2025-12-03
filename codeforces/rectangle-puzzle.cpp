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

namespace std
{
bool operator<(const P &a, const P &b)
{
	return real(a) != real(b) ? real(a) < real(b) : imag(a) < imag(b);
}
}

double dot(const P &a, const P &b)
{
	return real(conj(a) * b);
}

double cross(const P &a, const P &b)
{
	return imag(conj(a) * b);
}

int ccw(P a, P b, P c)
{
	b -= a;
	c -= a;
	if (cross(b, c) > 0)
		return +1; // counter clockwise
	if (cross(b, c) < 0)
		return -1; // clockwise
	if (dot(b, c) < 0)
		return +2; // c--a--b on line
	if (norm(b) < norm(c))
		return -2; // a--b--c on line
	return 0;
}

bool intersect(const L &s, const L &t)
{
	return ccw(s[0], s[1], t[0]) * ccw(s[0], s[1], t[1]) <= 0 && ccw(t[0], t[1], s[0]) * ccw(t[0], t[1], s[1]) <= 0;
}

pair<P, bool> crosspoint(const L &l, const L &m)
{
	double A = cross(l[1] - l[0], m[1] - m[0]);
	double B = cross(l[1] - l[0], l[1] - m[0]);
	if (abs(A) < EPS && abs(B) < EPS)
		return { m[0], true };
	if (B / A < 0 || B / A > 1)
		return { P(0, 0), false };
	return { m[0] + B / A * (m[1] - m[0]), true };
}

P rotate(const P &p, double a)
{
	return p * P(cosl(a), sinl(a));
}

G convex_hull(G g)
{
	if (g.size() <= 1)
		return g;
	sort(g.begin(), g.end());

	G a;
	for (auto &p : g) {
		if (a.empty() || abs(a.back() - p) > EPS)
			a.push_back(p);
	}
	if (a.size() <= 1)
		return a;
	G lower, upper;
	for (auto &p : a) {
		while (lower.size() >= 2) {
			P A = lower[lower.size() - 2];
			P B = lower[lower.size() - 1];
			if (cross(B - A, p - A) <= EPS)
				lower.pop_back();
			else
				break;
		}
		lower.push_back(p);
	}
	for (int i = a.size() - 1; i >= 0; i--) {
		P p = a[i];
		while (upper.size() >= 2) {
			P A = upper[upper.size() - 2];
			P B = upper[upper.size() - 1];
			if (cross(B - A, p - A) <= EPS)
				upper.pop_back();
			else
				break;
		}
		upper.push_back(p);
	}

	lower.pop_back();
	upper.pop_back();
	G res = lower;
	res.insert(res.end(), upper.begin(), upper.end());

	if (res.empty())
		return a;
	return res;
}

double area(const G &g)
{
	double A = 0;
	int n = g.size();
	for (int i = 0; i < n; i++) {
		A += cross(g[i], g[(i + 1) % n]);
	}
	return fabsl(A / 2.0L);
}

double solve()
{
	double w, h, a;
	cin >> w >> h >> a;
	a = a / 180.0L * PI;

	G ga = {
		P(w / 2.0L, -h / 2.0L),
		P(w / 2.0L, h / 2.0L),
		P(-w / 2.0L, h / 2.0L),
		P(-w / 2.0L, -h / 2.0L),
	};
	int n = ga.size();
	G gb = ga;
	for (int i = 0; i < (int)gb.size(); i++) {
		gb[i] = rotate(ga[i], a);
	}
	G g;
	for (int i = 0; i < n; i++) {
		L l1(ga[i], ga[(i + 1) % n]);
		for (int j = 0; j < n; j++) {
			L l2(gb[j], gb[(j + 1) % n]);
			auto [p, exist] = crosspoint(l1, l2);
			if (!exist)
				continue;
			g.push_back(p);
		}
	}
	return area(convex_hull(g));
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cout << fixed << setprecision(10) << solve() << "\n";
}
