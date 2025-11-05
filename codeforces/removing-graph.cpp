#include <algorithm>
#include <bits/stdc++.h>

#define int long long

using namespace std;

struct DSU {
	int n;
	vector<int> parent;
	vector<int> size;

	int sccCount;

	void init(int n)
	{
		this->n = n;
		parent.resize(n);
		size.resize(n);
		reset();
	}

	void reset()
	{
		sccCount = n;
		for (int i = 0; i < n; i++)
			parent[i] = i;
		for (int i = 0; i < n; i++)
			size[i] = 1;
	}

	int update(int a)
	{
		if (parent[a] == a)
			return a;
		return parent[a] = update(parent[a]);
	}

	void join(int a, int b)
	{
		a = update(a);
		b = update(b);
		if (size[b] > size[a])
			swap(a, b);
		if (a == b)
			return;

		size[a] += size[b];

		parent[b] = a;
		sccCount--;
	}
};

void solve()
{
	int n, l, r, u, v;
	cin >> n >> l >> r;
	DSU s;
	s.init(n);
	for (int i = 0; i < n; i++) {
		cin >> u >> v;
		s.join(u - 1, v - 1);
	}

	vector<int> a;
	for (int i = 0; i < n; i++) {
		if (s.parent[i] == i)
			a.push_back(s.size[s.update(i)]);
	}

	int m = l + r;

	vector<int> g_cycle(m);
	for (int i = 0; i < l; i++) {
		g_cycle[i] = 0;
	}
	for (int i = l; i < m; i++) {
		g_cycle[i] = i / l;
	}

	int xr = 0;
	for (auto x : a) {
		if (x < l + r)
			xr ^= g_cycle[x];
	}
	if (xr != 0)
		cout << "Alice\n";
	else
		cout << "Bob\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
