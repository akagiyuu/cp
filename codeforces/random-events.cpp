#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

double solve()
{
	ll n, m;
	cin >> n >> m;
	vector<ll> a(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i];
	}

	ll max_i = n - 1;
	while (max_i >= 0 && a[max_i] - 1 == max_i)
		max_i--;

	double res = 1;
	ll p;
	double val;
	for (ll i = 0; i < m; i++) {
		cin >> p >> val;
		if (p > max_i)
			res *= (1 - val);
	}
	if (max_i == -1)
		return 1;
	return 1 - res;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		cout << solve() << "\n";
}
