#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;
const int N = 107;

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

void solve()
{
	int n, i, j, x, y;
	cin >> n >> i >> j >> x >> y;
	if (x > y) {
		tie(i, j) = make_pair(n - j + 1, n - i + 1);
		swap(x, y);
	}

	int res = 0;
	if (y < n) {
		int s1 = x - 1;
		int s2 = y - x - 1;
		int s3 = n - y - 1;
		for (int k = i + 1; k < j; k++) {
			int c1 = i - 1;
			int c2 = k - i - 1;
			int c3 = j - k - 1;
			int c4 = n - j;
			int t = s3 - c3;

			int cur = C(s3, c3) % MOD;
			cur = cur * C(s2, c2 - t) % MOD;
			cur = cur * C(s1, c1) % MOD;
			cur = cur * C(s1 - c1 + s2 - (c2 - t), c4) % MOD;
			res = add(res, cur);
		}
		for (int k = j + 1; k < n; k++) {
			int c1 = i - 1;
			int c2 = j - i - 1;
			int c3 = k - j - 1;

			int cur = C(s1, c1);
			cur = cur * C(s2, c2) % MOD;
			cur = cur * C(s3, c3) % MOD;
			res = add(res, cur);
		}
	} else if (j < n && j > 1) {
		int s1 = x - 1;
		int s2 = y - x - 1;
		int c1 = i - 1;
		int c2 = j - i - 1;

		res = C(s1, c1);
		res = res * C(s2, c2) % MOD;
	}
	cout << res << '\n';
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
