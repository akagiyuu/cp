#include <bits/stdc++.h>

#define int long long
#define double long double

using namespace std;

struct pt {
	double x, y;
};

struct L {
	double a, b;
	L(double a, double b)
		: a(a)
		, b(b)
	{
	}
};

pt intersect(const L &l1, const L &l2)
{
	return pt{
		.x = (l2.b - l1.b) / (l1.a - l2.a),
		.y = (l1.a * l2.b - l2.a * l1.b) / (l1.a - l2.a),
	};
}

void solve()
{
	int n;
	double A, B;
	cin >> n >> A >> B;
	vector<L> lines;
	double a, b;
	for (int i = 0; i < n; i++) {
		cin >> a >> b;

		double delta2 = a * a - 4 * A * (B - b);
		if (delta2 < 0)
			continue;

		lines.push_back(L(a, b));
	}
	n = lines.size();
	int res = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			auto p = intersect(lines[i], lines[j]);
			res += p.y > (A * p.x * p.x + B);
		}
	}
	cout << res << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
