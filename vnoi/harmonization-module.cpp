#include <bits/stdc++.h>

#define int long long
#define double long double

using namespace std;

const int MAX = 1e9;

pair<int, int> solve(int a)
{
	if (a < 0) {
		return { abs(a), abs(a) };
	}

	int rt = floor(sqrtl((double)a));
	while (rt * rt <= a + 2)
		rt++;
	int diff = rt * rt - a;
	int x = -1;
	int y = -1;
	for (int i = 2; i * i <= diff; i++) {
		if (diff % i == 0) {
			y = i - 1;
			x = diff / i;
		}
	}
	if (x == -1) {
		y = diff - 1;
		x = 1;
	}
	if (y > MAX || x > MAX || x < 1 || y < 1) {
		return { -1, -1 };
	}

	return { x, y };
}

signed main()
{
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--) {
		int a;
		cin >> a;
		auto res = solve(a);
		if (res.first == -1)
			cout << -1 << "\n";
		else {
			int b = res.first * res.second + res.first + a;
			int rt = (int)sqrtl(b);
			assert(rt * rt == b);
			cout << res.first << " " << res.second << "\n";
		}
	}
}
