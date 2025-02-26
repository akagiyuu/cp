#include <bits/stdc++.h>
#include <unordered_set>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll n, m, q;
	cin >> n >> m >> q;

	vector<ll> a(n);
	ll sum_a = 0;
	unordered_set<ll> a_set;

	for (ll i = 0; i < n; i++) {
		cin >> a[i];
		sum_a += a[i];
	}
	for (ll i = 0; i < n; i++) {
		if (sum_a - a[i] != 0)
			a_set.insert(sum_a - a[i]);
	}

	vector<ll> b(n);
	ll sum_b = 0;
	unordered_set<ll> b_set;

	for (ll i = 0; i < m; i++) {
		cin >> b[i];
		sum_b += b[i];
	}
	for (ll i = 0; i < m; i++) {
		if (sum_b - b[i] != 0)
			b_set.insert(sum_b - b[i]);
	}

	ll x;
	while (q--) {
		cin >> x;
		bool is_beatiful = false;

		if (a_set.size() < b_set.size()) {
			for (auto first : a_set) {
				if (x % first != 0)
					continue;
				if (b_set.find(x / first) != b_set.end()) {
					is_beatiful = true;
					break;
				}
			}
		} else {
			for (auto first : b_set) {
				if (x % first != 0)
					continue;
				if (a_set.find(x / first) != a_set.end()) {
					is_beatiful = true;
					break;
				}
			}
		}
		if (is_beatiful) {
			cout << "YES\n";
		} else {
			cout << "NO\n";
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
