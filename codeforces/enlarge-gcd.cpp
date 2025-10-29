#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 2e7;
int lp[N];

void build()
{
	vector<int> pr;
	for (int i = 2; i < N; i++) {
		if (lp[i] == 0) {
			lp[i] = i;
			pr.push_back(i);
		}
		for (int j = 0; i * pr[j] <= N; j++) {
			lp[i * pr[j]] = pr[j];
			if (pr[j] == lp[i])
				break;
		}
	}
}

int solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	int g = a[0];
	for (int i = 1; i < n; i++) {
		g = gcd(g, a[i]);
	}
	for (int i = 0; i < n; i++) {
		a[i] /= g;
	}

	int x;
	unordered_map<int, int> cnt;
	for (int i = 0; i < n; i++) {
		x = a[i];
		while (x > 1) {
			auto cur = lp[x];
			while (x % cur == 0) {
				x /= cur;
			}
			cnt[cur]++;
		}
	}

	int res = n;

	for (auto [base, x] : cnt) {
		if (base == 1)
			continue;
		res = min(res, n - x);
	}

	if (res == n)
		return -1;
	return res;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();
	cout << solve() << "\n";
}
