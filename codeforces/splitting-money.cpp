#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

int cal_fee(int y, int x, int f)
{
	int diff = y - x;
	int m = x + f;
	int res = (diff + m - 1) / m * f;
	return res;
}

void solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	int x, f;
	cin >> x >> f;
	int res = 0;
	for (auto y : a) {
		res += cal_fee(y, x, f);
	}
	cout << res << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
