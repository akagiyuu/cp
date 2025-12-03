#include <bits/stdc++.h>

#define int long long

using namespace std;

typedef complex<int> P;
struct L : public vector<P> {
	L(const P &a, const P &b)
	{
		push_back(a);
		push_back(b);
	}
	L()
	{
	}
};
typedef vector<P> G;

namespace std
{
bool operator<(const P &a, const P &b)
{
	return real(a) != real(b) ? real(a) < real(b) : imag(a) < imag(b);
}
}

int cross(const P &a, const P &b)
{
	return imag(conj(a) * b);
}

bool line_contain(const L &l, const P &p)
{
	auto s1 = l[1] - l[0];
	auto s2 = p - l[0];
	return (__int128)real(s1) * (__int128)imag(s2) == (__int128)real(s2) * (__int128)imag(s1);
}

G convex_hull(G g)
{
	if (g.size() <= 1)
		return g;
	sort(g.begin(), g.end());

	G a;
	for (auto &p : g) {
		if (a.empty() || abs(a.back() - p) > 0)
			a.push_back(p);
	}
	if (a.size() <= 1)
		return a;

	G lower, upper;
	for (auto &p : a) {
		while (lower.size() >= 2) {
			P A = lower[lower.size() - 2];
			P B = lower[lower.size() - 1];
			double cr = cross(B - A, p - A);
			if (cr <= 0)
				lower.pop_back();
			else
				break;
		}
		lower.push_back(p);
	}
	for (int i = a.size() - 1; i >= 0; i--) {
		P p = a[i];
		while (upper.size() >= 2) {
			P A = upper[upper.size() - 2];
			P B = upper[upper.size() - 1];
			double cr = cross(B - A, p - A);
			if (cr <= 0)
				upper.pop_back();
			else
				break;
		}
		upper.push_back(p);
	}
	lower.pop_back();
	upper.pop_back();

	G res = lower;
	res.insert(res.end(), upper.begin(), upper.end());
	if (res.empty())
		return a;
	return res;
}

bool solve()
{
	int n;
	cin >> n;
	G g(n);
	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		g[i] = P(x, y);
	}
	G hull = convex_hull(g);
	if (hull.size() <= 2)
		return true;
	if (hull.size() >= 5)
		return false;
	if (hull.size() == 4) {
		auto check = [&](int i, int j, int k, int l) {
			L l1(hull[i], hull[j]), l2(hull[k], hull[l]);
			for (int i = 0; i < n; i++) {
				if (!line_contain(l1, g[i]) && !line_contain(l2, g[i]))
					return false;
			}
			return true;
		};
		return check(0, 1, 2, 3) || check(0, 2, 1, 3) || check(0, 3, 1, 2);
	}
	if (hull.size() == 3) {
		auto check = [&](const L &l, const P &p) {
			P second(-1, -1);
			for (int i = 0; i < n; i++) {
				if (g[i] == hull[0] || g[i] == hull[1] || g[i] == hull[2])
					continue;
				if (line_contain(l, g[i]))
					continue;
				if (second == P(-1, -1)) {
					second = g[i];
					continue;
				}
				if (!line_contain(L(p, second), g[i]))
					return false;
			}
			return true;
		};

		return check(L(hull[0], hull[1]), hull[2]) || check(L(hull[0], hull[2]), hull[1]) ||
		       check(L(hull[1], hull[2]), hull[0]);
	}
	assert(false);
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
