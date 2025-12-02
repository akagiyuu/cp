#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 1e6 + 1;
const int MOD = 998244353;

int fact[N], ifact[N];

int powmod(int a, int b)
{
	int res = 1;
	while (b) {
		if (b & 1)
			res = (res * a) % MOD;
		a = (a * a) % MOD;
		b >>= 1;
	}
	return res;
}

int add(int a, int b)
{
	int res = a + b;
	return res < MOD ? res : res - MOD;
}

int sub(int a, int b)
{
	int res = a - b;
	return res < 0 ? res + MOD : res;
}

void build()
{
	fact[0] = 1;
	for (int i = 1; i < N; i++) {
		fact[i] = fact[i - 1] * i % MOD;
	}
	ifact[N - 1] = powmod(fact[N - 1], MOD - 2);
	for (int i = N - 2; i >= 0; i--) {
		ifact[i] = ifact[i + 1] * (i + 1) % MOD;
	}
}

int C(int k, int n)
{
	if (k < 0 || k > n)
		return 0;
	return fact[n] * ifact[n - k] % MOD * ifact[k] % MOD;
}

int solve()
{
	int k, n;
	cin >> n >> k;
	if (k >= n)
		return 0;
	int res = C(k, n);
	int m = n - k;
	int cnt = 0;
	for (int i = 0; i <= m; i++) {
		int cur = C(i, m) * powmod(i, n) % MOD;
		if ((m - i) % 2 == 0)
			cnt = add(cnt, cur);
		else
			cnt = sub(cnt, cur);
	}
	res = res * cnt % MOD;
	if (k != 0)
		res = res * 2 % MOD;
	return res;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();
	cout << solve() << "\n";
}
