#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

void solve()
{
	string s;
	cin >> s;
	int n = s.size();

	vector<vector<bool> > is_palindrome(n, vector<bool>(n, false));
	for (int i = 0; i < n; i++) {
		is_palindrome[i][i] = true;
	}
	for (int i = 1; i < n; i++) {
		is_palindrome[i - 1][i] = s[i - 1] == s[i];
	}
	for (int len = 3; len <= n; len++) {
		for (int i = 0; i < n; i++) {
			int j = i + len - 1;
			if (j >= n)
				break;
			is_palindrome[i][j] = is_palindrome[i + 1][j - 1] && (s[i] == s[j]);
		}
	}

	vector<vector<int> > cnt(n, vector<int>(n, 0));
	for (int i = 0; i < n; i++) {
		cnt[i][i]++;
	}
	for (int len = 2; len <= n; len++) {
		for (int i = 0; i < n; i++) {
			int j = i + len - 1;
			if (j >= n)
				break;
			cnt[i][j] += cnt[i + 1][j] + cnt[i][j - 1] - cnt[i + 1][j - 1] + is_palindrome[i][j];
		}
	}
	// for (int i = 0; i < n; i++) {
	// 	for (int j = 0; j < n; j++) {
	// 		cout << cnt[i][j] << " ";
	// 	}
	// 	cout << "\n";
	// }

	int q;
	cin >> q;
	while (q--) {
		int l, r;
		cin >> l >> r;
		l--;
		r--;
		cout << cnt[l][r] << "\n";
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
