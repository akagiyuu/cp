#include <bits/stdc++.h>

using namespace std;

#define int long long
#define double long double

const double PI = acos(-1);

struct C {
	int x, y, r;
	C()
	{
	}
	C(int _x, int _y, int _r)
	{
		x = _x;
		y = _y;
		r = _r;
	}
};
double area(const C &a)
{
	return PI * (double)a.r * (double)a.r;
}
bool contain(const C &a, const C &b)
{
	if (a.r < b.r)
		return false;
	int dx = a.x - b.x;
	int dy = a.y - b.y;
	int dr = a.r - b.r;
	return dx * dx + dy * dy <= dr * dr;
}

void solve()
{
	int n;
	cin >> n;
	vector<C> a(n);
	for (int i = 0; i < n; i++) {
		int x, y, r;
		cin >> x >> y >> r;
		a[i] = C(x, y, r);
	}
	vector<int> cnt(n, 0);
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			cnt[j] += contain(a[i], a[j]);
			cnt[i] += contain(a[j], a[i]);
		}
	}
	double res = 0;
	for (int i = 0; i < n; i++) {
		if (cnt[i] == 0 || cnt[i] % 2 == 1)
			res += area(a[i]);
		else
			res -= area(a[i]);
	}
	cout << fixed << setprecision(10) << res << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
