#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
    ll n;
    cin >> n;

    ll temp;
    ll a = LLONG_MAX;
    ll b = 0;
    for (ll i = 0; i < n; i++) {
        cin >> temp;
        a = min(a, temp);
        b = max(b, temp);
    }
    cout << b - a << "\n";
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
