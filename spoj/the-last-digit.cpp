#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll pow(ll a, ll b, ll mod)
{
	ll res = 1;

	while (b) {
		if (b & 1)
			res = (res * a) % mod;

		a = (a * a) % mod;
		b /= 2;
	}

	return res;
}

void solve()
{
    ll a, b;
    cin >> a >> b;
    cout << pow(a, b, 10) << "\n";
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
