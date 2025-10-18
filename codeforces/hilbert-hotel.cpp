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
	vector<bool> possible(n, false);
	for (ll i = 0; i < n; i++) {
		possible[(i + a[i] % n + n) % n] = true;
	}
	ll valid = true;
	for (ll i = 0; i < n; i++) {
		if (!possible[i]) {
			valid = false;
			break;
		}
	}
	if (valid)
		cout << "YES\n";
	else
		cout << "NO\n";
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
