#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = 1e16;

void solve()
{
	ll n;
	cin >> n;
	vector<ll> a(n), c(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (ll i = 0; i < n; i++) {
		cin >> c[i];
	}

	set<ll> s;
	for (ll i = 0; i < n; i++) {
		s.insert(a[i]);
	}
	vector<ll> b(s.begin(), s.end());
	for (ll i = 0; i < n; i++) {
		for (ll j = 0; j < (ll)b.size(); j++) {
			if (a[i] == b[j]) {
				a[i] = j + 1;
				break;
			}
		}
	}

	vector<ll> dp(n + 1, INF), ndp(n + 1, INF);
	dp[a[0]] = 0;
	dp[1] = min(dp[1], c[0]);

	for (ll i = 1; i < n; i++) {
		fill(ndp.begin(), ndp.end(), INF);

		for (ll prev = 1; prev <= n; prev++) {
			ll cost = dp[prev];
			if (a[i] > prev) {
				ndp[a[i]] = min(ndp[a[i]], cost);
				ndp[prev] = min(ndp[prev], cost + c[i]);
			} else if (a[i] < prev) {
				ndp[prev] = min(ndp[prev], cost + c[i]);
			} else {
				ndp[a[i]] = min(ndp[a[i]], cost);
			}
		}

		dp = ndp;
	}

	ll res = INF;
	for (auto cost : dp) {
		res = min(res, cost);
	}
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
