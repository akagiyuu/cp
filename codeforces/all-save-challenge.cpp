#include <bits/stdc++.h>
#include <cassert>

using namespace std;

#define int long long
#define double long double

const double PI = acos(-1);
const double EPS = 1e-8;
const double INF = 1e32;
typedef complex<double> P;
typedef vector<P> G;
struct L : public vector<P> {
	L(const P &a, const P &u)
	{
		push_back(a);
		push_back(u);
	}
	L()
	{
	}
};
namespace std
{
bool operator<(const P &a, const P &b)
{
	return real(a) != real(b) ? real(a) < real(b) : imag(a) < imag(b);
}
}
double cross(const P &a, const P &b)
{
	return imag(conj(a) * b);
}
double dot(const P &a, const P &b)
{
	return real(conj(a) * b);
}
P rotate(P p, double angle)
{
	return p * P(cos(angle), sin(angle));
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
G convex_hull(G ps)
{
	if (ps.size() <= 1)
		return ps;
	sort(ps.begin(), ps.end());
	G a;
	for (auto &p : ps) {
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
			double cr = cross(B - A, p - A);
			// use cr < -EPS to keep collinear
			if (cr <= EPS)
				lower.pop_back();
			else
				break;
		}
		lower.push_back(p);
	}
	for (int i = a.size() - 1; i >= 0; --i) {
		P p = a[i];
		while (upper.size() >= 2) {
			P A = upper[upper.size() - 2];
			P B = upper[upper.size() - 1];
			double cr = cross(B - A, p - A);
			// use cr < -EPS to keep collinear
			if (cr <= EPS)
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
P crosspoint(const L &l, const L &m)
{
	double A = cross(l[1] - l[0], m[1] - m[0]);
	double B = cross(l[1] - l[0], l[1] - m[0]);
	if (abs(A) < EPS && abs(B) < EPS)
		return m[0]; // same line
	assert(abs(A) >= EPS);

	return m[0] + B / A * (m[1] - m[0]);
}

int next(int i, int n)
{
	return (i + 1) % n;
}
double area(double s)
{
	return sqrt(3) * s * s / 4.;
}

double solve()
{
	int n;
	cin >> n;
	G ps(n);
	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		ps[i] = P(x, y);
	}
	if (n == 1)
		return 0;
	if (n == 2) {
		double s = abs(ps[1] - ps[0]);
		return area(s);
	}
	ps = convex_hull(ps);
	n = ps.size();
	int j = 0, k = 0;
	auto a = ps[0], b = ps[1];
	auto n1 = rotate(b - a, PI / 6.), n2 = rotate(b - a, 5. * PI / 6.);
	for (int t = 0; t < n; t++) {
		if (dot(ps[t], n1) > dot(ps[j], n1))
			j = t;
		if (dot(ps[t], n2) > dot(ps[k], n2))
			k = t;
	}
	auto res = INF;
	for (int i = 0; i < n; i++) {
		auto a = ps[i], b = ps[next(i, n)];
		auto n1 = rotate(b - a, PI / 6.), n2 = rotate(b - a, 5. * PI / 6.);
		while (dot(ps[next(j, n)], n1) > dot(ps[j], n1))
			j = next(j, n);
		while (dot(ps[next(k, n)], n2) > dot(ps[k], n2))
			k = next(k, n);
		L l0(a, b);
		L l1(ps[j], ps[j] + P(imag(n1), -real(n1)));
		L l2(ps[k], ps[k] + P(imag(n2), -real(n2)));
		auto d = crosspoint(l0, l1), e = crosspoint(l0, l2);
		auto s = abs(e - d);
		res = min(res, area(s));
	}
	return res;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cout << fixed << setprecision(6) << solve() << '\n';
}
