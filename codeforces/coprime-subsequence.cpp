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

	vector<int> mu(M + 1, 0);
	mu[1] = 1;
	for (int i = 1; i <= M; i++)
		for (int j = 2 * i; j <= M; j += i)
			mu[j] = sub(mu[j], mu[i]);

	vector<int> cnt(M + 1, 0);
	for (int i = 0; i < n; i++)
		cnt[a[i]]++;

	int res = 0;
	for (int d = 1; d <= M; d++) {
		int c = 0;
		for (int x = d; x <= M; x += d)
			c += cnt[x];
		res = add(res, mu[d] * sub(powmod(2, c), 1) % MOD);
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
