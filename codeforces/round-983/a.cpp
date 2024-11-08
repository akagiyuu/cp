#include <bits/stdc++.h>

typedef long long ll;

const ll MOD = 1000000007;

using namespace std;

void solve()
{
	int n;
	cin >> n;
	int count = 0;
	for (int i = 0; i < 2 * n; i++) {
		short x;
		cin >> x;
		count += x;
	}
	int min_light = count % 2;
	int max_light;
	if (count <= n) {
		max_light = count;
	} else {
		max_light = n - (count - n);
	}
	cout << min_light << " " << max_light << "\n";
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
