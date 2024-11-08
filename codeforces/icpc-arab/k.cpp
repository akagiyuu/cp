#include <bits/stdc++.h>

typedef long long ll;

const ll MOD = 1000000007;

using namespace std;

ll count(vector<int> a, vector<int> b)
{
	ll count = 0;
	for (int i = 0; i < 26; i++) {
		if (a[i] == b[i]) {
			count += a[i];
			continue;
		}
		if (a[i] < b[i]) {
			ll diff = b[i] - a[i];
			for (int j = i + 1; j < 26; j++) {
				if (a[j] == 0) {
					continue;
				}
				if (a[j] >= diff) {
					a[j] -= diff;
                    break;
				}
                diff -= a[j];
                a[j] = 0;
			}
			count += a[i];
			continue;
		}
		if (a[i] > b[i]) {
			ll diff = a[i] - b[i];
			for (int j = i + 1; j < 26; j++) {
				if (b[j] == 0) {
					continue;
				}
				if (b[j] >= diff) {
					b[j] -= diff;
                    break;
				}
                diff -= b[j];
                b[j] = 0;
			}
			count += b[i];
			continue;
		}
	}
	return count;
}

void solve()
{
	ll n, m;
	cin >> n >> m;
	vector<vector<int> > jokes(n, vector<int>(26, 0));
	for (ll i = 0; i < n; i++) {
		char tmp;
		for (int j = 0; j < m; j++) {
			cin >> tmp;
			jokes[i][tmp - 'a']++;
		}
	}
	ll q;
	cin >> q;
	while (q--) {
		ll first, second;
		cin >> first >> second;
		first--;
		second--;
		cout << count(jokes[first], jokes[second]) << "\n";
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
