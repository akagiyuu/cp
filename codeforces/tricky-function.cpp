#include <bits/stdc++.h>

using namespace std;

#define int long long

const int INF = 1e18;

int n;
vector<int> a;

int dc(int l, int r)
{
	if (l >= r)
		return INF;
	if (l + 1 == r)
		return INF;
	if (l + 2 == r) {
		int i = l, j = l + 1;
		int x = i - j;
		int y = a[i] - a[j];
		return x * x + y * y;
	}
	int mid = (l + r) / 2;
	int d = INF;
	d = min(d, dc(l, mid));
	d = min(d, dc(mid, r));
	int dx = (int)floor(sqrt(d));
	for (int i = l; i < mid; i++) {
		for (int j = mid; j < r && j < dx + i; j++) {
			int x = i - j;
			int y = a[i] - a[j];
			int cur = x * x + y * y;
			if (cur < d) {
				d = cur;
				dx = (int)floor(sqrt(d));
			}
		}
	}
	return d;
}

void solve()
{
	cin >> n;
	a.resize(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	for (int i = 1; i < n; i++)
		a[i] += a[i - 1];
	cout << dc(0, n) << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
