#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll n;
	cin >> n;
	vector<ll> a(n);
	unordered_set<ll> possible;
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
		possible.insert(a[i]);
	}
	ll m = possible.size();

	for (ll i = 0; i < n; i += m) {
		ll k = i;
		unordered_set<ll> temp = possible;
		for (ll j = i; j < min(i + m, n); j++) {
			if (temp.find(a[j]) != temp.end()) {
				a[k] = a[j];
				temp.erase(a[j]);
				k++;
			};
		}
		for (auto x : temp) {
			if (k >= n)
				break;
			a[k] = x;
			k++;
		}
	}
	for (ll i = 0; i < n; i++) {
		cout << a[i] << " ";
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
