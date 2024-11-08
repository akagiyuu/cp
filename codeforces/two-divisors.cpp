#include <bits/stdc++.h>

typedef long long ll;

const ll MOD = 1000000007;

using namespace std;

ll gcd(ll a, ll b)
{
	while (b > 0) {
		ll temp = a % b;
		a = b;
		b = temp;
	}
	return a;
}

ll solve()
{
	ll a, b;
	cin >> a >> b;
	ll first = max(a, b);
	ll second = min(a, b);
	if (first % second == 0) {
		return first * (first / second);
	}
	ll res = first * second / gcd(first, second);

	return res;
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
