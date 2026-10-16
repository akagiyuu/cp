#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 998244353;
const int N = 99;

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
	int scale = inverse(100);
	vector<int> p(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> p[i];
		p[i] = p[i] * scale % MOD;
	}
	vector<int> inv(N + 1, 0);
	for (int j = 0; j <= N; j++) {
		int p = j * scale % MOD;
		inv[j] = inverse(p) % MOD;
	}

	vector<int> f(n + 1, 0);
	f[1] = inverse(sub(1, p[1]));
	vector<int> prefix(N + 1, 0);
	for (int j = 0; j <= N; j++) {
		prefix[j] = f[1] * inv[j] % MOD;
	}
	for (int i = 2; i <= n; i++) {
		f[i] = prefix[p[i] * 100 % MOD];
		f[i] = f[i] * powmod(p[i], i + 1) % MOD;
		f[i] = add(f[i], 1);
		f[i] = f[i] * inverse(sub(1, p[i])) % MOD;
		for (int j = 0; j <= N; j++) {
			prefix[j] = add(prefix[j], f[i] * powmod(inv[j], i) % MOD);
		}
	}
	int res = 0;
	for (int i = 1; i <= n; i++) {
		res = add(res, f[i]);
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
