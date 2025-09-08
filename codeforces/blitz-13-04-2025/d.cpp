#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll n;
	cin >> n;

	string s;
	cin >> s;

	ll count_original = 1;
	for (ll i = 1; i < n; i++) {
		if (s[i] != s[i - 1])
			count_original++;
	}

	ll start = 0;
	ll end;
	ll max_increase = 0;
	ll count_two = 0;
	while (start < n) {
		end = start;
		while (s[end] == s[start]) {
			end++;
		}
		end--;
		ll length = end - start + 1;

		if (length == 2) {
			count_two++;
			max_increase = max(max_increase, 1ll);
        }
		if (length >= 3) {
			max_increase = 2;
			break;
		}

		start = end + 1;
	}
	if (count_two >= 2)
		max_increase = 2;

	cout << count_original + max_increase << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
