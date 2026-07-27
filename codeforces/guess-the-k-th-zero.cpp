#include <bits/stdc++.h>
#include <cassert>

using namespace std;

#define int long long

const int MOD = 1000000007;
int ops = 0;

int zero_cnt(int l, int r)
{
	if (l > r)
		return 0;
	ops++;
	assert(ops <= 20);
	cout << "? " << l << " " << r << endl;
	int s;
	cin >> s;
	return r - l + 1 - s;
}

void solve()
{
	int n, t;
	cin >> n >> t;

	int k;
	cin >> k;
	int cnt = zero_cnt(1, n);
	int l = 1, r = n;
	while (l < r) {
		int mid = (l + r) / 2;
		int cur = zero_cnt(l, mid);
		if (k <= cur) {
			r = mid;
			cnt = cur;
		} else {
			k -= cur;
			l = mid + 1;
			cnt = cnt - cur;
		}
	}
	cout << "! " << l << endl;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
