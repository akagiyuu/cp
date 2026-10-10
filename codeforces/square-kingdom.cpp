#include <bits/stdc++.h>

using namespace std;

#define int long long

void solve()
{
	int n, k, a, b;
	cin >> n >> k >> a >> b;
	auto f = [&](__int128 x) {
		__int128 res = 0;
		for (__int128 t = 1; t < min((__int128)n, (__int128)5e6); t++) {
			__int128 cur = x - 2 * b * t;
			if (t % 2 == 1)
				cur -= a * t;
			cur /= (2 * a * t);
			cur -= t / 2;
			if (cur <= 0)
				continue;
			cur = min(cur, n - t);
			res += cur;
		}
		return res;
	};
	__int128 l = 0, r = 1e20;
	while (l < r) {
		int mid = (r - l) / 2 + l;
		if (f(mid) >= k)
			r = mid;
		else
			l = mid + 1;
	}
	int x = l, y = a;
	int g = gcd(x, y);
	x /= g;
	y /= g;
	cout << x << ' ' << y << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
