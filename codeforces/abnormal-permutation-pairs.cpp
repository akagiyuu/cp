#include <bits/stdc++.h>

using namespace std;

#define int long long

int MOD;

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

void solve()
{
	int N;
	cin >> N >> MOD;
	if (N <= 3) {
		cout << 0 << '\n';
		return;
	}

	vector<int> fact(N + 1);
	fact[0] = 1;
	for (int i = 1; i <= N; i++)
		fact[i] = fact[i - 1] * i % MOD;

	vector<vector<int> > C(N + 1, vector<int>(N + 2));
	for (int n = 0; n <= N; n++) {
		C[n][0] = 1;
		for (int k = 1; k <= n; k++)
			C[n][k] = add(C[n - 1][k], C[n - 1][k - 1]);
	}

	vector<vector<int> > cnt(N);
	vector<int> pcnt = { 1 };
	auto get = [&](int l, int r) {
		if (l == 0)
			return pcnt[r];
		return sub(pcnt[r], pcnt[l - 1]);
	};
	cnt[1] = { 1 };
	for (int n = 2; n < N; n++) {
		int m = n * (n - 1) / 2 + 1;

		cnt[n].resize(m);
		for (int i = 0; i < m; i++) {
			int prev_m = (n - 1) * (n - 2) / 2;
			int l = max(0ll, i - (n - 1));
			int r = min(i, prev_m);
			if (l > r)
				break;

			cnt[n][i] = get(l, r);
		}

		pcnt.resize(m);
		pcnt[0] = cnt[n][0];
		for (int i = 1; i < m; i++)
			pcnt[i] = add(pcnt[i - 1], cnt[n][i]);
	}

	vector<int> f(N + 1);
	for (int n = 4; n <= N; n++) {
		f[n] = n * f[n - 1] % MOD;
		int m = (n - 1) * (n - 2) / 2 + 1;

		vector<int> scnt = cnt[n - 1];
		for (int i = m - 2; i >= 0; i--)
			scnt[i] = add(scnt[i], scnt[i + 1]);

		for (int dist = 2; dist <= n; dist++) {
			int cur = 0;
			for (int k = 0; k < m - dist; k++)
				cur = add(cur, cnt[n - 1][k] * scnt[k + dist] % MOD);

			f[n] = add(f[n], cur * (n + 1 - dist) % MOD);
		}
	}

	cout << f[N] << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
