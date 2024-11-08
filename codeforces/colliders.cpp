#include <bits/stdc++.h>

typedef long long ll;

const ll MOD = 1000000007;

using namespace std;

void solve()
{
	ll n, m;
	cin >> n >> m;
	vector<vector<ll> > factors(n + 1);
	for (ll i = 2; i <= n; i++) {
		if (factors[i].size() >= 1) {
			continue;
		}
		factors[i].push_back(i);
		for (ll j = 2 * i; j <= n; j += i) {
			factors[j].push_back(i);
		}
	}
	vector<bool> is_on(n + 1, false);
	map<ll, set<ll> > counts;
	while (m--) {
		char ops;
		ll i;
		cin >> ops >> i;
		if (ops == '-') {
			if (!is_on[i]) {
				cout << "Already off\n";
				continue;
			}
			for (auto j : factors[i]) {
				counts[j].erase(i);
			}
            is_on[i] = false;
			cout << "Success\n";
			continue;
		}

		if (is_on[i]) {
			cout << "Already on\n";
			continue;
		}

		bool is_conflict = false;
		ll k = -1;
		for (auto j : factors[i]) {
			if (counts[j].size() > 0) {
				k = *counts[j].begin();
				is_conflict = true;
				break;
			}
		}
		if (is_conflict) {
			cout << "Conflict with " << k << "\n";
			continue;
		}
        is_on[i] = true;
		for (auto j : factors[i]) {
			counts[j].insert(i);
		}
		cout << "Success\n";
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
