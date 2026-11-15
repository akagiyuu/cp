#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 998244353;
const int N = 1e6 + 7;

int fact[N], ifact[N];

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

void build()
{
	fact[0] = 1;
	for (int i = 1; i < N; i++)
		fact[i] = fact[i - 1] * i % MOD;
	ifact[N - 1] = inverse(fact[N - 1]);
	for (int i = N - 2; i >= 0; i--)
		ifact[i] = ifact[i + 1] * (i + 1) % MOD;
}
int C(int n, int k)
{
	if (k < 0 || k > n)
		return 0;
	return fact[n] * ifact[n - k] % MOD * ifact[k] % MOD;
}

int calc(int n, int s, int a, int b)
{
	if (n == 0)
		return s == 0;

	int res = 0;
	for (int i = 0; i <= n; i++) {
		int cur = C(n, i) * C(s + (n - i) * (1 - a) - i * b - 1, n - 1) % MOD;
		if (i % 2 == 0)
			res = add(res, cur);
		else
			res = sub(res, cur);
	}
	return res;
}

void solve()
{
	int n, k;
	cin >> n >> k;

	int m = 2 * k;
	int q = n / m;
	int r = n % m;

	int res = q * (q + 1) / 2 * r + q * (q - 1) / 2 * (m - r);
	if (q == 0) {
		cout << res << ' ' << calc(k - 1, r - 2, 1, 2) << '\n';
		return;
	}

	int cnt = 0;
	for (int s : { r, r - 1, r - 1, r - 2 }) {
		if (s < 0)
			continue;
		cnt = add(cnt, calc(k - 1, s, 0, 2));
	}

	cout << res << ' ' << cnt << '\n';
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
