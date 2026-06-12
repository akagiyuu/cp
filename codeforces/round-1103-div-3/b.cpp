#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll k, n;
	cin >> n >> k;
	string s;
	cin >> s;

	for (ll i = 0; i < n; i++) {
		if (s[i] == '0')
			continue;
		if (i + k < n) {
			s[i] = '0';
			s[i + k] = s[i + k] == '0' ? '1' : '0';
			continue;
		}
		cout << "no\n";
		return;
	}
	cout << "yes\n";
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
