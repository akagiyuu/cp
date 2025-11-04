#include <bits/stdc++.h>

using namespace std;

#define int long long
#define double long double

bool solve()
{
	int l, r;
	cin >> l >> r;
	if (l == 0 && r == 0)
		return false;

	double res = 0;
	for (int i = l; i <= r; i++) {
		res += powl(1.0 / (double)i, 2.0 / 3.0);
	}
	res /= 3.0;
	int pw = 15;
	while (res < 1) {
		res *= 10.0;
		pw++;
	}
	vector<int> pw2;
	while (pw) {
		pw2.push_back(pw % 10);
		pw /= 10;
	}
	while (pw2.size() < 3)
		pw2.push_back(0);

	cout << fixed << setprecision(5) << res << "E-";
	for (int i = 3 - 1; i >= 0; i--) {
		cout << pw2[i];
	}
	cout << "\n";
	return true;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	while (solve())
		;
}
