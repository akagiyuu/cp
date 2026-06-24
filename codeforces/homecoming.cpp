#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll a, b, p;
	cin >> a >> b >> p;
	string s;
	cin >> s;

	ll n = s.size();
	ll res = n - 1;
	vector<ll> price(n, 0);
	int i = n - 2;
	while (i >= 0 && s[i] == s[n - 1]) {
		if (s[i] == 'A')
			price[i] = a;
		if (s[i] == 'B')
			price[i] = b;
		if (price[i] > p) {
			i--;
			break;
		}
		res = i;
		i--;
	}
	while (i >= 0) {
		price[i] = price[i + 1];
		if (s[i] != s[i + 1] && s[i] == 'A')
			price[i] += a;
		if (s[i] != s[i + 1] && s[i] == 'B')
			price[i] += b;
		if (price[i] > p)
			break;
		res = i;
		i--;
	}

	cout << res + 1 << "\n";
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
