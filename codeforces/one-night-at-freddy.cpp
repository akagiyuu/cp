#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

void solve()
{
	int n, m, l;
	cin >> n >> m >> l;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	vector<int> ani(m, 0);
	int light_remain = n;
	for (int t = 1; t <= l; t++) {
		if (light_remain >= m) {
			ani[m - 1]++;
			for (int i = m - 1; i >= 1; i--) {
				if (ani[i] > ani[i - 1])
					swap(ani[i], ani[i - 1]);
				else
					break;
			}
		} else if (light_remain > 0) {
			while (m - 1 > light_remain) {
				ani.pop_back();
				m--;
			}
			ani[m - 1]++;
			for (int i = m - 1; i >= 1; i--) {
				if (ani[i] > ani[i - 1])
					swap(ani[i], ani[i - 1]);
				else
					break;
			}
		} else {
			ani[0]++;
		}
		if (light_remain > 0 && *lower_bound(a.begin(), a.end(), t) == t) {
			light_remain--;
			for (int i = 0; i < m - 1; i++)
				ani[i] = ani[i + 1];
			ani[m - 1] = 0;
		}
	}
	cout << ani[0] << '\n';
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
