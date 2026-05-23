#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = 1e9;

void solve()
{
	ll n;
	cin >> n;
	vector<ll> a(n), b(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (ll i = 0; i < n; i++) {
		cin >> b[i];
	}

	vector<ll> idxs(n);
	for (ll i = 0; i < n; i++) {
		idxs[b[i] / 2 - 1] = i;
	}

	vector<ll> min_indxs(n);
	min_indxs[n - 1] = idxs[n - 1];
	for (ll i = n - 2; i >= 0; i--) {
		min_indxs[i] = min(min_indxs[i + 1], idxs[i]);
	}

	ll res = INF;
	for (ll i = 0; i < n; i++) {
		res = min(res, i + min_indxs[a[i] / 2]);
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
