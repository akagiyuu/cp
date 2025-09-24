#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

ll solve()
{
	ll a, b;
	cin >> a >> b;

	ll g = gcd(a, b);
	if (g != 1)
		return -1;

	return a * b - a - b + 1;
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
