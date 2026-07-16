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
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		if (cnt >= k)
			break;
		if (s[i] == 'R') {
			cnt++;
			continue;
		}
		for (int j = 0; j < i; j++) {
			if (s[j] == 'R')
				continue;
			s[j] = 'R';
			cnt++;
			res++;
		}
		if (cnt < k) {
			s[i] = 'R';
			cnt++;
			res++;
		}
	}

	cnt = 0;
	for (int i = n - 1; i >= 0; i--) {
		if (cnt >= k)
			break;
		if (s[i] == 'L') {
			cnt++;
			continue;
		}
		for (int j = n - 1; j > i; j--) {
			if (s[j] == 'L')
				continue;
			s[j] = 'L';
			cnt++;
			res++;
		}
		if (cnt < k) {
			s[i] = 'L';
			cnt++;
			res++;
		}
	}

	cnt = 0;
	for (int i = 0; i < n; i++) {
		if (cnt >= k)
			break;
		if (s[i] == 'R') {
			cnt++;
			continue;
		}
		if (cnt < k)
			return -1;
	}

	cnt = 0;
	for (int i = n - 1; i >= 0; i--) {
		if (cnt >= k)
			break;
		if (s[i] == 'L') {
			cnt++;
			continue;
		}
		if (cnt < k)
			return -1;
	}

	return res;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		cout << solve() << "\n";
}
