#include <bits/stdc++.h>

using namespace std;

#define int long long
struct Line {
	mutable int k, m, p;
	bool operator<(const Line &o) const
	{
		return k < o.k;
	}
	bool operator<(int x) const
	{
		return p < x;
	}
};
struct LineContainer : multiset<Line, less<> > {
	static const int inf = LLONG_MAX;
	int div(int a, int b)
	{
		return a / b - ((a ^ b) < 0 && a % b);
	}
	bool isect(iterator x, iterator y)
	{
		if (y == end())
			return x->p = inf, 0;
		if (x->k == y->k)
			x->p = x->m > y->m ? inf : -inf;
		else
			x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(int k, int m)
	{
		auto z = insert({ k, m, 0 }), y = z++, x = y;
		while (isect(y, z))
			z = erase(z);
		if (x != begin() && isect(--x, y))
			isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	int query(int x)
	{
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};

struct dat {
	int x, y, a;
};

void solve()
{
	int n;
	cin >> n;
	vector<dat> r(n);
	for (int i = 0; i < n; i++) {
		cin >> r[i].x >> r[i].y >> r[i].a;
	}
	r.push_back({ 0, 0, 0 });
	n = r.size();
	sort(r.begin(), r.end(), [](const dat &a, const dat &b) { return a.x < b.x; });

	vector<int> dp(n, 0);
	LineContainer lc;
	lc.add(-r[0].x, dp[0]);
	for (int i = 1; i < n; i++) {
		int t = lc.query(r[i].y);
		dp[i] = r[i].x * r[i].y - r[i].a + t;
		lc.add(-r[i].x, dp[i]);
	}
	int res = 0;
	for (int i = 1; i < n; i++)
		res = max(res, dp[i]);
	cout << res << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
