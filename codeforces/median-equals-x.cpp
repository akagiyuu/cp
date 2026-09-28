#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 998244353;
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
	int n, x;
	cin >> n >> x;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	sort(a.begin(), a.end());
	map<int, int> cnt;
	for (int i = 0; i < n; i++)
		cnt[a[i]]++;
	auto cnt_left = [&a](int x) { return lower_bound(a.begin(), a.end(), x) - a.begin(); };
	auto cnt_right = [&a, &n](int x) { return n - (upper_bound(a.begin(), a.end(), x) - a.begin()); };
	set<int> visited;
	int res = 0;
	for (int i = 0; i < n; i++) {
		if (a[i] != x || visited.find(x) != visited.end())
			continue;
		int s1 = cnt_left(x);
		int s2 = cnt[x];
		int s3 = n - s1 - s2;
		int tmp = s2;
		for (int j = 0; j < tmp; j++) {
			int cur = sub(C(s1 + s3 + s2, s3 + s2 - 1), C(s1 + s3, s3 - 1));
			res = add(res, cur);
			s1++;
			s2--;
		}
		visited.insert(x);
	}
	for (int i = 0; i < n; i++) {
		int l = a[i];
		int r = 2 * x - l;
		if (l >= r || visited.find(l) != visited.end())
			continue;
		visited.insert(l);
		if (cnt[r] == 0)
			continue;
		int s1 = cnt_left(l);
		int s2 = cnt[l];
		int s3 = cnt[r];
		int s4 = cnt_right(r);
		// cout << "TEST\n";
		// cout << l << ' ' << r << '\n';
		// cout << s1 << ' ' << s2 << ' ' << s3 << ' ' << s4 << '\n';
		for (int j = 0; j < s2; j++) {
			res = add(res, sub(C(s1 + s4 + s3, s4 + s3 - 1), C(s1 + s4, s4 - 1)));
			s1++;
		}
	}
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
