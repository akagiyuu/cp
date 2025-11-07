#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 5e6 + 1;
const int MOD = 1e9 + 7;

int fact[N], ifact[N];

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

int inv(int a)
{
	return binpow(a, MOD - 2);
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
	ifact[N - 1] = inv(fact[N - 1]);
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

void solve()
{
	int n, q;
	cin >> n >> q;

	vector<int> poly(3 * n + 1);
	for (int i = 1; i < 3; i++) {
		int cur = 0;
		for (int j = 0; j <= n; j++) {
			cur = add(cur, nCk(3 * j, i));
		}
		poly[i] = cur;
	}
	for (int i = 3; i <= 3 * n; i++) {
		int cur = nCk(3 * (n + 1), i + 1);
		cur = sub(cur, poly[i - 2]);
		cur = sub(cur, 3 * poly[i - 1] % MOD);
		cur = inv(3) * cur % MOD;
		poly[i] = cur;
	}

	int x;
	while (q--) {
		cin >> x;
		cout << poly[x] << "\n";
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();
	solve();
}
