#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 107;
const int S = 1e5 + 7;

double C[N][N + 1];
int a[N];
double dp[N][S];
double p[N];

void build()
{
	for (int i = 0; i < N; i++) {
		C[i][0] = 1;
		for (int j = 1; j <= i; j++)
			C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
	}
}

void solve()
{
	int n, x;
	cin >> n >> x;

	for (int i = 1; i <= n; i++)
		cin >> a[i];
	int maxs = 0;
	for (int i = 1; i <= n; i++)
		maxs += a[i];
	dp[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int c = n; c >= 1; c--) {
			for (int s = maxs; s >= a[i]; s--) {
				dp[c][s] += dp[c - 1][s - a[i]];
			}
		}
	}
	for (int i = 1; i <= n; i++)
		p[i] = (double)(n + i) / (2.0L * i) * (double)x;

	double res = 0;
	for (int c = 1; c <= n; c++) {
		double cur = 0;
		for (int s = 0; s <= maxs; s++) {
			cur += dp[c][s] * min(p[c], (double)s / c);
		}
		cur /= C[n][c];
		res += cur;
	}
	cout << fixed << setprecision(9) << res << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();
	solve();
}
