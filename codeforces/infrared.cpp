#include <bits/stdc++.h>
#include <iomanip>

#define int long long
#define double long double

using namespace std;

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

P projection(const L &l, const P &p)
{
	double t = dot(p - l[0], l[0] - l[1]) / norm(l[0] - l[1]);
	return l[0] + t * (l[0] - l[1]);
}

P reflection(const L &l, const P &p)
{
	return p + P(2, 0) * (projection(l, p) - p);
}
double cross(const P &a, const P &b)
{
	return imag(conj(a) * b);
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
double angle(const P &a, const P &b)
{
	double ret = arg(b) - arg(a);
	return ret;
}

void solve()
{
	int n;
	cin >> n;
	vector<P> g(n);
	for (int i = 0; i < n; i++) {
		double x, y;
		cin >> x >> y;
		g[i].real(x);
		g[i].imag(y);
	}
	vector<P> refl_g = g;
	for (int i = 1; i < n - 1; i++) {
		L edge(refl_g[i], refl_g[i + 1]);
		for (int j = 0; j < n; j++) {
			refl_g[j] = reflection(edge, refl_g[j]);
		}
	}
	auto p = g[0];
	auto refl_p = refl_g[0];
	L refl_line(p, refl_p);

	auto check = [&](const L &line) {
		refl_g = g;
		for (int i = 1; i < n - 1; i++) {
			L edge(refl_g[i], refl_g[i + 1]);
			auto inter = crosspoint(line, edge);
			auto alpha = real(inter - refl_g[i + 1]) / real(refl_g[i] - refl_g[i + 1]);
			if (min(alpha, 1.L - alpha) < 1e-5)
				return false;
			for (int j = 0; j < n; j++) {
				refl_g[j] = reflection(edge, refl_g[j]);
			}
		}
		return true;
	};
	if (!check(refl_line)) {
		cout << "NO\n";
		return;
	}

	auto res = angle(complex<double>(1, 0), refl_p - p);
	cout << "YES\n";
	// cout << g[0] << "\n";
	// cout << refl_g[0] << "\n";
	cout << fixed << setprecision(10) << res * 180.L / PI << "\n";
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
