#include <bits/stdc++.h>

typedef long long ll;

const ll MOD = 1000000007;

using namespace std;

void solve()
{
	ll n, k;
	cin >> n >> k;
	if (n == 1 && k == 1) {
		cout << "1\n1\n";
		return;
	}
	if (k == 1 || k == n) {
		cout << "-1\n";
		return;
	}
	int a[3];
	if (k % 2 != 0) {
		a[0] = 1;
		a[1] = k - 1;
		a[2] = k + 2;
	} else {
		a[0] = 1;
		a[1] = k;
		a[2] = k + 1;
	}
	ll m = min(min(a[0], a[1]), a[2]);
	ll M = max(max(a[0], a[1]), a[2]);
	if (m <= 0 || M > n) {
		cout << "-1\n";
		return;
	}
	cout << 3 << "\n";
	for (ll i = 0; i < 3; i++) {
		cout << a[i] << " ";
	}
    cout << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	ll t;
	cin >> t;
	while (t--)
		solve();
}
