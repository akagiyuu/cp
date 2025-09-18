#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
    ll n;
    cin >> n;
	string s;
	cin >> s;
	ll count = 0;
	for (ll i = 0; i < n; i++) {
		if (s[i] == '1')
			count++;
	}

	ll res = count;
	for (ll i = 0; i < count; i++) {
		if (s[n - 1 - i] == '1')
			res--;
	}
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
