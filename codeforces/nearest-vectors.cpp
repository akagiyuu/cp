#include <bits/stdc++.h>

#define int long long
#define double long double

using namespace std;

const double PI = acos(-1);

typedef complex<__int128> P;

inline bool upper(const P &p)
{
	__int128 y = p.imag();
	__int128 x = p.real();
	return (y > 0) || (y == 0 && x > 0);
}

__int128 dot(const P &a, const P &b)
{
	return real(conj(a) * b);
}

__int128 cross(const P &a, const P &b)
{
	return imag(conj(a) * b);
}

bool ccw(P a, P b)
{
	return cross(a, b) > 0;
}

double angle(const P &a, const P &b)
{
	return atan2(abs((double)cross(a, b)), (double)dot(a, b));
}

void solve()
{
	int n;
	cin >> n;
	vector<pair<P, int> > a(n);
	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		a[i] = { P(x, y), i };
	}

	sort(a.begin(), a.end(), [](const pair<P, int> &a, const pair<P, int> &b) {
		auto p = a.first, q = b.first;
		if (upper(p) != upper(q))
			return upper(p);
		return cross(p, q) > 0;
	});
	double res = angle(a[0].first, a[1].first);
	int mini = 0;
	for (int i = 1; i < n; i++) {
		double cur = angle(a[i].first, a[(i + 1) % n].first);
		if (cur < res) {
			res = cur;
			mini = i;
		}
	}
	cout << a[mini].second + 1 << " " << a[(mini + 1) % n].second + 1 << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
