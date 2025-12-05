#include <bits/stdc++.h>

#define int long long

using namespace std;

vector<int> possible;

bool solve()
{
	int a, n, p, h;
	cin >> a >> n >> p >> h;
	if (h >= p - 1)
		return true;
	n++;
	possible.resize(n);
	for (int i = 0; i < n; i++) {
		possible[i] = (a * i) % p;
	}
	sort(possible.begin(), possible.end());
	// for (int i = 0; i < n; i++) {
	// 	cout << possible[i] << " ";
	// }
	// cout << "\n";
	for (int i = 0; i < n - 1; i++) {
		if (possible[i + 1] - possible[i] > h)
			return false;
	}

	return true;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--) {
		if (solve())
			cout << "YES\n";
		else
			cout << "NO\n";
	}
}
