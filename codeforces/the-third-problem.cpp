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

int solve()
{
	int n;
	cin >> n;
	vector<int> a(n), inv_a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		inv_a[a[i]] = i;
	}
	if (n <= 3)
		return 1;

	int l = inv_a[0], r = inv_a[1];
	if (l > r)
		swap(l, r);
	int fixed_cnt = 2;
	int offset = 0;
	int res = 1;
	for (int x = 2; x < n; x++) {
		int i = inv_a[x];
		if (i < l || i > r) {
			l = min(i, l);
			r = max(r, i);
			fixed_cnt++;
			continue;
		}
		int cnt = r - l + 1 - fixed_cnt;
		cnt -= offset;
		offset++;
		res = res * cnt % MOD;
	}
	return res;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		cout << solve() << "\n";
}
