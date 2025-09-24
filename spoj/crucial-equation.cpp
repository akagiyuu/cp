#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

ll gcd(ll a, ll b) {
    while(b) {
        tie(a, b) = make_pair(b, a % b);
    }
    return a;
}

bool solve()
{
    ll a, b, c;
    cin >> a >> b >> c;
    
    return c % gcd(a, b) == 0;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	ll t;
	cin >> t;
	for (ll i = 0; i < t; i++) {
		cout << "Case " << i + 1 << ": ";
		if (solve()) {
			cout << "Yes\n";
		} else {
			cout << "No\n";
		}
	}
}
