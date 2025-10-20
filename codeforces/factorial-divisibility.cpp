#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

bool solve()
{
	ll n, x, tmp;
	cin >> n >> x;
	vector<ll> cnt(x + 1);
	for (ll i = 0; i < n; i++) {
		cin >> tmp;
		cnt[tmp]++;
	}
	for (ll i = 0; i < x; i++) {
		if (cnt[i] == 0)
			continue;
		if (cnt[i] % (i + 1) != 0)
			return false;
		cnt[i + 1] += cnt[i] / (i + 1);
	}
	return true;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	if (solve())
		cout << "Yes\n";
	else
		cout << "No\n";
}
