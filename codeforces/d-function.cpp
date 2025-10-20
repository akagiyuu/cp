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
		b >>= 1;
	}
	return res;
}

void solve()
{
	ll l, r, k;
	cin >> l >> r >> k;
	ll p = 9 / k + 1;
	ll res = (binpow(p, r) - binpow(p, l) + MOD) % MOD;
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
