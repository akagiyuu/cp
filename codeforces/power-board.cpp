#include <bits/stdc++.h>
#include <cassert>

#define int long long
#define pi pair<int, int>
#define fi first
#define se second

using namespace std;

const int N = 1e6 + 5;

int lp[N];
void build()
{
	vector<int> pr;
	for (int i = 2; i < N; i++) {
		if (lp[i] == 0) {
			pr.push_back(i);
			lp[i] = i;
		}
		for (int j = 0; i * pr[j] < N; j++) {
			lp[i * pr[j]] = pr[j];
			if (lp[i] == pr[j])
				break;
		}
	}
}

vector<pi> factorize(int n)
{
	vector<pi> res;
	while (n > 1) {
		int cur = lp[n];
		int cnt = 0;
		while (n % cur == 0) {
			n /= cur;
			cnt++;
		}
		res.push_back({ cur, cnt });
	}
	return res;
}

void solve()
{
	int n, m;
	cin >> n >> m;
	int res = 1;
	vector<int> multiple(n + 1, -1);
	vector<int> should_check(n + 1, true);
	for (int i = 2; i <= n; i++) {
		if (!should_check[i])
			continue;
		int cnt = 1;
		int cur = i;
		while (cur <= n) {
			should_check[cur] = false;
			cur *= i;
			cnt++;
		}
		multiple[i] = cnt - 1;
	}

	int max_k = __lg(n);
	int cnt = 0;
	vector<int> visited(max_k * m + 1, false);
	vector<int> dp(max_k + 1);
	for (int j = 1; j <= max_k; j++) {
		for (int k = 1; k <= m; k++) {
			int cur = j * k;
			if (visited[cur])
				continue;
			visited[cur] = true;
			cnt++;
		}
		dp[j] = cnt;
	}
	for (int i = 2; i <= n; i++) {
		if (multiple[i] == -1)
			continue;
		int x = multiple[i];
		res += dp[x];
	}
	cout << res << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();
	solve();
}
