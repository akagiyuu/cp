#include <bits/stdc++.h>
#include <queue>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll n, k, x;
	cin >> n >> k;

	priority_queue<ll> a, b;
	for (ll i = 0; i < n; i++) {
		cin >> x;
		a.push(x);
	}
	for (ll i = 0; i < k; i++) {
		cin >> x;
		b.push(-x);
	}
	ll res = 0;
	while (!b.empty()) {
		ll dis = -b.top();
		b.pop();
		if (a.size() < dis)
			break;

		ll last = 0;
		for (ll i = 0; i < dis; i++) {
			ll val = a.top();
			a.pop();
			res += val;
			last = val;
		}
		res -= last;
	}
	while (!a.empty()) {
		ll val = a.top();
		a.pop();
		res += val;
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
