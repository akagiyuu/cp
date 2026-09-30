#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

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

typedef complex<int> P;
int cross(const P &a, const P &b)
{
	return imag(conj(a) * b);
}
int dot(const P &a, const P &b)
{
	return real(conj(a) * b);
}
int half(const P &a)
{
	return a.imag() > 0 || (a.imag() == 0 && a.real() >= 0);
}

void solve()
{
	P h, g;
	int x, y;
	cin >> x >> y;
	h = P(x, y);
	cin >> x >> y;
	g = P(x, y) - h;

	int n;
	cin >> n;
	vector<P> a(n);
	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		a[i] = P(x, y) - h;
	}
	if (n <= 1) {
		cout << 0 << '\n';
		return;
	}
	a.push_back(g);
	n = a.size();

	sort(a.begin(), a.end(), [](const P &a, const P &b) {
		if (half(a) != half(b))
			return half(a) > half(b);
		return cross(a, b) > 0;
	});

	int s = 0;
	for (; s < n; s++)
		if (a[s] == g)
			break;
	vector<P> tmp(n);
	for (int i = 0; i < n; i++) {
		tmp[i] = a[(i + s) % n];
	}
	a = tmp;
	// for (auto x : a)
	// 	cout << x << '\n';

	int res = 0;
	vector<vector<int> > dp(n, vector<int>(n, 0));
	for (int j = 1; j < n; j++)
		dp[j][0] = cross(a[0], a[j]) > 0;
	for (int i = 2; i < n; i++) {
		for (int j = 1; j < i; j++) {
			if (cross(a[j], a[i]) <= 0)
				continue;
			for (int k = 0; k < j; k++) {
				if (cross(a[j] - a[k], a[i] - a[k]) <= 0)
					continue;
				dp[i][j] = add(dp[i][j], dp[j][k]);
			}
			// cout << a[i] << ' ' << a[j] << ' ' << dp[i][j] << '\n';
			if (cross(a[i], a[0]) <= 0 || cross(a[i] - a[j], a[0] - a[j]) <= 0)
				continue;
			res = add(res, dp[i][j]);
		}
	}
	cout << res << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
