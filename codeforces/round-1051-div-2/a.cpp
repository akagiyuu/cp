#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll n;
	cin >> n;
	vector<ll> a(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}

	ll l = 0;
	ll r = n - 1;
	for (ll k = 0; k < n; k++) {
		if (a[l] != k + 1 && a[r] != k + 1) {
			cout << "NO\n";
			return;
		}
		if (a[l] == k + 1)
			l++;
		if (a[r] == k + 1)
			r--;
	}

	cout << "YES\n";
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
