#include <bits/stdc++.h>

#define int long long
#define double float

using namespace std;

const double PI = acos(-1);
const double EPS = 1e-8;

typedef complex<double> pt;

double cross(const pt &a, const pt &b)
{
	return imag(conj(a) * b);
}

double angle(const pt &a, const pt &b)
{
	double ret = arg(b) - arg(a);
	return (ret >= 0) ? ret : ret + 2 * PI;
}

typedef array<pt, 2> L;

pt crosspoint(const L &l, const L &m)
{
	double A = cross(l[1] - l[0], m[1] - m[0]);
	double B = cross(l[1] - l[0], l[1] - m[0]);
	if (abs(A) < EPS && abs(B) < EPS)
		return m[0];
	if (abs(A) < EPS)
		assert(false);
	return m[0] + B / A * (m[1] - m[0]);
}

void solve()
{
	int n, h;
	cin >> n >> h;

	double tmp;
	vector<pt> a(n);
	for (int i = 0; i < n; i++) {
		cin >> tmp;
		a[i].real(tmp);
		cin >> tmp;
		a[i].imag(tmp);
	}

	pt e = a[n - 1];
	e += complex<double>(0, h);

	vector<double> ang(n);
	for (int i = 0; i < n; i++) {
		ang[i] = angle(complex<double>(0, 1), a[i] - e);
	}
	//
	// cout << e << "\n";
	// cout << a[5] << " " << Ox - e << "\n";
	// cout << angle2(a[5] - e, Ox - e) << "\n";

	double cur = 2 * PI;
	pt curp;
	double res = 0;
	for (int i = n - 1; i >= 1; i--) {
		if (ang[i - 1] > ang[i]) {
			if (ang[i] < cur) {
				cur = ang[i];
				curp = a[i];
			}
			continue;
		}
		if (cur >= ang[i]) {
			// cout << i << " " << abs(a[i - 1] - a[i]) << "\n";
			res += abs(a[i] - a[i - 1]);
			if (ang[i] < cur) {
				cur = ang[i];
				curp = a[i];
			}
			continue;
		}
		if (cur <= ang[i - 1]) {
			if (ang[i] < cur) {
				cur = ang[i];
				curp = a[i];
			}
			continue;
		}
		auto c = crosspoint({ a[i], a[i - 1] }, { curp, e });

		res += abs(a[i - 1] - c);
		// cout << i << " " << abs(a[i - 1] - c) << "\n";
		if (ang[i] < cur) {
			cur = ang[i];
			curp = a[i];
		}
	}
	cout << fixed << setprecision(10) << res << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
