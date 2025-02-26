#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

char encode(char c) {
    if (c == 'p') return 'q';
    if (c == 'q') return 'p';
    return c;
}

void solve()
{
    string s;
    cin >> s;
    ll n = s.length();
    for (ll i = n - 1; i >= 0; i--) {
        cout << encode(s[i]);
    }
    cout << "\n";
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
