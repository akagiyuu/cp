#include <bits/stdc++.h>

using namespace std;

#define int long long
#define double long double

const double PI = acos(-1);
const double EPS = 1e-8;

typedef complex<double> P;
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
double cross(const P &a, const P &b)
{
	return imag(conj(a) * b);
}
double dot(const P &a, const P &b)
{
	return real(conj(a) * b);
}
P projection(const L &l, const P &p)
{
	double t = dot(p - l[0], l[0] - l[1]) / norm(l[0] - l[1]);
	return l[0] + t * (l[0] - l[1]);
}
P reflection(const L &l, const P &p)
{
	return p + P(2, 0) * (projection(l, p) - p);
}
bool intersect(const L &s, const P &p)
{
	return abs(s[0] - p) + abs(s[1] - p) - abs(s[1] - s[0]) < EPS;
}

void solve()
{
	int n;
	cin >> n;
	P o;
	int x, y;
	cin >> x >> y;
	o = P(x, y);
	vector<P> a(n);
	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		a[i] = P(x, y) - o;
	}
	o = P(0, 0);

	double rmin = abs(a[0]), rmax = abs(a[0]);
	for (int i = 1; i < n; i++) {
		double r = abs(a[i]);
		rmin = min(rmin, r);
		rmax = max(rmax, r);
	}
	for (int i = 0; i < n; i++) {
		int j = (i + 1) % n;
		L edge(a[i], a[j]);
		auto p = projection(edge, o);
		if (!intersect(edge, p))
			continue;
		double r = abs(p);
		rmin = min(rmin, r);
		rmax = max(rmax, r);
	}
	double res = PI * (rmax * rmax - rmin * rmin);
	cout << fixed << setprecision(6) << res << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
