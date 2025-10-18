#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll n;
	cin >> n;
	vector<ll> a(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}
	if (n == 1) {
		cout << n << " " << n << "\n";
		cout << -a[n - 1] << "\n";
		cout << n << " " << n << "\n";
		cout << 0 << "\n";
		cout << n << " " << n << "\n";
		cout << 0 << "\n";
		return;
	}
	cout << 1 << " " << n << "\n";
	for (ll i = 0; i < n - 1; i++) {
		cout << -a[i] * n << " ";
	}
	cout << 0 << "\n";
	cout << 1 << " " << n - 1 << "\n";
	for (ll i = 0; i < n - 1; i++) {
		cout << a[i] * (n - 1) << " ";
	}
	cout << n << " " << n << "\n";
	cout << -a[n - 1] << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
