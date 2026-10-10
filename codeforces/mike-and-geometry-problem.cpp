#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

template <class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long
#define pi pair<int, int>
#define fi first
#define se second

const int MOD = 1000000007;
const int N = 4e5 + 7;

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
	int n, k;
	cin >> n >> k;
	vector<pi> a(n);
	ordered_set<int> s;
	for (int i = 0; i < n; i++) {
		cin >> a[i].fi >> a[i].se;
		a[i].se++;
		s.insert(a[i].fi);
		s.insert(a[i].se);
	}
	vector<int> xs(s.begin(), s.end());
	int m = xs.size();
	for (int i = 0; i < n; i++) {
		a[i] = {
			s.order_of_key(a[i].fi),
			s.order_of_key(a[i].se),
		};
	}
	auto sz = [&](int l, int r) { return (xs[r] - xs[l]) % MOD; };

	vector<int> cnt(m);
	for (int i = 0; i < n; i++) {
		cnt[a[i].fi]++;
		cnt[a[i].se]--;
	}
	for (int i = 1; i < m; i++)
		cnt[i] += cnt[i - 1];

	int res = 0;
	for (int i = 0; i < m - 1; i++) {
		res = add(res, sz(i, i + 1) * C(cnt[i], k) % MOD);
	}

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
