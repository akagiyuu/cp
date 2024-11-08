#include <bits/stdc++.h>

typedef long long ll;

const ll MOD = 1000000007;

using namespace std;

ll solve()
{
	ll n;
	cin >> n;
	vector<ll> a(n);
	ll s = 0;
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
		s += a[i];
	}

	sort(a.begin(), a.end());
	ll m_i = (n - 1) / 2;
	ll left, right;
	if (n % 2 == 1) {
		left = a[m_i - 1];
		right = a[m_i];
	} else {
		left = a[m_i];
		right = a[m_i + 1];
	}

	ll x = left * (n + 1) - s;
	if (x < left) {
		return x;
	}
	if (s % n == 0) {
		x = s / n;
		if (left <= x && x <= right) {
			return x;
		}
	}
	x = right * (n + 1) - s;
	return x;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	ll t;
	cin >> t;
	while (t--)
		cout << solve() << "\n";
}
