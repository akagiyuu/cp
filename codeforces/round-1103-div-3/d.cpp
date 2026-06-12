#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll n;
	ll k;
	cin >> n >> k;

	map<int, int> freq;

	for (ll i = 0; i < n; i++) {
		ll x;
		cin >> x;
		freq[x]++;
	}

	bool ok = false;

	for (auto &[v, cnt] : freq) {
		if (cnt % 2 == 0) {
			ok = true;
			break;
		}
	}

	if (!ok) {
		vector<ll> vals;
		vals.reserve(freq.size());

		for (auto &[v, _] : freq) {
			vals.push_back(v);
		}

		sort(vals.begin(), vals.end());

		for (ll i = 1; i < vals.size(); i++ ) {
			if (vals[i] - vals[i - 1] <= k) {
				ok = true;
				break;
			}
		}
	}

	cout << (ok ? "YES" : "NO") << '\n';
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
