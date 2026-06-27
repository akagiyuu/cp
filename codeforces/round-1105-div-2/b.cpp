#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 998244353;

int powmod(int a, int b)
{
	int res = 1;
	while (b) {
		if (b & 1) {
			res = res * a % MOD;
		}
		a = a * a % MOD;
		b >>= 1;
	}
	return res;
}

void solve()
{
	int n, m, r, c;
	cin >> n >> m >> r >> c;

	int p = (n - r) * (c - 1) % (MOD - 1) + (m - c) * (r - 1) % (MOD - 1);
	p %= MOD - 1;
	p = (p + r * c % (MOD - 1)) % (MOD - 1);
	p = (p + MOD - 2) % (MOD - 1);
	int res = powmod(2, p);
	cout << res << "\n";
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
