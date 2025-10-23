#include <bits/stdc++.h>

using namespace std;

#define double long double
typedef complex<double> P;
#define int long long
#define PI 3.14159265358979323846
#define curr(P, i) P[i]
#define next(P, i) P[(i + 1) % P.size()]

bool operator<(const P &a, const P &b)
{
	return real(a) != real(b) ? real(a) < real(b) : imag(a) < imag(b);
}

double cross(const P &a, const P &b)
{
	return imag(conj(a) * b);
}
double dot(const P &a, const P &b)
{
	return real(conj(a) * b);
}

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

P projection(const L &l, const P &p)
{
	double t = dot(p - l[0], l[0] - l[1]) / norm(l[0] - l[1]);
	return l[0] + t * (l[0] - l[1]);
}

double area(const vector<P> &v)
{
	double A = 0;
	for (int i = 0; i < v.size(); ++i) {
		A += cross(v[i], next(v, i));
	}
	return abs(A / 2);
}

P centroid(const vector<P> &v)
{
	double S = 0;
	P res;
	for (int i = 0; i < v.size(); i++) {
		int j = i + 1;
		if (j == v.size())
			j = 0;
		double tmp = cross(v[i], v[j]);
		S += tmp;
		res += (v[i] + v[j]) * tmp;
	}
	S /= 2;
	res /= 6 * S;
	return res;
}
double angle(const P &a, const P &b)
{
	double ret = arg(b) - arg(a);
	return (ret >= 0) ? ret : ret + 2 * PI;
}
double angle2(const P &a, const P &b)
{
	return min(angle(a, b), angle(b, a));
}

double get_multiplier(const P &a, const P &b, const P &c)
{
	auto projected = projection(L(a, b), c);
	auto d = projected - a;

	return real(d) / real(b - a);
}

void solve()
{
	int n;
	cin >> n;
	double x, y;
	vector<P> v(n);
	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		v[i].real(x);
		v[i].imag(y);
	}
	auto c = centroid(v);
	vector<double> res;
	for (int i = 0; i < n; i++) {
		res.push_back(angle(c - v[i], c - v[(i + 1) % n]));
	}
	for (int q = 0; q < 2; q++) {
		for (int i = 0; i < n; i++) {
			auto multiplier = get_multiplier(v[i], v[(i + 1) % n], c);
			if (multiplier > 1) {
				res[(i + 1) % n] += res[i];
				res[i] = 0;
			}
		}
	}
	for (int q = 0; q < 2; q++) {
		for (int i = n - 1; i >= 0; i--) {
			auto multiplier = get_multiplier(v[(i - 1 + n) % n], v[i], c);
			auto val = (i - 1 + n) % n;
			if (multiplier < 0) {
				res[(val - 1 + n) % n] += res[val];
				res[val] = 0;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		cout << setprecision(10) << res[i] / (2 * PI) << "\n";
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
