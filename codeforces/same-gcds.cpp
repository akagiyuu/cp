#include <bits/stdc++.h>

using namespace std;

#define int long long

int phi(int n)
{
	int res = n;
	for (int i = 2; i * i <= n; i++) {
		if (n % i != 0)
			continue;
		res -= res / i;
		while (n % i == 0)
			n /= i;
	}
	if (n > 1) {
		res -= res / n;
	}
	return res;
}

void solve()
{
	int a, m;
	cin >> a >> m;
	auto g = gcd(a, m);
	m /= g;
	cout << phi(m) << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		solve();
}
