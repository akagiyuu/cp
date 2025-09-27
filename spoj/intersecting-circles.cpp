#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

bool solve()
{
	ll x1, y1, r1, x2, y2, r2;
	cin >> x1 >> y1 >> x2 >> y2 >> r1 >> r2;

	ll dx = x2 - x1;
	ll dy = y2 - y1;

	ll d2 = dx * dx + dy * dy;
	ll s = r1 + r2;
	return d2 <= s * s;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--) {
		if (solve()) {
			cout << "YES\n";
		} else {
			cout << "NO\n";
		}
	}
}
