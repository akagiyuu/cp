#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;
const int N = 26;

bool solve()
{
	int n, k;
	cin >> n >> k;
	string a, b;
	cin >> a >> b;
	array<int, N> cnt_a, cnt_b;
	fill(cnt_a.begin(), cnt_a.end(), 0);
	fill(cnt_b.begin(), cnt_b.end(), 0);
	for (int i = 0; i < n; i++) {
		cnt_a[a[i] - 'a']++;
		cnt_b[b[i] - 'a']++;
	}
	for (int i = N - 1; i >= 0; i--) {
		int diff = cnt_b[i] - cnt_a[i];
		if (i == 0 && diff != 0)
			return false;
		if (diff % k != 0)
			return false;
		if (diff < 0)
			return false;
		cnt_a[i] += diff;
		if (i > 0)
			cnt_a[i - 1] -= diff;
	}
	return true;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--) {
		if (solve())
			cout << "Yes\n";
		else
			cout << "No\n";
	}
}
