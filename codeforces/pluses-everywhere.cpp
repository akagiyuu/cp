#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

struct mint {
	int x;
	mint(int x)
		: x(x)
	{
	}
	mint()
		: x(0)
	{
	}
};
static inline mint operator+(mint a, mint b)
{
	a.x += b.x;
	if (a.x >= MOD)
		a.x -= MOD;
	return a;
}
static inline mint operator-(mint a, mint b)
{
	a.x -= b.x;
	if (a.x < 0)
		a.x += MOD;
	return a;
}
static inline mint operator*(mint a, mint b)
{
	return (long long)a.x * (long long)b.x % MOD;
}

void solve()
{
	int n, k;
	cin >> n >> k;
	string s;
	cin >> s;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; i++) {
		a[i] = s[n - i] - '0';
	}
	vector<vector<mint> > dp(n + 1, vector<mint>(k + 1));

	mint pw = 1;
	for (int i = 1; i <= n; i++, pw = pw * 10) {
		dp[i][0] = a[i] * pw + dp[i - 1][0];
	}
	for (int j = 1; j <= k; j++) {
		for (int i = j + 1; i <= n; i++) {
			mint cur = 0;
			for (int k = i; k <= n; k++) {
				cur = cur * 10 + a[k];
				dp[i][j] = dp[i][j] + cur;
				if (k + 1 <= n) {
					dp[i][j] = dp[i][j] + dp[k + 1][j - 1];
				}
			}
		}
	}
	for (int j = 0; j <= k; j++) {
		for (int i = 0; i <= n; i++) {
			cout << dp[i][j].x << " ";
		}
		cout << "\n";
	}
	cout << dp[n][k].x << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
