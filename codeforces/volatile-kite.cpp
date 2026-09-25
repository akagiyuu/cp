#include <bits/stdc++.h>

using namespace std;

#define int long long
#define double long double

const double INF = 1e32;
const double PI = acos(-1);

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
double distanceLP(const L &l, const P &p)
{
	return abs(p - projection(l, p));
}

void solve()
{
	int n;
	cin >> n;
	vector<P> a(n);
	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		a[i] = P(x, y);
	}

	double res = INF;
	for (int i = 0; i < n; i++) {
		int j = (i + 1) % n;
		int k = (i + n - 1) % n;
		double cur = distanceLP(L(a[j], a[k]), a[i]) / 2.;
		res = min(res, cur);
	}
	cout << fixed << setprecision(6) << res << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
