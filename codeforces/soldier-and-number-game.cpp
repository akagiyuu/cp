#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;
const ll N = 5e6 + 7;

ll lp[N], sum[N];

void build()
{
	vector<ll> pr;
	for (ll i = 2; i < N; i++) {
		if (lp[i] == 0) {
			lp[i] = i;
			pr.push_back(i);
		}
		for (ll j = 0; i * pr[j] < N; j++) {
			lp[i * pr[j]] = pr[j];
			if (pr[j] == lp[i])
				break;
		}
	}

	sum[1] = 0;
	for (ll i = 2; i < N; i++) {
		sum[i] = sum[i / lp[i]] + 1;
	}
	for (ll i = 2; i < N; i++) {
		sum[i] += sum[i - 1];
	}
}

void solve()
{
	ll a, b;
	cin >> a >> b;
	cout << sum[a] - sum[b] << "\n";
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
