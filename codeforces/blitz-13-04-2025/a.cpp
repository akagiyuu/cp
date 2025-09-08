#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	string s;
	cin >> s;

	ll count_f = 0;
	ll count_s = 0;

	for (auto c : s) {
		if (c == '4')
			count_f++;
		else if (c == '7')
			count_s++;
	}

	if (count_f > count_s)
		cout << "4\n";
	else
		cout << "7\n";
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
