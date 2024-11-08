#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll n;
	cin >> n;
	ll odd_count = 1ll << __builtin_popcountll(n);
	ll even_count = n + 1 - odd_count;
	cout << even_count << " " << odd_count << "\n";
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
