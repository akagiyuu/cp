#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 998244353;
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
	int g = 0;
	for (int i = 0; i < n; i++) {
		g += a[i] == 0;
	}
	int cnt = 0;
	for (int i = 0; i < g; i++) {
		cnt += a[i] == 0;
	}
	int res = 0;
	for (int i = g - 1; i >= cnt; i--) {
		int p = (g - i) * (g - i) % MOD;
		p = p * inverse(n * (n - 1) / 2 % MOD) % MOD;
		res = add(res, inverse(p));
	}
	cout << res << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		solve();
}
