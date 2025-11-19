#include <algorithm>
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int MOD = 1e9 + 7;
const int N = 1e6;

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

int fact[N], ifact[N];
void build()
{
	fact[0] = 1;
	for (int i = 1; i < N; i++) {
		fact[i] = fact[i - 1] * i % MOD;
	}

	ifact[N - 1] = powmod(fact[N - 1], MOD - 2);
	assert(ifact[N - 1] * fact[N - 1] % MOD == 1);
	for (int i = N - 2; i >= 0; i--) {
		ifact[i] = ifact[i + 1] * (i + 1) % MOD;
	}
}

int C(int n, int k)
{
	if (k < 0 || k > n)
		return 0;
	return fact[n] * ifact[k] % MOD * ifact[n - k] % MOD;
}

int count_way(const pair<int, int> &a, const pair<int, int> &b)
{
	int di = abs(a.first - b.first);
	int dj = abs(a.second - b.second);
	int dist = di + dj;
	return C(dist, di);
}

void solve()
{
	int h, w, n;
	cin >> h >> w >> n;
	vector<pair<int, int> > black_cells(n);
	for (int i = 0; i < n; i++) {
		cin >> black_cells[i].first >> black_cells[i].second;
	}
	black_cells.push_back({ 1, 1 });
	black_cells.push_back({ h, w });
	n = black_cells.size();
	sort(black_cells.begin(), black_cells.end());

	vector<int> cnt(n);
	cnt[n - 1] = MOD - 1;
	for (int i = n - 2; i >= 0; i--) {
		int cur = 0;
		for (int j = i + 1; j < n; j++) {
			if (black_cells[i].first > black_cells[j].first ||
			    black_cells[i].second > black_cells[j].second)
				continue;
			cur = sub(cur, count_way(black_cells[i], black_cells[j]) * cnt[j] % MOD);
		}
		cnt[i] = cur;
	}

	cout << cnt[0] << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();
	solve();
}
