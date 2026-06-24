#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

void solve()
{
	int n, k;
	cin >> n >> k;
	string s;
	cin >> s;

	string p = s;
	string res = s;
	p.pop_back();
	for (; !p.empty(); p.pop_back()) {
		bool is_smaller = false;
		for (int i = 0; i < k; i++) {
			char a = p[i % p.size()];
			char b = res[i % res.size()];
			if (a == b)
				continue;
			is_smaller = a < b;
			break;
		}
		if (is_smaller)
			res = p;
	}
	for (int i = 0; i < k; i++) {
		cout << res[i % res.size()];
	}
	cout << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
