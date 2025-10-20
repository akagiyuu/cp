#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;
const ll N = 10;

ll cnt[N];

void build()
{
	for (ll a = 0; a < N; a++) {
		for (ll b = 0; b < N; b++) {
			for (ll c = 0; c < N; c++) {
				ll d = a + b + c;
				if (d < N)
					cnt[d]++;
			}
		}
	}
}

void solve()
{
	ll n;
	cin >> n;
	ll res = 1;
	while (n) {
		res *= cnt[n % 10];
		n /= 10;
	}
	cout << res << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();

	int t;
	cin >> t;
	while (t--)
		solve();
}
