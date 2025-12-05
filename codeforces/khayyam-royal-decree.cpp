#include <bits/stdc++.h>

#define int long long
#define pi pair<int, int>
#define fi first
#define se second

using namespace std;

const int N = 1e6;
const int MOD = 998244353;

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

int powmod(int a, int b)
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
	return powmod(a, MOD - 2);
}

int fact[N], ifact[N];

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

int C(int n, int k)
{
	if (k < 0 || n < k)
		return 0;
	return fact[n] * ifact[k] % MOD * ifact[n - k] % MOD;
}

int calc(int i, pi cur, int cnt, const vector<pi> &a)
{
	int k = a.size();
	int res = add(2 * cur.fi % MOD, cur.se) * cnt % MOD;
	if (i == k - 1) {
		// cout << cur.fi << " " << cur.se << " " << cnt << "\n";
		return res;
	}

	for (int j = i + 1; j < k; j++) {
		if (a[i].fi < a[j].fi || a[i].se < a[j].se)
			continue;
		int x = a[i].fi - a[j].fi;
		int y = a[i].se - a[j].se;
		pi next = {
			add(cur.fi, x % MOD) * 2 % MOD,
			add(cur.se, y % MOD) * 2 % MOD,
		};
		cout << i << " " << j << " " << a[i].fi << " " << a[j].se << " " << x << " " << y << "\n";
		int next_cnt = cnt * C(x + y, x) % MOD;
		res = add(res, calc(j, next, next_cnt, a));
	}
	return res;
}

void solve()
{
	int n, m, k;
	cin >> n >> m >> k;

	vector<pi> a(k);
	for (int i = 0; i < k; i++) {
		cin >> a[i].fi >> a[i].se;
	}
	a.push_back({ n, m });
	a.push_back({ 0, 0 });
	sort(a.begin(), a.end(), [](const pi &a, const pi &b) { return b < a; });

	int res = calc(0, { 0, 0 }, 1, a);
	res = res * inv(2) % MOD;
	// res = res * inv(C(m + n, n)) % MOD;

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
