#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll m, a, b, c;
	cin >> m >> a >> b >> c;
	ll first = min(a, m);
	ll second = min(b, m);

    ll res = first + second + min(c, 2 * m - first - second);
    cout << res << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		solve();
}
