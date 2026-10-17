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
	string a, b;
	cin >> a >> b;
	vector<int> f(n, 0);
	f[n - 1] = 1;
	for (int i = 2; i <= n; i++) {
		f[n - i] = add(n, (i - 1) * f[n - i + 1] % MOD);
		f[n - i] = f[n - i] * inverse(n - i + 1) % MOD;
	}
	int d = 0;
	for (int i = 0; i < n; i++) {
		d += a[i] != b[i];
	}
	int res = 0;
	for (int i = 0; i < d; i++)
		res = add(res, f[i]);
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
