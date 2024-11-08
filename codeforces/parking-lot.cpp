#include <bits/stdc++.h>

typedef unsigned long long ll;

const ll MOD = 1000000007;

using namespace std;

ll pow(ll b, ll p)
{
	ll res = 1;
	while (p > 0) {
		if (p % 2 == 1) {
			res *= b;
		}
		b *= b;
		p /= 2;
	}
	return res;
}

void solve()
{
	ll n;
	cin >> n;
	ll res = (2 * 4 * 3 + 9 * (n - 3)) * pow(4, n - 3);
	cout << res << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
