#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

const ll N = 20;
constexpr array<ll, N> precal()
{
	array<ll, N> values = { 0 };
	for (ll i = 0; i < N; i++) {
		values[i] = 3 * (1ll << i) - 3;
	}

	return values;
}
const array<ll, N> values = precal();

void solve()
{
	ll n;
	cin >> n;
	ll i = lower_bound(values.begin(), values.end(), n - 1) - values.begin() + 1;
	cout << i << "\n";
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
