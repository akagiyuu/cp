#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;
const int INF = 1ll << 32;

string s;

int calc()
{
	int x = 0;
	while (cin >> s) {
		if (s == "add") {
			x = min(x + 1, INF);
			continue;
		}
		if (s == "end") {
			break;
		}
		int cnt;
		cin >> cnt;
		x = min(x + cnt * calc(), INF);
	}
	return x;
}

void solve()
{
	int l;
	cin >> l;
	int res = calc();
	if (res == INF) {
		cout << "OVERFLOW!!!\n";
	} else {
		cout << res << "\n";
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
