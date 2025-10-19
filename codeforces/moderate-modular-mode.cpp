#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

ll solve()
{
	ll x, y;
	cin >> x >> y;
	if (x > y) {
		return x + y;
	}
	return y - (y % x) / 2;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		cout << solve() << "\n";
}
