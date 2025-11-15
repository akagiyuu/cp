#include <bits/stdc++.h>

#define int long long

using namespace std;

const int MOD = 998244353;

vector<int> cur;

void print(int i, int n, int k)
{
	if (i == n) {
		for (int i = 0; i < n; i++) {
			cout << cur[i] << " ";
		}
		cout << "\n";
		cout << cur[0] << " ";
		for (int i = 1; i < n; i++) {
			cout << (i + 1) * cur[i] - i * cur[i - 1] << " ";
		}
		cout << "\n";
		cout << "\n";
		return;
	}

	int left = 1;
	int right = k;
	if (i > 0) {
		left = (1 + i * cur[i - 1] + i) / (i + 1);
		right = (k + i * cur[i - 1]) / (i + 1);
	}

	for (int j = left; j <= right; j++) {
		cur[i] = j;
		print(i + 1, n, k);
	}
}

int ceil(int x, int y)
{
	return (x + y - 1) / y;
}

int add(int a, int b)
{
	int res = a + b;
	return res > MOD ? res - MOD : res;
}

int sub(int a, int b)
{
	int res = a - b;
	return res < 0 ? res + MOD : res;
}

void solve()
{
	int n, k;
	cin >> n >> k;
	vector<int> dp(k + 1, 1);
	n = min(n, k);
	dp[0] = 0;
	for (int i = 2; i <= n; i++) {
		vector<int> ndp(k + 1, 0);
		for (int y = 1; y <= k; y++) {
			int left = max(ceil(i * y - k, i - 1), 0ll);
			int right = min((i * y - 1) / (i - 1), k);
			for (int x = left; x <= right; x++) {
                ndp[y] = add(ndp[y], dp[x]);
			}
		}
		dp = ndp;
	}
	int res = 0;
	for (int i = 1; i <= k; i++) {
        res = add(res, dp[i]);
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
