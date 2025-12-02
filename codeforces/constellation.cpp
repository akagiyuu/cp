#include <bits/stdc++.h>

using namespace std;

typedef complex<__int128> P;

__int128 dot(const P &a, const P &b)
{
	return real(conj(a) * b);
}

__int128 cross(const P &a, const P &b)
{
	return imag(conj(a) * b);
}

void solve()
{
	int n;
	cin >> n;
	vector<P> a(n);
	for (int i = 0; i < n; i++) {
		long long x, y;
		cin >> x >> y;
		a[i].real(x);
		a[i].imag(y);
	}
	array<int, 3> res;
	res[0] = 0;

	int min_i = 2;
	__int128 dist = -1;
	for (int i = 1; i < n; i++) {
		auto d = a[i] - a[res[0]];
		__int128 cur = dot(d, d);
		if (cur == 0)
			continue;
		if (dist == -1) {
			min_i = i;
			dist = cur;
			continue;
		}
		if (cur < dist) {
			min_i = i;
			dist = cur;
		}
	}
	res[1] = min_i;

	min_i = 2;
	dist = -1;
	for (int i = 0; i < n; i++) {
		if (i == res[0] || i == res[1])
			continue;
		__int128 cur = cross(a[res[1]] - a[res[0]], a[i] - a[res[0]]);
		if (cur == 0)
			continue;
		if(cur < 0) cur = -cur;
		if (dist == -1) {
			min_i = i;
			dist = cur;
		}
		if (cur < dist) {
			min_i = i;
			dist = cur;
		}
	}
	res[2] = min_i;
	for (int i = 0; i < 3; i++) {
		cout << res[i] + 1 << " ";
	}
	cout << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
