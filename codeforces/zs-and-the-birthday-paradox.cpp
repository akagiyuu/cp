#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1e6 + 3;
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
	e %= MOD - 1;
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
	int n, k;
	cin >> n >> k;
	if (n <= __lg(k) + 7 && (1ll << n) < k) {
		cout << 1 << ' ' << 1 << '\n';
		return;
	}
	int T = powmod(2, n);

	int x = 0;
	int e = 1, p = 2;
	for (; p < k; e++, p *= 2) {
		x += (k + p - 1) / p;
	}
	x += (n - e + 1);
	x = powmod(2, x);
	x = inverse(x);

	int a = 0;
	if (k <= MOD) {
		a = 1;
		for (int i = 1; i <= k; i++) {
			a = a * (T - k + i) % MOD;
		}
	}
	a = a * x % MOD;
	int b = powmod(T, k) * x % MOD;
	a = sub(b, a);
	cout << a << ' ' << b << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
