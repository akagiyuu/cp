#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 1e5 + 1;

int lp[N];

void build()
{
	vector<int> pr;
	for (int i = 2; i < N; i++) {
		if (lp[i] == 0) {
			lp[i] = i;
			pr.push_back(i);
		}
		for (int j = 0; i * pr[j] < N; j++) {
			lp[i * pr[j]] = pr[j];
			if (pr[j] == lp[i])
				break;
		}
	}
}

int solve()
{
	int n, k;
	cin >> n >> k;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	map<map<int, int>, int> cnt;
	for (int i = 0; i < n; i++) {
		int x = a[i];
		map<int, int> f;
		while (x > 1) {
			int cur = lp[x];
			int pw = 0;
			while (x % cur == 0) {
				pw++;
				x /= cur;
			}
			pw %= k;
			if (pw != 0)
				f[cur] = pw;
		}
		cnt[f]++;
	}

	int res = 0;
	for (auto [f, x] : cnt) {
		map<int, int> f2;
		for (auto [base, pw] : f) {
			f2[base] = (k - pw) % k;
		}
		if (f2 == f)
			res += x * (x - 1);
		else
			res += x * cnt[f2];
	}
	res /= 2;
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
