#include <bits/stdc++.h>

#define int long long

using namespace std;

vector<int> cur;

void print(int i, int cur_sum, int n, int k)
{
	if (i == n) {
		int s = 0;

		// for (int i = 0; i < n; i++) {
		// 	cout << cur[i] << " ";
		// }
		for (int i = 0; i < n; i++) {
			s += cur[i];
			cout << s / (i + 1) << " ";
		}
		cout << "\n";
		return;
	}

	for (int j = 1; j <= k; j++) {
		if ((cur_sum + j) % (i + 1) != 0)
			continue;
		cur[i] = j;
		print(i + 1, cur_sum + j, n, k);
	}
}

void solve()
{
	int n, k;
	cin >> n >> k;
	cur.resize(n);
	print(0, 0, n, k);
	cout << "\n";
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
