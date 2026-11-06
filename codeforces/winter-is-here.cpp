#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

int add(int x, int y)
{
	x += y;
	if (x >= MOD)
		x -= MOD;
	return x;
}
int sub(int x, int y)
{
	x -= y;
	if (x < 0)
		x += MOD;
	return x;
}
int powmod(int x, int e)
{
	int r = 1;
	while (e) {
		if (e & 1)
			r = r * x % MOD;
		x = x * x % MOD;
		e >>= 1;
	}
	return r;
}
int inverse(int x)
{
	return powmod(x, MOD - 2);
}

void solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];

	int M = 0;
	for (int i = 0; i < n; i++)
		M = max(M, a[i]);

	vector<int> cnt(M + 1, 0);
	for (int i = 0; i < n; i++) {
		int x = a[i];
		for (int i = 1; i * i <= x; i++) {
			if (x % i != 0)
				continue;
			int j = x / i;
			cnt[i] = add(cnt[i], 1);
			if (j != i)
				cnt[j] = add(cnt[j], 1);
		}
	}
	vector<int> dp(M + 1, 0);
	int res = 0;
	for (int g = M; g >= 2; g--) {
		if (cnt[g] == 0)
			continue;
		dp[g] = cnt[g] * powmod(2, cnt[g] - 1) % MOD;
		for (int x = 2 * g; x <= M; x += g) {
			dp[g] = sub(dp[g], dp[x]);
		}
		res = add(res, g * dp[g] % MOD);
	}
	cout << res << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
