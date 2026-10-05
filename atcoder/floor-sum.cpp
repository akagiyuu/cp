#include <bits/stdc++.h>

using namespace std;

#define int long long

int floor_sum(int a, int b, int c, int n)
{
	if (a == 0)
		return b / c * (n + 1);
	if (a >= c || b >= c)
		return a / c * n * (n + 1) / 2 + b / c * (n + 1) + floor_sum(a % c, b % c, c, n);
	int m = (a * n + b) / c;
	return n * m - floor_sum(c, c - b - 1, a, m - 1);
}

void solve()
{
	int n, a, b, c;
	cin >> n >> c >> a >> b;
	cout << floor_sum(a, b, c, n - 1) << '\n';
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
