#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll n, q;
	cin >> n >> q;
	vector<ll> a(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}

	vector<ll> pl(n), pr(n);
	stack<ll> s;

	for (ll i = 0; i < n; i++) {
		while (!s.empty() && a[i] < a[s.top()]) {
			pr[s.top()] = i;
			s.pop();
		}

		s.push(i);
	}
	while (!s.empty()) {
		pr[s.top()] = -1;
		s.pop();
	}

	for (ll i = n - 1; i >= 0; i--) {
		while (!s.empty() && a[i] > a[s.top()]) {
			pl[s.top()] = i;
			s.pop();
		}
		s.push(i);
	}
	while (!s.empty()) {
		pl[s.top()] = -1;
		s.pop();
	}

	vector<ll> ml(n, -1);
	for (ll i = 0; i < n; i++) {
		ll l = pl[i];
		ll r = pr[i];
		if (l == -1 || r == -1)
			continue;
		ml[r] = max(ml[r], l);
	}
	for (ll i = 1; i < n; i++) {
		ml[i] = max(ml[i], ml[i - 1]);
	}

	ll l, r;
	while (q--) {
		cin >> l >> r;
		l--;
		r--;

		if (ml[r] < l)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
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
