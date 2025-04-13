#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll n;
	cin >> n;

	ll temp;
	ll count = 0;
	ll sum = 0;
	ll m = 0;
	for (ll i = 0; i < n; i++) {
		cin >> temp;
		if (temp % 2 == 1)
			count++;
		sum += temp;
		m = max(m, temp);
	}

	if (count == n || count == 0)
		cout << m << "\n";
	else
		cout << sum - count + 1 << "\n";
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
