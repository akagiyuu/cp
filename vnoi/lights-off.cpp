#include <bits/stdc++.h>

#define int long long

using namespace std;
const int NBIT = 16;
const int N = 1 << NBIT;

int g[N];
set<int> gs[N];
set<int> gn[N];

int grundy(int mask)
{
	if (g[mask] != -1)
		return g[mask];

	for (int i = 0; i < NBIT; i++) {
		if (!((mask >> i) & 1))
			continue;
		int m = mask & ~(1 << i);
		gs[mask].insert(grundy(m));
		gn[mask].insert(m);
		for (int j = 0; j < i; j++) {
			gs[mask].insert(grundy(m ^ (1 << j)));
			gn[mask].insert(m ^ (1 << j));
		}
		for (int j = 0; j < i; j++) {
			for (int k = j + 1; k < i; k++) {
				gs[mask].insert(grundy(m ^ (1 << j) ^ (1 << k)));
				gn[mask].insert(m ^ (1 << j) ^ (1 << k));
			}
		}
	}

	int mex = 0;
	while (gs[mask].find(mex) != gs[mask].end())
		mex++;

	g[mask] = mex;
	return mex;
}

void print_mask(int mask)
{
	for (int i = 0; i < NBIT; i++) {
		int cur = (mask >> i) & 1;
		cout << cur << " ";
	}
	cout << "\n";
}

int calc(int n)
{
	return (n << 1) + ((__builtin_popcountll(n) & 1) ^ 1);
}

void build()
{
	for (int i = 0; i < N; i++) {
		g[i] = -1;
	}
	g[0] = 0;
	// int v[] = { 1, 2, 3, 4 };
	// int test = 0;
	// for (auto x : v) {
	// 	test ^= grundy(1 << (x - 1));
	// }
	// cout << test << "\n";
	for (int i = 0; i < NBIT; i++) {
		int test = calc(i);

		if (test != grundy(1 << (i)))
			cout << test << " " << grundy(1 << i) << "\n";
		// print_mask(grundy(mask));
	}
}

void solve()
{
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
