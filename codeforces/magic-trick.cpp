#include <bits/stdc++.h>

using namespace std;

#define int long long
#define double long double

const int MOD = 1000000007;
const int N = 1e3 + 7;

double cache[N][N];

void build()
{
	for (int i = 0; i < N; i++) {
		cache[i][0] = 1;
		for (int j = 1; j <= i; j++) {
			cache[i][j] = cache[i - 1][j] + cache[i - 1][j - 1];
		}
	}
}

double C(int n, int k)
{
	if (k < 0 || k > n)
		return 0;
	if (n < N)
		return cache[n][k];
	if (n - k < k)
		k = n - k;
	double res = 1;
	for (int i = 1; i <= k; i++) {
		res *= (double)(n + 1 - i) / (double)i;
	}
	return res;
}

void solve()
{
	int n, m;
	cin >> n >> m;

	double res = 0;
	for (int f = 1; f <= m; f++) {
		double p = C(m, f) * C((n - 1) * m, n - f) / C(n * m, n);
		res += p * f * f;
	}
	res /= n;

	cout << fixed << setprecision(6) << res << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();
	solve();
}
