#include <bits/stdc++.h>

using namespace std;

#define int long long

const double PI = acos(-1);
const double EPS = 1e-6;

typedef complex<double> P;

P rotate(P p, double angle)
{
	return p * P(cos(angle), sin(angle));
}

int cnt_main_direction(vector<P> &a)
{
	int n = a.size();
	int res = 0;

	sort(a.begin(), a.end(), [](const P &a, const P &b) { return real(a) < real(b); });
	int cur = 1;
	for (int i = 1; i < n; i++) {
		if (abs(real(a[i] - a[i - 1])) < EPS) {
			cur++;
		} else {
			res += cur * (cur - 1);
			cur = 1;
		}
	}
	res += cur * (cur - 1);

	sort(a.begin(), a.end(), [](const P &a, const P &b) { return imag(a) < imag(b); });
	cur = 1;
	for (int i = 1; i < n; i++) {
		if (abs(imag(a[i] - a[i - 1])) < EPS) {
			cur++;
		} else {
			res += cur * (cur - 1);
			cur = 1;
		}
	}
	res += cur * (cur - 1);

	return res;
}

void solve()
{
	int n;
	cin >> n;
	vector<P> a(n);
	for (int i = 0; i < n; i++) {
		double x, y;
		cin >> x >> y;
		a[i] = P(x, y);
	}
	int res = cnt_main_direction(a);
	// cout << "TEST:\n";
	for (int i = 0; i < n; i++) {
		a[i] = rotate(a[i], PI / 4);
	}
	res += cnt_main_direction(a);
	// for (int i = 0; i < n; i++) {
	// 	cout << real(a[i]) << " " << imag(a[i]) << "\n";
	// }
	// cout << "\n";
	cout << res << "\n";
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
