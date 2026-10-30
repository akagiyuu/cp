#include <bits/stdc++.h>

using namespace std;

#define int long long

void solve()
{
	int n;
	cin >> n;
	string a, b;
	cin >> a >> b;

	int sample_space = 0;
	for (int k = 1; k <= n; k++)
		sample_space += (n - k + 1) * (n - k + 1);

	double res = 0;
	for (char c = 'A'; c <= 'Z'; c++) {
		vector<int> pa(n + 1, 0), pb(n + 1, 0);
		for (int i = 1; i <= n; i++)
			pa[i] = pa[i - 1] + (a[i - 1] == c);
		for (int i = 1; i <= n; i++)
			pb[i] = pb[i - 1] + (b[i - 1] == c);

		double s = 0;
		for (int i = 1; i <= n; i++)
			s += pa[i] * pb[i];
		s = n * s;
		res += s;

		s = 0;
		for (int i = n; i >= 1; i--) {
			s += pb[i];
			res -= pa[i - 1] * s;
		}

		s = 0;
		for (int i = n; i >= 1; i--) {
			s += pa[i];
			res -= pb[i - 1] * s;
		}
	}
	cout << setprecision(10) << res / sample_space << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
