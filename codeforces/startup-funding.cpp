#include <bits/stdc++.h>

using namespace std;

#define int long long
#define double long double

struct MinST {
	int n;
	vector<vector<signed> > st;
	vector<int> lg;

	MinST(const vector<signed> &a)
	{
		n = a.size();
		lg.assign(n + 1, 0);

		for (int i = 2; i <= n; i++)
			lg[i] = lg[i / 2] + 1;

		st.assign(lg[n] + 1, vector<signed>(n));
		st[0] = a;

		for (int k = 1; k < (int)st.size(); k++) {
			for (int i = 0; i + (1LL << k) <= n; i++) {
				st[k][i] = min(st[k - 1][i], st[k - 1][i + (1LL << (k - 1))]);
			}
		}
	}

	int get(int l, int r)
	{
		int k = lg[r - l + 1];
		return min(st[k][l], st[k][r - (1LL << k) + 1]);
	}
};
struct MaxST {
	int n;
	vector<vector<signed> > st;
	vector<int> lg;

	MaxST(const vector<signed> &a)
	{
		n = a.size();
		lg.assign(n + 1, 0);

		for (int i = 2; i <= n; i++)
			lg[i] = lg[i / 2] + 1;

		st.assign(lg[n] + 1, vector<signed>(n));
		st[0] = a;

		for (int k = 1; k < (int)st.size(); k++) {
			for (int i = 0; i + (1LL << k) <= n; i++) {
				st[k][i] = max(st[k - 1][i], st[k - 1][i + (1LL << (k - 1))]);
			}
		}
	}

	int get(int l, int r)
	{
		int k = lg[r - l + 1];
		return max(st[k][l], st[k][r - (1LL << k) + 1]);
	}
};

double C_inv(int n, int k)
{
	if (k < 0 || k > n)
		return 0;
	if (n - k < k)
		k = n - k;
	double res = 1;
	for (int i = 1; i <= k; i++)
		res *= (double)i / (double)(n - k + i);
	return res;
}

void solve()
{
	int n, k;
	cin >> n >> k;
	vector<signed> v(n), c(n);
	for (int i = 0; i < n; i++) {
		cin >> v[i];
		v[i] *= 100;
	}
	MaxST tv(v);
	for (int i = 0; i < n; i++)
		cin >> c[i];
	MinST tc(c);

	vector<int> g(n);
	for (int l = 0; l < n; l++) {
		int a = l, b = n - 1;
		while (a < b) {
			int mid = (a + b) / 2;

			int x = tv.get(l, mid);
			int y = tc.get(l, mid);

			if (x < y)
				a = mid + 1;
			else
				b = mid;
		}

		g[l] = min(tv.get(l, a), tc.get(l, a));

		if (a > l) {
			int x = min(tv.get(l, a - 1), tc.get(l, a - 1));
			g[l] = max(g[l], x);
		}
	}
	sort(g.begin(), g.end());
	double p = (double)k / n;
	double res = 0;
	for (int i = 0; i <= n - k; i++) {
		res += p * g[i];
		if (i < n - k)
			p *= (double)(n - i - k) / (n - i - 1);
	}
	cout << fixed << setprecision(10) << res << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
