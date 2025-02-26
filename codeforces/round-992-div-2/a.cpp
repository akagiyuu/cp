#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll n, k, x;
	cin >> n >> k;
	vector<vector<ll> > count(k);
	for (ll i = 0; i < n; i++) {
		cin >> x;
		count[x % k].push_back(i);
	}
	for (ll i = 0; i < k; i++) {
		if (count[i].size() == 1) {
            cout << "YES\n";
            cout << count[i][0] + 1 << "\n";
            return;
		}
	}
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
