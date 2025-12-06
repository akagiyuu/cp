#include <bits/stdc++.h>

#define int long long
#define double long double

using namespace std;

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
int mul(int a, int b)
{
	return (int)((__int128)a * b % MOD);
}
int powmod(int a, int b)
{
	int res = 1;
	while (b) {
		if (b & 1)
			res = mul(res, a);
		a = mul(a, a);
		b >>= 1;
	}
	return res;
}
int inv(int a)
{
	return powmod((a % MOD + MOD) % MOD, MOD - 2);
}

vector<int> nxt;
vector<int> acoef;
vector<int> bcoef;
vector<int> vis;

int dp(int start, int S, int pk, int pr, vector<int> &cache)
{
	if (cache[start] != -1)
		return cache[start];

	int u = start;
	vector<int> path;
	while (true) {
		if (cache[u] != -1) {
			// known, unwind path
			for (int idx = (int)path.size() - 1; idx >= 0; --idx) {
				int node = path[idx];
				cache[node] = add(mul(acoef[node], cache[nxt[node]]), bcoef[node]);
				vis[node] = 2;
			}
			return cache[start];
		}
		if (vis[u] == 0) {
			vis[u] = 1;
			path.push_back(u);
			int v = nxt[u];
			if (v == 0 || v == S) {
				for (int idx = (int)path.size() - 1; idx >= 0; --idx) {
					int node = path[idx];
					cache[node] = add(mul(acoef[node], cache[nxt[node]]), bcoef[node]);
					vis[node] = 2;
				}
				return cache[start];
			}
			u = v;
			continue;
		} else if (vis[u] == 1) {
			int pos = -1;
			for (int i = 0; i < (int)path.size(); ++i) if (path[i] == u) { pos = i; break; }
			int k = (int)path.size() - pos;
			vector<int> cyc;
			for (int i = pos; i < (int)path.size(); ++i) cyc.push_back(path[i]);
			int A = 1;
			for (int idx = 0; idx < k; ++idx) {
				int node = cyc[idx];
				A = mul(A, acoef[node]);
			}
			int B = 0;
			int pref = 1;
			for (int idx = 0; idx < k; ++idx) {
				int node = cyc[idx];
				B = add(B, mul(pref, bcoef[node]));
				pref = mul(pref, acoef[node]);
			}
			int denom = sub(1, A);
			int val = 0;
			if (denom != 0) val = mul(B, inv(denom));
			for (int t = 0; t < k; ++t) {
				int node = cyc[t];
				cache[node] = -2; // temporary mark
			}
			cache[cyc[0]] = val;
			for (int t = k - 1; t >= 1; --t) {
				int node = cyc[t];
				int nextnode = (t == k - 1) ? cyc[0] : cyc[t + 1];
				cache[node] = add(mul(acoef[node], cache[nextnode]), bcoef[node]);
			}
			for (int t = pos - 1; t >= 0; --t) {
				int node = path[t];
				cache[node] = add(mul(acoef[node], cache[nxt[node]]), bcoef[node]);
				vis[node] = 2;
			}
			for (int node : cyc) vis[node] = 2;
			return cache[start];
		} else {
			for (int idx = (int)path.size() - 1; idx >= 0; --idx) {
				int node = path[idx];
				cache[node] = add(mul(acoef[node], cache[nxt[node]]), bcoef[node]);
				vis[node] = 2;
			}
			return cache[start];
		}
	}
}

void solve()
{
	int pk_raw, pr_raw, b, x, y;
	cin >> pk_raw >> pr_raw >> b >> x >> y;

	int pk = mul(pk_raw % MOD, inv(b % MOD));
	int pr = mul(pr_raw % MOD, inv(b % MOD));
	int sum = add(pk, pr);
	if (sum == 0) {
		cout << 0 << "\n";
		return;
	}
	int p = mul(pk, inv(sum));
	int q = mul(pr, inv(sum));

	int S = x + y;
	int n = S + 1;
	if (S == 0) {
		cout << 0 << "\n";
		return;
	}

	nxt.assign(n, -1);
	acoef.assign(n, 0);
	bcoef.assign(n, 0);
	for (int i = 1; i <= S - 1; ++i) {
		if (i <= S / 2) {
			nxt[i] = 2 * i;
			acoef[i] = p;
			bcoef[i] = 0;
		} else {
			nxt[i] = 2 * i - S;
			acoef[i] = q;
			bcoef[i] = p;
		}
	}

	vector<int> cache(n, -1);
	cache[0] = 0;
	cache[S] = 1;
	vis.assign(n, 0);
	vis[0] = vis[S] = 2;

	cout << dp(x, S, pk, pr, cache) << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		solve();
}
