#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;
const int N = 65;

int C[N][N];

void build()
{
	for (int n = 0; n < N; n++) {
		C[n][0] = 1;
		for (int k = 1; k < n; k++) {
			C[n][k] = C[n - 1][k - 1] + C[n - 1][k];
		}
		C[n][n] = 1;
	}
}

int nCk(int n, int k)
{
	if (n < 0 || k < 0 || n < k)
		return 0;
	return C[n][k];
}

void solve()
{
	int n, k;
	cin >> n >> k;
	int cnt = 0;
	// for (int i = 1; i <= n; i++) {
	// 	int cur = __lg(i) + __builtin_popcount(i);
	// 	cnt += cur > k;
	// }
	for (int p = 0; p < __lg(n); p++) {
		for (int i = 0; i <= min(k - p - 1, p); i++) {
			cnt += nCk(p, i);
		}
	}
	cnt = n - cnt;
	if (__lg(n) + 1 <= k)
		cnt--;
	cout << cnt << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();

	int t;
	cin >> t;
	while (t--)
		solve();
}
