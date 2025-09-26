#include <bits/stdc++.h>
// #include <cpp-dump.hpp>

using namespace std;

typedef long long ll;

const ll MOD = 1000000007;
const double PI = acos(-1.0);

struct Circle {
	double x;
	double y;
	double r;
};

double distance(Circle &a, Circle &b)
{
	double dx = a.x - b.x;
	double dy = a.y - b.y;

	return sqrt(dx * dx + dy * dy);
}

bool is_contain(Circle &a, Circle &b)
{
	double d = distance(a, b);
	return a.r > b.r && d < a.r - b.r;
}

bool is_contain(Circle &a, double x, double y)
{
	return pow(x - a.x, 2) + pow(y - a.y, 2) <= pow(a.r, 2);
}

double acos(double x, double y)
{
	double norm = sqrt(x * x + y * y);
	if (norm == 0)
		return 0;
	double res = acos(x / norm);

	return y > 0 ? res : 2 * PI - res;
}

pair<double, double> get_intersect_angle(Circle &coc, Circle &p)
{
	double a = -2 * p.x;
	double b = -2 * p.y;
	double c = pow(p.x, 2) + pow(p.y, 2) + pow(coc.r, 2) - pow(p.r, 2);

	double tmp = a * a + b * b;
	double m = pow(coc.r, 2) / tmp - pow(c, 2) / pow(tmp, 2);
	if (m <= 0)
		return make_pair(-1, -1);
	m = sqrt(m);
	double x0 = -a * c / tmp;
	double y0 = -b * c / tmp;

	double o1 = acos(x0 + b * m, y0 - a * m);
	double o2 = acos(x0 - b * m, y0 + a * m);
	if (o1 > o2)
		swap(o1, o2);
	if (abs(o1 - o2) > PI) {
		tie(o1, o2) = make_pair(o2 - 2 * PI, o1);
	}

	return make_pair(o1, o2);
}

pair<double, double> get_max_angle(Circle &coc, Circle &p)
{
	auto d = distance(coc, p);
	double tangent_length = sqrt(d * d - p.r * p.r);
	if (tangent_length > 0 && tangent_length <= coc.r) {
		Circle new_coc{
			.x = 0,
			.y = 0,
			.r = tangent_length,
		};
		return get_intersect_angle(new_coc, p);
	}

	return get_intersect_angle(coc, p);
}

double sum_overlapping(vector<pair<double, double> > &a)
{
	a.push_back(make_pair(2 * PI + 1, 2 * PI + 1));
	ll n = a.size();

	sort(a.begin(), a.end(), [](pair<double, double> &a, pair<double, double> &b) {
		if (a.first == b.first) {
			return a.second < b.second;
		}

		return a.first < b.first;
	});

	double ans = 0;
	double cur_start = a[0].first;
	double cur_end = a[0].second;
	for (ll i = 1; i < n; i++) {
		if (a[i].first <= cur_end) {
			cur_end = a[i].second;
			continue;
		}
		ans += cur_end - cur_start;
		tie(cur_start, cur_end) = a[i];
	}

	return ans;
}

double solve()
{
	Circle coc;
	cin >> coc.x >> coc.y >> coc.r;
	double tmp;
	cin >> tmp;
	coc.r *= tmp;

	ll n;
	cin >> n;
	vector<Circle> ps(n);
	for (ll i = 0; i < n; i++) {
		cin >> ps[i].x >> ps[i].y >> ps[i].r;
		ps[i].x -= coc.x;
		ps[i].y -= coc.y;
	}
	coc.x = 0;
	coc.y = 0;

	for (ll i = 0; i < n; i++) {
		if (is_contain(ps[i], coc.x, coc.y))
			return 1;
	}
	if (coc.r == 0)
		return 0;

	for (ll i = 0; i < n; i++) {
		if (is_contain(ps[i], coc))
			return 1;
	}

	vector<pair<double, double> > angles;
	for (ll i = 0; i < n; i++) {
		auto p = get_max_angle(coc, ps[i]);
		if (p.first == -1)
			continue;
		angles.push_back(p);
	}
	// cpp_dump(angles);

	return sum_overlapping(angles) / (2 * PI);
}

int main()
{
	// CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cout << solve() << "\n";
}
