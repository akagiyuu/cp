#include <bits/stdc++.h>
#include <cpp-dump.hpp>

using namespace std;

typedef long long ll;
typedef long double f;

const ll MOD = 1000000007;

struct Circle {
	f x;
	f y;
	f r;
};

f dis(Circle &a, Circle &b)
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

f cal_common_line_length(Circle &cir, f a, f b, f c)
{
	f d = pow(cir.r, 2) - pow(c, 2) / (pow(a, 2) + pow(b, 2));
	f m = d / (pow(a, 2) + pow(b, 2));

	return 4 * m * (pow(a, 2) + pow(b, 2));
}

f sum_common_arc(Circle a, Circle b)
{
	b.x -= a.x;
	b.y -= a.y;
	a.x = 0;
	a.y = 0;

	f c = cal_common_line_length(a, -2 * b.x, -2 * b.y, pow(b.x, 2) + pow(b.y, 2) + pow(a.r, 2) - pow(b.r, 2));
	if (c <= 0)
		return 0;

	f o_a = acos((2 * pow(a.r, 2) - c) / (2 * pow(a.r, 2)));
	f o_b = acos((2 * pow(b.r, 2) - c) / (2 * pow(b.r, 2)));

	f tmp = a.r * o_a + b.r * o_b;
    if(tmp > 0) {
        cpp_dump(sqrt(c));
    }
	return tmp;
}

void solve()
{
	f w, h;
	cin >> w >> h;
	ll n;
	cin >> n;

	vector<Circle> cs;
	for (ll i = 0; i < n; i++) {
		Circle c;
		cin >> c.x >> c.y >> c.r;

		bool add = true;
		for (ll j = 0; j < cs.size(); j++) {
			if (cs[j].r < c.r)
				continue;
			if (cs[j].r - c.r > dis(cs[j], c)) {
				add = false;
				break;
			}
		}
		if (add)
			cs.push_back(c);
	}
	n = cs.size();

	f ans = 0;
	for (ll i = 0; i < n; i++) {
		ans += 2 * M_PI * cs[i].r;
	}

	for (ll i = 0; i < n; i++) {
		for (ll j = i + 1; j < n; j++) {
			f tmp = sum_common_arc(cs[i], cs[j]);
			if (tmp > 0) {
				cpp_dump(cs[i].x, cs[i].y);
				cpp_dump(cs[j].x, cs[j].y);
				cpp_dump(tmp);
			}
			ans -= tmp;
		}
	}

	cout << ans << "\n";
}

int main()
{
	CPP_DUMP_SET_OPTION(es_style, cpp_dump::types::es_style_t::no_es);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		solve();
}
