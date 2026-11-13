#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 998244353;
const int M = 17;

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

void solve()
{
	int n;
	string s;
	cin >> n >> s;

	int cnt = 0;
	for (int i = 0; i < n; i++)
		cnt += s[i] == '?';

	vector<vector<int> > dp(M + 1, vector<int>(1ll << M, 0));

	for (int i = 0; i < n; i++) {
		int mask = 0;
		int free = 0;
		int cur_cnt = 0;
		for (int j = 0; i - j >= 0 && i + j < n; j++) {
			int l = i - j;
			int r = i + j;

			if (s[l] == '?' && s[r] == '?')
				free++;
			else if (s[l] == '?')
				mask |= 1ll << (s[r] - 'a');
			else if (s[r] == '?')
				mask |= 1ll << (s[l] - 'a');
			else if (s[l] != s[r])
				break;
			cur_cnt += s[l] == '?';
			if (l != r)
				cur_cnt += s[r] == '?';

			for (int s = 1; s <= M; s++)
				dp[s][mask] = add(dp[s][mask], powmod(s, free + cnt - cur_cnt));
		}
	}
	for (int i = 0; i < n - 1; i++) {
		int mask = 0;
		int free = 0;
		int cur_cnt = 0;
		for (int j = 0; i - j >= 0 && i + 1 + j < n; j++) {
			int l = i - j;
			int r = i + 1 + j;

			if (s[l] == '?' && s[r] == '?')
				free++;
			else if (s[l] == '?')
				mask |= 1ll << (s[r] - 'a');
			else if (s[r] == '?')
				mask |= 1ll << (s[l] - 'a');
			else if (s[l] != s[r])
				break;
			cur_cnt += s[l] == '?';
			cur_cnt += s[r] == '?';

			for (int s = 1; s <= M; s++)
				dp[s][mask] = add(dp[s][mask], powmod(s, free + cnt - cur_cnt));
		}
	}
	for (int s = 1; s <= M; s++) {
		for (int k = 0; k < M; k++)
			for (int mask = 0; mask < (1 << M); mask++)
				if (mask & (1 << k))
					dp[s][mask] = add(dp[s][mask], dp[s][mask ^ (1 << k)]);
	}

	int q;
	cin >> q;
	string t;
	while (q--) {
		cin >> t;
		int mask = 0;
		for (auto c : t)
			mask |= 1ll << (c - 'a');

		cout << dp[__builtin_popcountll(mask)][mask] << '\n';
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
