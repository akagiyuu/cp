#include <bits/stdc++.h>

using namespace std;

#define int long long
#define double long double

double solve()
{
	int x1, y1, r1, x2, y2, r2;
	cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
	double dx = x1 - x2;
	double dy = y1 - y2;
	double d = sqrt(dx * dx + dy * dy);
	if (d < abs(r2 - r1)) {
		return ((double)abs(r2 - r1) - d) / 2.;
	} else if (d > r1 + r2) {
		return (d - (double)r1 - (double)r2) / 2.;
	} else {
		return 0;
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cout << fixed << setprecision(6) << solve() << '\n';
}
