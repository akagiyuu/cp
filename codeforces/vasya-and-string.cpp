#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

int solve()
{
	int n, k;
	cin >> n >> k;
	string s;
	cin >> s;

	int res = 0;
	int cnt = 1;
	int cur = s[0];
	for (int i = 1; i < n; i++) {
		if (s[i] == cur)
			cnt++;
		else {
			res = max(res, cnt);
			cnt = 1;
			cur = s[i];
		}
	}
	res = max(res, cnt);

	auto cal = [n, k, s](char c) {
		int res = 0;

		int cnt = 0;
		for (int i = 0; i < n; i++) {
			cnt += s[i] == c;
		}
		cnt = min(cnt, k);
		int i = 0;
		int j = 0;
		int cur = 0;
		while (j < n && cur < cnt) {
			cur += s[j] == c;
			j++;
		}
		while (j < n && s[j] != c)
			j++;
		j--;

		// cout << c << " -> " << cnt << "\n";
		res = max(res, j - i + 1);
		// cout << c << " -> " << i << " " << j << "\n";
		while (i <= j && j < n) {
			while (i < n && cur == cnt) {
				cur -= s[i] == c;
				i++;
			}
			if (cur == cnt)
				break;
			j++;
			while (j < n && cur < cnt) {
				cur += s[j] == c;
				j++;
			}
			while (j < n && s[j] != c)
				j++;
			j--;
			if (cur != cnt)
				break;
			if (i <= j && j < n) {
				// cout << c << " -> " << i << " " << j << "\n";
				res = max(res, j - i + 1);
			}
		}
		return res;
	};

	return max(res, max(cal('a'), cal('b')));
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cout << solve() << "\n";
}
