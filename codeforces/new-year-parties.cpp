#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

void solve()
{
	int n;
	cin >> n;

	vector<bool> has_person(n + 1, false);
	vector<int> cnt(n + 1, 0);
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		has_person[x] = true;
		cnt[x]++;
	}
	int m = 0;
	for (int i = 0; i <= n;) {
		if (has_person[i]) {
			m++;
			i += 3;
		} else {
			i++;
		}
	}

	int M = 0;
	for (int i = n + 1; i >= 0; i--) {
		if (i + 1 <= n && cnt[i + 1] > 0) {
			cnt[i + 1]--;
			M++;
			continue;
		}
		if (i <= n && cnt[i] > 0) {
			cnt[i]--;
			M++;
			continue;
		}
		if (i - 1 >= 0 && cnt[i - 1] > 0) {
			cnt[i - 1]--;
			M++;
			continue;
		}
	}
	cout << m << " " << M << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
