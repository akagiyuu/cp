#include <bits/stdc++.h>
#include <cassert>

using namespace std;

#define int long long
#define double long double

typedef complex<double> P;

void solve()
{
	int a, b, c, x1, y1, x2, y2;
	cin >> a >> b >> c >> x1 >> y1 >> x2 >> y2;
	double res = abs(x2 - x1) + abs(y2 - y1);
	for (int i = 0; i <= 1; i++) {
		for (int j = 0; j <= 1; j++) {
			if (a == 0 && (i == 0 || j == 0))
				continue;
			if (b == 0 && (i == 1 || j == 1))
				continue;
			P A(x1, y1), B(x2, y2), C, D;
			if (i == 0)
				C = P(-(double)(b * y1 + c) / (double)a, y1);
			else
				C = P(x1, -(double)(a * x1 + c) / (double)b);
			if (j == 0)
				D = P(-(double)(b * y2 + c) / (double)a, y2);
			else
				D = P(x2, -(double)(a * x2 + c) / (double)b);
			double cur = abs(C - A) + abs(D - C) + abs(D - B);
			res = min(res, cur);
		}
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
