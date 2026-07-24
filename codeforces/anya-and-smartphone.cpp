#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

void solve()
{
	int n, m, k;
	cin >> n >> m >> k;
	vector<int> a(n);
	map<int, int> idxs;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		a[i]--;
		idxs[a[i]] = i;
	}

	int res = 0;
	while (m--) {
		int b;
		cin >> b;
		b--;

		int i = idxs[b];
		res += i / k + 1;
		if (i == 0)
			continue;
		int c = a[i - 1];
		a[i - 1] = b;
		idxs[b] = i - 1;
		a[i] = c;
		idxs[c] = i;
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
