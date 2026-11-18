#include <bits/stdc++.h>

using namespace std;

#define int long long
#define double long double

struct dat {
	double p, t;
};

double calc(const vector<dat> &t)
{
	int n = t.size();
	double suf = 1;
	double a = 0;
	for (int i = n - 1; i >= 0; i--) {
		a += t[i].t * suf;
		suf *= t[i].p;
	}
	return a / suf;
}

double solve()
{
	int n;
	cin >> n;
	vector<int> _t(n), _s(n), _f(n), _c(n);
	for (int i = 0; i < n; i++)
		cin >> _t[i] >> _s[i] >> _f[i] >> _c[i];
	for (int i = 0; i < n; i++)
		if (_s[i] == 0)
			return -1;

	vector<dat> t(n);
	for (int i = 0; i < n; i++) {
		t[i] = {
			.p = (double)_s[i] / (double)(_s[i] + _c[i]),
			.t = (double)_t[i] * (double)(_s[i] + _f[i] + _c[i]) / (double)(_s[i] + _c[i]),
		};
	}
	double res = calc(t);
	if (res == -1)
		return -1;
	while (true) {
		bool cont = false;
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				swap(t[i], t[j]);
				double cur = calc(t);
				if (cur < res) {
					res = cur;
					cont = true;
				} else {
					swap(t[i], t[j]);
				}
			}
		}
		if (!cont)
			break;
	}

	return res;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--) {
		double res = solve();
		if (res == -1)
			cout << "impossible\n";
		else
			cout << fixed << setprecision(10) << res << '\n';
	}
}
