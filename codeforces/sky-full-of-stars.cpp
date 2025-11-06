#include <bits/stdc++.h>

#define int long long

using namespace std;
const int MOD = 998244353;
const int N = 1e6 + 1;


int add(int a, int b)
{
	int res = a + b;
	if (res >= MOD)
		res -= MOD;
	return res;
}

int sub(int a, int b)
{
	int res = a - b;
	if (res < 0)
		res += MOD;
	return res;
}

int binpow(int a, int b)
{
	b %= MOD - 1;
	int res = 1;
	while (b) {
		if (b & 1)
			res = (res * a) % MOD;
		a = (a * a) % MOD;
		b >>= 1;
	}
	return res;
}

int ifact[N], fact[N];

void build()
{
	fact[0] = 1;
	for (int i = 1; i < N; i++) {
		fact[i] = fact[i - 1] * i % MOD;
	}
	ifact[N - 1] = binpow(fact[N - 1], MOD - 2);
	for (int i = N - 2; i >= 0; i--) {
		ifact[i] = ifact[i + 1] * (i + 1) % MOD;
	}
}

int nCk(int n, int k)
{
	if (k < 0 || n < k)
		return 0;

	return fact[n] * ifact[k] % MOD * ifact[n - k] % MOD;
}

int solve()
{
	int n;
	cin >> n;

	int res = binpow(3, n);
	res = sub(res, 3);
	res = binpow(res, n);
	res = 2 * sub(binpow(3, n * n), res) % MOD;
	for (int i = 1; i <= n; i++) {
		int cur = binpow(3, n - i);
		cur = sub(cur, 1);
		cur = binpow(cur, n);
		cur = sub(binpow(3, n * (n - i)), cur);
		cur = nCk(n, i) * cur % MOD;
		cur = 3 * cur % MOD;
		if (i % 2 == 0)
			res = add(res, cur);
		else
			res = sub(res, cur);
		// for (int j = i; j <= n; j++) {
		// 	int cur = nCk(n, i) * nCk(n, j) % MOD;
		// 	cur = cur * binpow(3, (n - i) * (n - j) + 1);
		// 	cur = 2 * cur % MOD;
		// 	if ((i + j) % 2 == 0) {
		// 		res = sub(res, cur);
		// 	} else {
		// 		res = add(res, cur);
		// }
		// }
	}
	// for (int i = 1; i <= n; i++) {
	// 	int cur = nCk(n, i) * nCk(n, i) % MOD;
	// 	cur = cur * binpow(3, (n - i) * (n - i) + 1);
	// 	res = sub(res, cur);
	// }
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
