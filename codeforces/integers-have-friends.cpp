#include <bits/stdc++.h>

using namespace std;

#define int long long

struct Segtree {
	int n;
	vector<int> t;

	Segtree(const vector<int> &a)
	{
		n = (int)a.size();
		t.assign(2 * n, 0);
		for (int i = 0; i < n; ++i)
			t[n + i] = a[i];
		for (int i = n - 1; i > 0; --i)
			t[i] = gcd(t[i << 1], t[i << 1 | 1]);
	}

	void update(int p, int v)
	{
		p += n;
		t[p] = v;
		for (p >>= 1; p > 0; p >>= 1)
			t[p] = gcd(t[p << 1], t[p << 1 | 1]);
	}

	int query(int l, int r)
	{
		if (l > r)
			return 0;
		l += n;
		r += n + 1;
		int resL = 0, resR = 0;
		while (l < r) {
			if (l & 1)
				resL = gcd(resL, t[l++]);
			if (r & 1)
				resR = gcd(t[--r], resR);
			l >>= 1;
			r >>= 1;
		}
		return gcd(resL, resR);
	}
};

void solve()
{
	int n, tmp;
	cin >> n;
	vector<int> a(n - 1);
	if (n == 1) {
		cin >> tmp;
		cout << 1 << "\n";
		return;
	}
	cin >> a[0];
	for (int i = 0; i < n - 1; i++) {
		cin >> tmp;
		a[i] = abs(a[i] - tmp);
		if (i < n - 2)
			a[i + 1] = tmp;
	}
	n--;
	Segtree s(a);
	int best = 1;
	int L = 0;
	for (int R = 0; R < n; ++R) {
		while (L <= R && s.query(L, R) == 1)
			++L;
		best = max(best, R - L + 1 + 1);
	}
	cout << best << "\n";
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
