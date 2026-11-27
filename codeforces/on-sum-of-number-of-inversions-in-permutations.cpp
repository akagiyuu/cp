#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

#define int long long

template <class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const int MOD = 1000000007;
const int N = 1e6 + 7;

int fact[N], ifact[N];

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
	ifact[N - 1] = inverse(fact[N - 1]);
	for (int i = N - 2; i >= 0; i--)
		ifact[i] = ifact[i + 1] * (i + 1) % MOD;
}
int C(int n, int k)
{
	if (k < 0 || k > n)
		return 0;
	return fact[n] * ifact[n - k] % MOD * ifact[k] % MOD;
}

void solve()
{
	int n;
	cin >> n;
	vector<int> p(n + 1);
	for (int i = 1; i <= n; i++)
		cin >> p[i];

	vector<int> cnt_inv(n + 1, 0);
	for (int i = 2; i <= n; i++)
		cnt_inv[i] = add(i * (i - 1) / 2 % MOD * fact[i - 1] % MOD, i * cnt_inv[i - 1] % MOD);

	ordered_set<int> s(p.begin() + 1, p.end());
	int res = 0;
	int sum = 0;
	for (int i = 1; i <= n; i++) {
		int c = s.order_of_key(p[i]);

		int v = c * sum % MOD;
		v = add(v, c * (c - 1) / 2 % MOD);
		v = v * fact[n - i] % MOD;
		v = add(v, c * cnt_inv[n - i] % MOD);

		res = add(res, v);

		s.erase(p[i]);
		sum = add(sum, s.order_of_key(p[i]));
	}
	res = add(res, sum);

	cout << res << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();
	solve();
}
