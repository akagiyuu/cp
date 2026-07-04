#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;
const int N = 1e6;

int add(int a, int b)
{
	a += b;
	return a >= MOD ? a - MOD : a;
}
int sub(int a, int b)
{
	a -= b;
	return a < 0 ? a + MOD : a;
}
int mul(int a, int b)
{
	return a * b % MOD;
}
int powmod(int a, int b)
{
	int res = 1;
	while (b) {
		if (b & 1) {
			res = mul(res, a);
		}

		a = mul(a, a);
		b >>= 1;
	}
	return res;
}
int inv(int a)
{
	return powmod(a, MOD - 2);
}

int fact[N], ifact[N];

void build()
{
	fact[0] = 1;
	for (int i = 1; i < N; i++) {
		fact[i] = mul(fact[i - 1], i);
	}

	ifact[N - 1] = inv(fact[N - 1]);
	for (int i = N - 2; i >= 0; i--) {
		ifact[i] = mul(ifact[i + 1], i + 1);
	}
}

int C(int n, int k)
{
	if (k < 0 || k > n)
		return 0;
	return mul(fact[n], mul(ifact[k], ifact[n - k]));
}
int P(int n, int k)
{
	if (k < 0 || k > n)
		return 0;
	return mul(fact[n], ifact[n - k]);
}

void solve()
{
	int n, m, k;
	cin >> n >> m >> k;
	int res = 0;
	int cnt = n * (n - 1) / 2;
	cnt %= MOD;
	int s = 0;
	for (int i = 0; i < m; i++) {
		int a, b, f;
		cin >> a >> b >> f;
		s = add(s, f);
	}
	for (int i = 1; i <= k; i++) {
		int cur = mul(C(k, i), powmod(sub(cnt, 1), sub(k, i)));
		int tmp = i * (i - 1) / 2;
		tmp %= MOD;
		tmp = mul(tmp, m % MOD);
		cur = mul(cur, add(mul(i, s), tmp));
		res = add(res, cur);
	}
	res = mul(res, inv(powmod(cnt, k)));
	cout << res << "\n";
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
