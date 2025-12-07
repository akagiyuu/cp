#include <bits/stdc++.h>

#define int long long

using namespace std;

const int MOD = 1000000007;

struct ntype {
	int x;
	ntype(int _n)
		: x(_n % MOD)
	{
	}
	ntype()
		: x(0)
	{
	}
};

ntype operator+(ntype a, ntype b)
{
	int res = a.x + b.x;
	return ntype(res >= MOD ? res - MOD : res);
}
ntype operator-(ntype a, ntype b)
{
	int res = a.x - b.x;
	if (res < 0)
		res += MOD;
	return ntype(res);
}
ntype operator*(ntype a, ntype b)
{
	return ntype((a.x * 1ll * b.x) % MOD);
}
ntype powmod(ntype a, int b)
{
	ntype res = 1;
	while (b) {
		if (b & 1)
			res = res * a;
		a = a * a;
		b >>= 1;
	}
	return res;
}

void solve()
{
	int n;
	cin >> n;
	vector<ntype> a(n, ntype(0));
	for (int i = 0; i < n - 1; i++) {
		long long tmp;
		cin >> tmp;
		a[i] = ntype(tmp % MOD);
	}
	a[n - 1] = ntype(0);

	// triangular cnt: cnt[i][j] j = 0 .. n-1-i
	vector<vector<ntype> > cnt(n);
	for (int i = 0; i < n; ++i)
		cnt[i].assign(n - i, ntype(0));

	cnt[n - 1][0] = ntype(1);
	for (int i = n - 2; i >= 0; --i) {
		int max_dist = n - 1 - i;
		for (int j = 1; j <= max_dist; ++j) {
			cnt[i][j] = cnt[i + 1][j - 1] * a[i];
		}
		cnt[i][0] = ntype(1);
	}

	// nodes at depth i
	vector<ntype> nodes(n, ntype(0));
	nodes[0] = ntype(1);
	for (int i = 1; i < n; ++i)
		nodes[i] = nodes[i - 1] * a[i - 1];

	int maxK = 2 * n - 2;
	vector<ntype> fk(maxK + 1, ntype(0));

	// 1) ancestor-descendant pairs
	for (int k = 1; k <= n - 1; ++k) {
		ntype sum = ntype(0);
		for (int i = 0; i <= n - 1 - k; ++i) {
			sum = sum + (nodes[i] * cnt[i][k]);
		}
		fk[k] = fk[k] + sum;
	}

	// prepare conv arrays: we keep only next_c (which represents c_{d+1})
	vector<ntype> next_c(1, ntype(1)); // c_{n-1} = {1}

	ntype inv2 = powmod(ntype(2), MOD - 2);

	for (int d = n - 2; d >= 0; --d) {
		int L = n - (d + 1); // length of b_d (cnt[d+1]) is L (indices 0..L-1)
		int csize = 2 * L - 1; // c_d indices 0..(2L-2)
		vector<ntype> cur_c(csize, ntype(0));

		ntype a_next = a[d + 1];
		ntype a_next_sq = a_next * a_next;

		// fill cur_c using recurrence c_d[s] = 2*b_d[s] + a_{d+1}^2 * c_{d+1}[s-2], c_d[0]=1
		for (int s = 0; s < csize; ++s) {
			if (s == 0) {
				cur_c[0] = ntype(1);
			} else {
				ntype bd_s = ntype(0);
				if (s <= L - 1)
					bd_s = cnt[d + 1][s]; // b_d[s]
				ntype term = ntype(0);
				if (s - 2 >= 0 && s - 2 < (int)next_c.size())
					term = next_c[s - 2];
				cur_c[s] = (ntype(2) * bd_s) + (a_next_sq * term);
			}
		}

		// contribution from depth d:
		// nodes[d] * C(a[d],2) * conv_d[s] where path length k -> s = k-2
		ntype choose2 = a[d] * (a[d] - ntype(1));
		choose2 = choose2 * inv2; // divide by 2
		if (choose2.x != 0) {
			for (int s = 0; s < csize; ++s) {
				int k = s + 2;
				if (k > maxK)
					continue;
				fk[k] = fk[k] + (nodes[d] * choose2 * cur_c[s]);
			}
		}

		next_c.swap(cur_c); // cur becomes next for the previous depth
	}

	// print f1..f_{2n-2}
	for (int k = 1; k <= maxK; ++k) {
		cout << fk[k].x << (k < maxK ? ' ' : '\n');
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
	return 0;
}
