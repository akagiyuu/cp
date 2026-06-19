#include <bits/stdc++.h>
#include <cassert>

using namespace std;

typedef long long ll;
typedef array<ll, 3> pt;

const ll MOD = 1000000007;

ll sq_dist(const pt &a, const pt &b)
{
	ll dx = a[0] - b[0];
	ll dy = a[1] - b[1];
	ll dz = a[2] - b[2];

	return dx * dx + dy * dy + dz * dz;
}

void solve()
{
	ll n;
	cin >> n;
	vector<pt> a(n);
	for (ll i = 0; i < n; i++) {
		cin >> a[i][0] >> a[i][1] >> a[i][2];
	}

	vector<bool> is_removed(n, false);
	for (ll i = 0; i < n; i++) {
		if (is_removed[i])
			continue;
		ll min_j = -1;
		for (ll j = i + 1; j < n; j++) {
			if (is_removed[j])
				continue;
			if (min_j == -1)
				min_j = j;
			else if (sq_dist(a[i], a[j]) < sq_dist(a[i], a[min_j])) {
				min_j = j;
			}
		}
		assert(!is_removed[min_j]);
		cout << i + 1 << " " << min_j + 1 << "\n";
		is_removed[i] = true;
		is_removed[min_j] = true;
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
