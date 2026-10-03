#include <bits/stdc++.h>

using namespace std;

#define int long long
#define pi pair<int, int>
#define fi first
#define se second

pi inter(const pi &a, const pi &b)
{
	pi res = { max(a.fi, b.fi), min(a.se, b.se) };
	if (res.fi > res.se)
		return { res.fi, res.fi };
	return res;
}
vector<pi> inter(const vector<pi> &a, const vector<pi> &b)
{
	return { inter(a[0], b[0]), inter(a[1], b[1]) };
}
int area(const vector<pi> &rec)
{
	return (abs(rec[0].fi - rec[0].se)) * (abs(rec[1].fi - rec[1].se));
}

bool solve()
{
	vector<vector<pi> > a(3, vector<pi>(2));
	for (int i = 0; i < 3; i++) {
		cin >> a[i][0].fi >> a[i][1].fi;
		cin >> a[i][0].se >> a[i][1].se;
	}
	a[1] = inter(a[1], a[0]);
	a[2] = inter(a[2], a[0]);
	int s = area(a[1]) + area(a[2]) - area(inter(a[1], a[2]));
	return s < area(a[0]);
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	if (solve())
		cout << "YES\n";
	else
		cout << "NO\n";
}
