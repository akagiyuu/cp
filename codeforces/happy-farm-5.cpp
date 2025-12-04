#include <bits/stdc++.h>

#define int long long

using namespace std;

typedef complex<int> P;
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

G convex_hull(G g)
{
	if (g.size() <= 1)
		return g;
	sort(g.begin(), g.end());

	G a;
	for (auto &p : g) {
		if (a.empty() || a.back() != p) {
			a.push_back(p);
		}
	}
	if (a.size() <= 1)
		return a;
	int n = a.size();

	G lower, upper;
	for (int i = 0; i < n; i++) {
		P p = a[i];
		while (lower.size() >= 2) {
			P A = lower[lower.size() - 2];
			P B = lower[lower.size() - 1];
			if (cross(B - A, p - A) <= 0)
				lower.pop_back();
			else
				break;
		}
		lower.push_back(p);
	}
	for (int i = n - 1; i >= 0; i--) {
		P p = a[i];
		while (upper.size() >= 2) {
			P A = upper[upper.size() - 2];
			P B = upper[upper.size() - 1];
			if (cross(B - A, p - A) <= 0)
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

int solve()
{
	int n;
	cin >> n;
	G g(n);
	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		g[i] = P(x, y);
	}
	g = convex_hull(g);
	n = g.size();
	if (n == 1)
		return 4;
	if (n == 2) {
		auto p = g[1] - g[0];
		return 4 + 2 * max(abs(real(p)), abs(imag(p)));
	}
	int res = 4;
	for (int i = 0; i < n; i++) {
		auto p = g[i] - g[(i + 1) % n];
		res += max(abs(real(p)), abs(imag(p)));
	}
	return res;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cout << solve() << "\n";
}
