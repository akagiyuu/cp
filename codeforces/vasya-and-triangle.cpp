#include <bits/stdc++.h>
#include <cassert>

using namespace std;

#define int long long
#define pi pair<int, int>

vector<pi> solve()
{
	int n, m, k;
	cin >> n >> m >> k;
	if (2 * n * m % k != 0) {
		return {};
	}
	if (k % 2 == 0) {
		k /= 2;
		int a = n / gcd(n, k);
		int b = n * m / k / a;
		assert(a <= n);
		assert(b <= m);
		return { { 0, 0 }, { a, 0 }, { 0, b } };
	} else {
		int a = n / gcd(n, k);
		int b = n * m / k / a;
		if (a * 2 <= n)
			a *= 2;
		else if (b * 2 <= m)
			b *= 2;
		return { { 0, 0 }, { a, 0 }, { 0, b } };
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	auto res = solve();
	if (res.empty())
		cout << "NO\n";
	else {
		cout << "YES\n";
		for (int i = 0; i < 3; i++) {
			cout << res[i].first << ' ' << res[i].second << '\n';
		}
	}
}
