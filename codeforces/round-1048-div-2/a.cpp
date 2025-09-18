#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll a, b;
	cin >> a >> b;
	ll res = lcm(a, b);
	if (res == a & res == b) {
		cout << 0 << "\n";
	} else if (res == a || res == b) {
		cout << 1 << "\n";
	} else {
		cout << 2 << "\n";
	}
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
