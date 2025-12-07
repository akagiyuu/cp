#include <bits/stdc++.h>

using namespace std;
const int MOD = 998244353;

struct mint {
	int x;
	mint(int x)
		: x(x)
	{
	}
	mint()
	{
	}
};

inline mint operator+(mint a, mint b)
{
	a.x += b.x;
	return a.x < MOD ? a.x : a.x - MOD;
}
inline mint operator-(mint a, mint b)
{
	a.x -= b.x;
	return a.x < 0 ? a.x + MOD : a.x;
}
inline mint operator*(mint a, mint b)
{
	return (long long)a.x * (long long)b.x % MOD;
}
mint powmod(mint a, int b)
{
	mint res = 1;
	while (b) {
		if (b & 1)
			res = res * a;
		a = a * a;
		b >>= 1;
	}
	return res;
}
inline mint operator/(mint a, mint b)
{
	return a * powmod(b, MOD - 2);
}

void solve()
{
	int n;
	cin >> n;
	vector<mint> p(n);
	for (int i = 0; i < n; i++) {
		cin >> p[i].x;
		p[i] = p[i] / 100;
	}
	mint res = 0;
	mint cur = 1;
	for (int i = 0; i < n; i++) {
		res = res + cur;
		cur = cur * p[i];
	}
	for (int i = 0; i < n; i++) {
		res = res / p[i];
	}
	cout << res.x << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
