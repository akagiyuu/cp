#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

double solve()
{
	double m, n;
	cin >> m >> n;
	double res = m;
	for (ll i = 0; i < m; i++) {
		res -= pow((double)i / m, n);
	}
	return res;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cout << setprecision(10) << solve() << "\n";
}
