#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;
const int N = 1e6 + 7;

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
			if (pr[j] == lp[i])
				break;
		}
	}
}

int factorize(int n)
{
	int f = 1;
	while (n > 1) {
		int p = lp[n];
		int c = 0;
		while (n % p == 0) {
			c++;
			n /= p;
		}
		if (c % 2 == 1)
			f *= p;
	}
	return f;
}

void solve()
{
	int n;
	cin >> n;
	map<int, int> cnt;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		auto f = factorize(x);
		cnt[f]++;
	}

	int m = 0;
	int s = 0;
	for (auto [k, v] : cnt) {
		m = max(m, v);
		if (k != 1 && v % 2 == 1)
			continue;
		s += v;
	}
	int q;
	cin >> q;
	while (q--) {
		int w;
		cin >> w;
		if (w >= 1) {
			cout << max(m, s) << "\n";
		} else {
			cout << m << "\n";
		}
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();

	int t;
	cin >> t;
	while (t--)
		solve();
}
