#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
    ll n;
    cin >> n;
    
	string a, b;
	cin >> a >> b;

	ll even_chain = 0, odd_chain = 0;
	for (ll i = 0; i < n; i++) {
		if (i % 2 == 0) {
			even_chain += a[i] == '0';
			odd_chain += b[i] == '0';
		} else {
			odd_chain += a[i] == '0';
			even_chain += b[i] == '0';
		}
	}

	bool is_possible = even_chain >= (n + 1) / 2 && odd_chain >= n / 2;
	cout << (is_possible ? "YES" : "NO") << "\n";
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
