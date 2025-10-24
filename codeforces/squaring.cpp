#include <bits/stdc++.h>
// #include <cpp-dump.hpp>

using namespace std;

#define int long long

void solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	int pre = 0;
	int res = 0;
	for (int i = 1; i < n; i++) {
		if (a[i - 1] == 1) {
			continue;
		}
		if (a[i] == 1) {
			cout << -1 << "\n";
			return;
		}
		int cur = max(pre - (int)floor(log2(log(a[i]) / log(a[i - 1]))), 0ll);
		// cout << cur << "\n";
		res += cur;
		pre = cur;
	}
	cout << res << "\n";
}

signed main()
{
	// CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		solve();
}
