#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

double solve()
{
	double x1, y1, r1, x2, y2, r2;
	cin >> x1 >> y1 >> r1;
	cin >> x2 >> y2 >> r2;
	x2 -= x1;
	y2 -= y1;

	double a = 2 * x2, b = 2 * y2, c = pow(r2, 2) - pow(r1, 2) - pow(x2, 2) - pow(y2, 2);
	double d = pow(r1, 2) - pow(c, 2) / (pow(a, 2) + pow(b, 2));
	if (d < 0)
		return 0;
	double m = sqrt(d / (pow(a, 2) + pow(b, 2)));
	double square_common = 4 * pow(m, 2) * (pow(a, 2) + pow(b, 2));
	double o1 = acos((2 * pow(r1, 2) - square_common) / (2 * pow(r1, 2)));
	double o2 = acos((2 * pow(r2, 2) - square_common) / (2 * pow(r2, 2)));

	double res = o1 * pow(r1, 2) / 2 + o2 * pow(r2, 2) / 2;
	res -= sqrt(square_common) * sqrt(pow(x2, 2) + pow(y2, 2)) / 2;
	return res;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cout << setprecision(32) << solve() << "\n";
}
