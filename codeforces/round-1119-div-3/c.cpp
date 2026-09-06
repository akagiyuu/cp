#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

void solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];

	int first = -1, last = -1, bestL = -1, bestR = -1, bestLen = 0;
	for (int i = 0; i < n; i++) {
		if (a[i] != 0) {
			if (first == -1)
				first = i;
			last = i;
		}
		if (a[i] == 1) {
			if (first != -1) {
				int len = last - first + 1;
				if (len > bestLen) {
					bestLen = len;
					bestL = first;
					bestR = last;
				}
			}
			first = i;
			last = i;
		}
	}
	if (first != -1) {
		int len = last - first + 1;
		if (len > bestLen) {
			bestLen = len;
			bestL = first;
			bestR = last;
		}
	}
	for (int i = 0; i < n; i++) {
		if (a[i] == -1)
			a[i] = 0;
	}
	if (bestL != -1) {
		a[bestL] = 1;
		a[bestR] = 1;
	}
	for (auto x : a)
		cout << x << ' ';
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
