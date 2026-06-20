#include <bits/stdc++.h>
#include <cassert>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll n, k;
	cin >> n >> k;
	vector<ll> a(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}
	vector<ll> res;
	vector<bool> exist(n + 1, false);
	for (ll i = 0; i < n; i++) {
		if (!exist[a[i]])
			res.push_back(a[i]);
		exist[a[i]] = true;
	}
	if((ll) res.size() > k) {
		cout << -1 << "\n";
		return;
	}
	while(res.size() < k) {
		res.push_back(1);
	}

	cout << n * k << "\n";
	for (ll i = 0; i < n; i++) {
		for (ll j = 0; j < k; j++) {
			cout << res[j] << " ";
		}
	}
	cout << "\n";
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
