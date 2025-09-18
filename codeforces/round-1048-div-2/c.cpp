#include <bits/stdc++.h>
#include <utility>

using namespace std;

typedef unsigned long long ll;

const ll MOD = 1000000007;

void solve()
{
	ll k, x;
	cin >> k >> x;
	__int128 sum = 1 << (k + 1);
	vector<short> res = vector<short>(0);

	auto cur = make_pair((__int128)x, sum - x);

	while (cur.first != (1 << k)) {
		if (cur.first > cur.second) {
			cur = make_pair(cur.first - cur.second, 2 * cur.second);
			res.push_back(2);
		} else {
			cur = make_pair(2 * cur.first, cur.second - cur.first);
			res.push_back(1);
		}
	}

    reverse(res.begin(), res.end());
	ll n = res.size();
	cout << n << "\n";
    for (ll i = 0; i < n; i++) {
        cout << res[i] << " ";
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
