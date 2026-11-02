#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

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
	string s;
	cin >> s;

	vector<int> a(n), b(n + 1, 0), c(n + 1, 0);

	int inv3 = inverse(3);
	auto f = [&](char c, int i) {
		int res = (s[i] == c || s[i] == '?');
		if (s[i] == '?')
			res = res * inv3 % MOD;
		return res;
	};

	for (int i = 0; i < n; i++) {
		a[i] = f('a', i);
		b[i] = f('b', i);
		c[i] = f('c', i);
	}
	for (int i = n - 2; i >= 0; i--)
		c[i] = add(c[i + 1], c[i]);
	for (int i = 0; i < n; i++)
		b[i] = b[i] * c[i + 1] % MOD;
	for (int i = n - 2; i >= 0; i--)
		b[i] = add(b[i + 1], b[i]);

	int res = 0;
	for (int i = 0; i < n; i++) {
		res = add(res, a[i] * b[i + 1] % MOD);
	}

	int qcnt = 0;
	for (int i = 0; i < n; i++)
		qcnt += s[i] == '?';
	res = res * powmod(3, qcnt) % MOD;

	cout << res << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
