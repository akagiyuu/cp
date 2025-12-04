#include <bits/stdc++.h>

#define int long long

using namespace std;

unordered_map<int, int> cache;

int cnt(int x, int n)
{
	if (x > n)
		return 0;
	if (cache.find(x) != cache.end())
		return cache[x];

	int res = 1 + cnt(x << 1, n);
	if (!(x & 1))
		res += cnt(x | 1, n);
	cache[x] = res;
	return res;
}

void solve()
{
	int n, k;
	cin >> n >> k;

	cache.clear();
	cache[n] = 1;

	int res = -1;
	int l = 1;
	int r = n;
	while (l <= r) {
		int mid = l + (r - l) / 2;
		if (cnt(mid, n) >= k) {
			res = mid;
			l = mid + 1;
		} else {
			r = mid - 1;
		}
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
