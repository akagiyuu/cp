#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;
const int N = 1e5 + 7;

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
	vector<int> c(n + 1);
	for (int i = 1; i <= n; i++)
		cin >> c[i];

	vector<int> dp_len(n + 1);
	dp_len[0] = 0;
	for (int i = 1; i <= n; i++) {
		int j = i;
		int cnt = 0;
		for (; j >= 1; j--) {
			cnt += c[i] == c[j];
			if (cnt == k)
				break;
		}
		if (cnt == k) {
			dp_len[i] = dp_len[j - 1] + k;
		}
		dp_len[i] = max(dp_len[i], dp_len[i - 1]);
	}

	vector<int> dp_cnt(n + 1);
	dp_cnt[0] = 1;
	for (int i = 1; i <= n; i++) {
		int m = dp_len[i];
		int j = i;
		int cnt = 0;

		for (; j >= 1; j--) {
			cnt += c[i] == c[j];
			if (cnt == k)
				break;
		}
		if (cnt < k) {
			dp_cnt[i] = dp_cnt[i - 1];
			continue;
		}
		if (dp_len[j - 1] + k == m)
			dp_cnt[i] = add(dp_cnt[i], dp_cnt[j - 1] % MOD);

		j--;
		for (; j >= 1; j--) {
			if (c[i] == c[j]) {
				cnt++;
				if (dp_len[j - 1] + k == m) {
					int scale = k <= 2 ? 1 : C(cnt - 2, k - 2);
					dp_cnt[i] = add(dp_cnt[i], scale * dp_cnt[j - 1] % MOD);
				}
			}
			if (cnt == 2 * k - 1)
				break;
		}
		if (dp_len[i - 1] == m)
			dp_cnt[i] = add(dp_cnt[i], dp_cnt[i - 1]);
	}
	cout << dp_cnt[n] << '\n';
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
