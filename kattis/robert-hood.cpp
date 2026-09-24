#include <bits/stdc++.h>

using namespace std;

#define int long long
#define double long double

typedef complex<int> P;
typedef vector<P> G;
struct L : public vector<P> {
	L(const P &a, const P &b)
	{
		push_back(a);
		push_back(b);
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
int cross(const P &a, const P &b)
{
	return imag(conj(a) * b);
}
int dot(const P &a, const P &b)
{
	return real(conj(a) * b);
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
		if (a.empty() || abs(a.back() - p) > 0)
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
			if (cr <= 0)
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
			if (cr <= 0)
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
double dist(const P &a, const P &b)
{
	return sqrt(dot(b - a, b - a));
}

int next(int i, int n)
{
	return (i + 1) % n;
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
	ps = convex_hull(ps);
	n = ps.size();
	int j = 0;
	auto a = ps[0], b = ps[1];
	P n0(-imag(b - a), real(b - a));
	for (int t = 0; t < n; t++)
		if (dot(ps[t], n0) > dot(ps[j], n0))
			j = t;
	double res = 0;
	for (int i = 0; i < n; i++) {
		auto a = ps[i], b = ps[next(i, n)];
		P n0(-imag(b - a), real(b - a));
		while (dot(ps[next(j, n)], n0) > dot(ps[j], n0))
			j = next(j, n);
		res = max(res, dist(ps[j], a));
		res = max(res, dist(ps[j], b));
		if (cross(b - a, ps[next(j, n)] - ps[j]) == 0) {
			res = max(res, dist(ps[next(j, n)], a));
			res = max(res, dist(ps[next(j, n)], b));
		}
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
