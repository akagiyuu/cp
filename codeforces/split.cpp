#include <bits/stdc++.h>

using namespace std;

#define int long long
typedef complex<double> cd;

void solve()
{
	int N;
	cin >> N;
	int a, b, c, d, e, f;
	cin >> a >> b >> c >> d >> e >> f;
	auto cal = [a, b, c, d, e, f](int k) {
		return cd((double)((a + b * k) ^ (c * k)) * 1e-3, (double)((d + e * k) ^ (f * k)) * 1e-3);
	};

	int m;
	cin >> m;
	while (m--) {
		int k;
		cin >> k;
		auto z1 = cal(k), z2 = conj(cal((N - k) % N));
		auto x = (z1 + z2) * 0.5;
		auto y = (z1 - z2) * cd(0.0, -0.5);
		cout << fixed << setprecision(4) << x.real() << ' ' << x.imag() << ' ' << y.real() << ' ' << y.imag()
		     << '\n';
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
