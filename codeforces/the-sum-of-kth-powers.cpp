#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;
const int N = 1e6 + 7;

int fact[N];

int normalize(int x)
{
	x %= MOD;
	if (x < 0)
		x += MOD;
	return x;
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
	fact[0] = 1;
	for (int i = 1; i < N; i++)
		fact[i] = fact[i - 1] * i % MOD;
}

int interpolate(int x, const vector<int> &ys)
{
	int n = ys.size() - 1;
	vector<int> scale(n + 1), xs(n + 1);
	for (int i = 0; i <= n; i++) {
		scale[i] = inverse(fact[i] * fact[n - i] % MOD);
		if ((n - i) % 2 == 1)
			scale[i] = sub(0, scale[i]);
		xs[i] = normalize(x - i);
	}
	vector<int> px(n + 1), sx(n + 1);
	px[0] = xs[0];
	for (int i = 1; i <= n; i++)
		px[i] = px[i - 1] * xs[i] % MOD;
	sx[n] = xs[n];
	for (int i = n - 1; i >= 0; i--)
		sx[i] = sx[i + 1] * xs[i] % MOD;
	int res = 0;
	for (int i = 0; i <= n; i++) {
		int cur = ys[i];
		if (i > 0)
			cur = cur * px[i - 1] % MOD;
		if (i < n)
			cur = cur * sx[i + 1] % MOD;
		cur = cur * scale[i] % MOD;
		res = add(res, cur);
	}
	return res;
}

void solve()
{
	int n, k;
	cin >> n >> k;
	vector<int> ys(k + 2);
	ys[0] = 0;
	for (int i = 1; i <= k + 1; i++) {
		ys[i] = add(ys[i - 1], powmod(i, k));
	}
	cout << interpolate(n, ys) << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();
	solve();
}
