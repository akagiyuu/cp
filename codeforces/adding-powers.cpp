#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;

int convert(int n, int k)
{
	int res = 0;
	int i = 0;
	while (n > 0) {
		if (n % k > 1) {
			return -1;
		}
		if(n % k == 1) 
			res |= (1ll << i);
		n /= k;
		i++;
	}
	return res;
}

bool solve()
{
	int n, k;
	cin >> n >> k;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	vector<int> b(n);
	for (int i = 0; i < n; i++) {
		b[i] = convert(a[i], k);
		if (b[i] == -1)
			return false;
	}
	for (int j = 0; j < 64; j++) {
		int cnt = 0;
		for (int i = 0; i < n; i++) {
			if ((b[i] >> j) & 1)
				cnt++;
		}
		if (cnt >= 2)
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
