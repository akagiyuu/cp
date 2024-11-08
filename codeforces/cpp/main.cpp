#include <bits/stdc++.h>
using namespace std;

const int maxN = 220000;
long long a[maxN], b[maxN];

int main(  )
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int T;
	for (cin >> T; T; T--) {
		int n, k;
		cin >> n >> k;
		for (int i = 0; i < n; i++) {
			cin >> a[i];
			b[i] = a[i] - i;
		}
		long long f = 1;
		for (int i = 0; i < k; i++)
            cout << *upper_bound(b, b + n, f) << '\n';
			cout << upper_bound(b, b + n, f) - b << '\n';
		f += upper_bound(b, b + n, f) - b;
		cout << f << '\n';
	}
	return 0;
}
