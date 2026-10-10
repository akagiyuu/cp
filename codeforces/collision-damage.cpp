#include <bits/stdc++.h>

using namespace std;

#define int long long

const double EPS = 1e-8;
const double INF = 1e18;
typedef complex<double> P;
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
double cross(const P &a, const P &b)
{
	return imag(conj(a) * b);
}
double dot(const P &a, const P &b)
{
	return real(conj(a) * b);
}
double area(const G &g)
{
	int n = g.size();
	double A = 0;
	for (int i = 0; i < n; ++i)
		A += cross(g[i], g[(i + 1) % n]);
	return abs(A / 2);
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
G minkowski_sum(const G &A0, const G &B0)
{
	G A = convex_hull(A0), B = convex_hull(B0);
	if (A.empty() || B.empty())
		return {};
	int ia = min_element(A.begin(), A.end()) - A.begin();
	int ib = min_element(B.begin(), B.end()) - B.begin();
	int n = (int)A.size(), m = (int)B.size();
	G a(n), b(m);

	for (int i = 0; i < n; ++i)
		a[i] = A[(ia + i) % n];
	for (int j = 0; j < m; ++j)
		b[j] = B[(ib + j) % m];
	vector<P> r;
	r.reserve(n + m);
	r.push_back(a[0] + b[0]);
	int i = 0, j = 0;
	while (i < n && j < m) {
		P va = a[(i + 1) % n] - a[i], vb = b[(j + 1) % m] - b[j];
		if (cross(va, vb) >= -EPS) {
			r.push_back(r.back() + va);
			++i;
		} else {
			r.push_back(r.back() + vb);
			++j;
		}
	}
	while (i < n) {
		r.push_back(r.back() + (a[(i + 1) % n] - a[i]));
		++i;
	}
	while (j < m) {
		r.push_back(r.back() + (b[(j + 1) % m] - b[j]));
		++j;
	}
	if (!r.empty() && abs(r.front() - r.back()) < EPS)
		r.pop_back();
	return convex_hull(r);
}

void solve()
{
	int n, m;
	cin >> n >> m;
	G p(n), q(m), neg_q(m);
	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		p[i] = P(x, y);
	}
	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		q[i] = P(x, y);
		neg_q[i] = P(-x, -y);
	}
	auto t = minkowski_sum(p, neg_q);
	double res = area(p) * area(q) / area(t);
	cout << fixed << setprecision(6) << res << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		solve();
}
