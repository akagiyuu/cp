#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 998244353;
const int N = 1e5 + 7;

int f[N];

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
	f[1] = 0;
	for (int i = 2; i < N; i++) {
		f[i] = add(f[i - 1], 2 * inverse(i) % MOD);
	}
}

void solve()
{
	int n;
	cin >> n;
	int res = (n * (n - 1)) % MOD * inverse(4) % MOD;
	res = add(res, f[n]);
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
