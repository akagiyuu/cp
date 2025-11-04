#include <bits/stdc++.h>

using namespace std;

#define int long long
const int MOD = 1e9 + 7;
const int N = 1e5;

int binpow(int a, int b)
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

int fact[N], ifact[N];

void build()
{
	fact[0] = 1;
	for (int i = 1; i < N; i++) {
		fact[i] = i * fact[i - 1] % MOD;
	}
	ifact[N - 1] = binpow(fact[N - 1], MOD - 2);
	for (int i = N - 2; i >= 0; i--) {
		ifact[i] = ifact[i + 1] * (i + 1) % MOD;
	}
}

int nCk(int n, int k)
{
	return fact[n] * ifact[k] % MOD * ifact[n - k] % MOD;
}

int count(int n)
{
	int cnt = 0;
	for (int k = 0; k <= n; k++) {
		if (nCk(n, k) % 7 == 0)
			cnt++;
	}
	return cnt;
}

int solve()
{
	int n;
	cin >> n;
	n -= 6;
	if (n < 0)
		return 0;

	int q = n / 7;
	int r = n % 7;
	int res = 1;
	if (q % 2 == 0) {
		res = q / 2;
		res *= q + 1;
		res %= MOD;
	} else {
		res = (q + 1) / 2;
		res *= q;
		res %= MOD;
	}
	res *= (1 + 2 + 3 + 4 + 5 + 6);
	res %= MOD;
	for (int i = 0; i < r; i++) {
		res += (q + 1) * (6 - i) % MOD;
		res %= MOD;
	}
	return res;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	build();

	for (int i = 0; i < 30; i++) {
		for (int j = 0; j <= i; j++) {
			cout << nCk(i, j) % 7 << " ";
			if (j % 7 == 6)
				cout << " ";
		}
		cout << "\n";
	}

	// int t;
	// cin >> t;
	// while (t--)
	// 	cout << solve() << "\n";
}
