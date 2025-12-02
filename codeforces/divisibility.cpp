#include <bits/stdc++.h>

#define int long long
#define double long double

using namespace std;

int ceil(int a, int b)
{
	if (a >= 0)
		return (a + b - 1) / b;
	return a / b;
}

int floor(int a, int b)
{
	if (a >= 0)
		return a / b;

	return -ceil(-a, b);
}

void solve()
{
	int a, b, k;
	cin >> k >> a >> b;
	a = ceil(a, k);
	b = floor(b, k);
	cout << max(b - a + 1, 0ll) << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
