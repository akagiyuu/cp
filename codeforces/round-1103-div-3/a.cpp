#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll n;
	cin >> n;
	ll m = 1000, M = 0;
	for (ll i = 0; i < n; i++) {
		ll x;
		cin >> x;
		m = min(m, x);
		M = max(M, x);
	}
	cout << M - m + 1 << "\n";
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
