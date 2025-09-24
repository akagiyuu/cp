#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

ll binpow(ll a, ll b)
{
	ll res = 1;
	while (b) {
		if (b & 1)
			res = (res * a) % MOD;
		a = (a * a) % MOD;
		b /= 2;
	}

	return res;
}

ll cal_max_money(ll n)
{
	if (n <= 4)
		return n;
	if (n % 3 == 0)
		return binpow(3ll, n / 3);
	if (n % 3 == 1)
		return binpow(3ll, n / 3 - 1) * 4 % MOD;
	return binpow(3ll, n / 3) * 2 % MOD;
}

void solve()
{
	ll n;
	cin >> n;

	cout << cal_max_money(n) << "\n";
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
