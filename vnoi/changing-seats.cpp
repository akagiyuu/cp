#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll n;
	cin >> n;

	vector<array<ll, 2> > a(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i][0];
	}
	for (ll i = 0; i < n; i++) {
		cin >> a[i][1];
	}

	if (n % 2 == 0) {
		cout << -1 << "\n";
		return;
	}

	ll count = 12 * (n / 2) + 1;

	ll k, x, row;
	for (ll i = 0; i < n; i++) {
		if (a[i][1] == 0 || a[i][0] == 0) {
			k = i;
			x = max(a[i][0], a[i][1]);
			if (a[i][0] > 0)
				row = 0;
			else
				row = 1;
			break;
		}
	}
	cout << count << "\n";
	if (row == 0)
		cout << x << " ";
	a.erase(a.begin() + k);
	n = a.size();
	for (ll i = 0; i < n; i += 2) {
		array<ll, 12> swap = {
            a[i][1],
            a[i][0],
            x,
            a[i][1],
            a[i + 1][1],
            x,
            a[i][1],
            a[i + 1][1],
            x,
            a[i + 1][0],
            a[i + 1][1],
            x,
        };

		for (auto v : swap) {
			cout << v << " ";
		}
	}
	if (row == 1)
		cout << x << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
