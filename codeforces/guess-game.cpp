#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 998244353;

int add(int x, int y)
{
	x += y;
	if (x >= MOD)
		x -= MOD;
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

struct Node {
	int32_t child[2] = { -1, -1 };
	int32_t cnt = 0;
};

vector<Node> trie;

void insert(int x)
{
	int32_t v = 0;
	trie[v].cnt++;

	for (int bit = 30; bit >= 0; bit--) {
		int b = (x >> bit) & 1;

		int32_t nxt = trie[v].child[b];

		if (nxt == -1) {
			nxt = trie.size();
			trie[v].child[b] = nxt;
			trie.emplace_back();
		}

		v = nxt;
		trie[v].cnt++;
	}
}

int res;

void dfs(int32_t v, int depth, int ones)
{
	if (depth == 31) {
		int cnt = trie[v].cnt;
		res = add(res, cnt * cnt % MOD * (ones + 1) % MOD);
		return;
	}

	int32_t l = trie[v].child[0];
	int32_t r = trie[v].child[1];

	if (l != -1 && r != -1) {
		int c0 = trie[l].cnt;
		int c1 = trie[r].cnt;

		int ways = c0 * c1 % MOD;
		res = add(res, ways * (2 * ones + 3) % MOD);
	}

	if (l != -1)
		dfs(l, depth + 1, ones);

	if (r != -1)
		dfs(r, depth + 1, ones + 1);
}

void solve()
{
	int n;
	cin >> n;

	trie.clear();
	trie.emplace_back();
	trie.reserve(1 + 31 * n);

	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		insert(x);
	}

	res = 0;
	dfs(0, 0, 0);

	res = res * inverse(n * n % MOD) % MOD;
	cout << res << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int t;
	cin >> t;

	while (t--)
		solve();
}
