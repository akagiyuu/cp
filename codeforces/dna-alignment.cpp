#include <bits/stdc++.h>
#include <cassert>

using namespace std;

#define int long long

const int MOD = 1000000007;
const int N = 4;

int powmod(int a, int b)
{
	int res = 1;
	while (b) {
		if (b & 1) {
			res = res * a % MOD;
		}
		a = a * a % MOD;
		b >>= 1;
	}
	return res;
}

int encode(char c)
{
	switch (c) {
	case 'A':
		return 0;
	case 'C':
		return 1;
	case 'G':
		return 2;
	case 'T':
		return 3;
	default:
		assert(false);
	}
}

void solve()
{
	int n;
	cin >> n;
	string s;
	cin >> s;

	array<int, N> cnt = { 0, 0, 0, 0 };
	for (int i = 0; i < n; i++) {
		cnt[encode(s[i])]++;
	}
	int max_cnt = 0;
	for (int i = 0; i < N; i++) {
		max_cnt = max(max_cnt, cnt[i]);
	}
	int m = 0;
	for (int i = 0; i < N; i++) {
		if (cnt[i] == max_cnt)
			m++;
	}

	cout << powmod(m, n) << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
