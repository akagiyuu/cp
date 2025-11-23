#include <bits/stdc++.h>
#include <iomanip>

using namespace std;

#define double long double

const double PI = acos(-1);
const double EPS = 1e-8;
const double INF = 1e18;

typedef complex<double> P;
typedef vector<P> G;
struct C {
	P p;
	double r;
	C()
	{
	}
	C(const P &p, double r)
		: p(p)
		, r(r)
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
			if (cr <= EPS)
				lower.pop_back();
			else
				break;
		}
		lower.push_back(p);
	}
	for (int i = (int)a.size() - 1; i >= 0; --i) {
		P p = a[i];
		while (upper.size() >= 2) {
			P A = upper[upper.size() - 2];
			P B = upper[upper.size() - 1];
			double cr = cross(B - A, p - A);
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
	int ia = int(min_element(A.begin(), A.end()) - A.begin());
	int ib = int(min_element(B.begin(), B.end()) - B.begin());
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

C circle2(const P &a, const P &b)
{
	P c = (a + b) * P(0.5, 0);
	return C(c, abs(a - c));
}
C circle3(const P &a, const P &b, const P &c)
{
	double ax = real(a), ay = imag(a), bx = real(b), by = imag(b), cx = real(c), cy = imag(c);
	double d = 2 * (ax * (by - cy) + bx * (cy - ay) + cx * (ay - by));
	if (fabs(d) < EPS)
		return C(P(0, 0), -1);
	double A = ax * ax + ay * ay, B = bx * bx + by * by, Cc = cx * cx + cy * cy;
	P o = P((A * (by - cy) + B * (cy - ay) + Cc * (ay - by)) / d,
		(A * (cx - bx) + B * (ax - cx) + Cc * (bx - ax)) / d);
	return C(o, abs(o - a));
}
bool inC(const C &c, const P &p)
{
	return c.r >= 0 && abs(p - c.p) <= c.r + EPS;
}

C welzl(vector<P> &pts, vector<P> &R, int n)
{
	if (n == 0 || R.size() == 3) {
		if (R.empty())
			return C(P(0, 0), -1);
		if (R.size() == 1)
			return C(R[0], 0);
		if (R.size() == 2)
			return circle2(R[0], R[1]);
		return circle3(R[0], R[1], R[2]);
	}
	P p = pts[n - 1];
	C D = welzl(pts, R, n - 1);
	if (D.r >= 0 && inC(D, p))
		return D;
	R.push_back(p);
	C D2 = welzl(pts, R, n - 1);
	R.pop_back();
	return D2;
}
C minimum_enclosing_circle(G pts)
{
	random_device rd;
	mt19937 g(rd());
	shuffle(pts.begin(), pts.end(), g);
	vector<P> R;
	C ans = welzl(pts, R, (int)pts.size());
	if (ans.r < 0)
		return C(P(0, 0), 0);
	return ans;
}

void solve()
{
	int n;
	cin >> n;
	G A(n);
	for (int i = 0; i < n; i++) {
		double x, y;
		cin >> x >> y;
		A[i].real(x);
		A[i].imag(y);
	}

	int m;
	cin >> m;
	G B(m);
	for (int i = 0; i < m; i++) {
		double x, y;
		cin >> x >> y;
		x = -x;
		y = -y;
		B[i].real(x);
		B[i].imag(y);
	}
	G S = minkowski_sum(A, B);
	C res = minimum_enclosing_circle(S);
	cout << setprecision(10) << res.r << " " << -res.p.real() << " " << -res.p.imag() << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
