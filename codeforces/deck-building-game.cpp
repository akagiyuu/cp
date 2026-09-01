#include <bits/stdc++.h>

using namespace std;

#define int long long
#define MAX 1048576

const int MOD = 998244353;
const int NBIT = 17;
const int N = 1 << NBIT;

void walsh_transform(long long *ar, int n)
{
	if (!n)
		return;
	int m = n >> 1;
	walsh_transform(ar, m);
	walsh_transform(ar + m, m);
	for (int i = 0; i < m; i++) {
		long long x = ar[i], y = ar[i + m];
		ar[i] = x + y, ar[i + m] = x - y;
	}
}

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

int binpow(int a, int b)
{
	b %= MOD - 1;
	int res = 1;
	while (b) {
		if (b & 1)
			res = res * a % MOD;
		a = a * a % MOD;
		b >>= 1;
	}
	return res;
}

void solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	int f[N];
	fill(f, f + N, 0);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		f[a[i]]++;
	}

	walsh_transform(f, N);

	int res = 0;

	for (int t = 0; t < (1 << NBIT); t++) {
		int d = f[t];

		int x = (n + d) / 2;
		x %= MOD - 1;
		int y = (n - d) / 2;
		int cur = binpow(3, x);
		if (y & 1)
			res = sub(res, cur);
		else
			res = add(res, cur);
	}
	res = res * binpow(1 << NBIT, MOD - 2) % MOD;
	cout << res << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
