#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;

struct Circle {
	double x;
	double y;
	double r;
};

struct cmp {
	bool operator()(const pair<double, double> &A, const pair<double, double> &B) const
	{
		const double EPS = 1e-9;
		if (A.first + EPS < B.first)
			return true;
		if (B.first + EPS < A.first)
			return false;
		if (A.second + EPS < B.second)
			return true;
		return false;
	}
};

vector<pair<double, double> > get_intersect(Circle c1, Circle c2)
{
	double dx = c1.x;
	double dy = c1.y;

	c2.x -= c1.x;
	c2.y -= c1.y;
	c1.x = 0;
	c1.y = 0;

	double a = -2 * c2.x;
	double b = -2 * c2.y;
	double c = pow(c2.x, 2) + pow(c2.y, 2) + pow(c1.r, 2) - pow(c2.r, 2);
	double denom = pow(a, 2) + pow(b, 2);
	double m = pow(c1.r, 2) / denom - pow(c, 2) / pow(denom, 2);
	if (m < 0)
		return {};
	m = sqrt(m);
	double x0 = -a * c / denom + dx;
	double y0 = -b * c / denom + dy;

	return { make_pair(x0 + b * m, y0 - a * m), make_pair(x0 - b * m, y0 + a * m) };
}

ll solve()
{
	ll n;
	cin >> n;

	vector<Circle> c(n);
	for (ll i = 0; i < n; i++) {
		cin >> c[i].x >> c[i].y >> c[i].r;
	}
	if (n == 1)
		return 2;

	set<pair<double, double>, cmp> inters;
	vector<set<pair<double, double>, cmp> > cinters(n);
	for (ll i = 0; i < n; i++) {
		for (ll j = i + 1; j < n; j++) {
			auto cur_inters = get_intersect(c[i], c[j]);
			for (auto x : cur_inters) {
				inters.insert(x);
				cinters[i].insert(x);
				cinters[j].insert(x);
			}
		}
	}
	ll res = 2 - inters.size();
	for (ll i = 0; i < n; i++) {
		res += cinters[i].size();
	}
	return res;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cout << solve() << "\n";
}
