#include <bits/stdc++.h>

using namespace std;

#define int long long
#define pi pair<int, int>
#define fi first
#define se second

const int W = 1e5;
const int H = 100;

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

int cross(const P &a, const P &b)
{
	return imag(conj(a) * b);
}

bool intersectLS(const L &l, const L &s)
{
	auto c1 = cross(l[1] - l[0], s[0] - l[0]);
	auto c2 = cross(l[1] - l[0], s[1] - l[0]);

	return (c1 >= 0 && c2 <= 0) || (c1 <= 0 && c2 >= 0);
}

P horizontal_refl(int refl_y, const P &p)
{
	return P(real(p), 2 * refl_y - imag(p));
}

L horizontal_refl(int refl_y, L l)
{
	l[0] = horizontal_refl(refl_y, l[0]);
	l[1] = horizontal_refl(refl_y, l[1]);
	return l;
}

struct Mirror {
	int idx, x1, x2;
	Mirror(int _idx, int _x1, int _x2)
	{
		idx = _idx;
		x1 = _x1;
		x2 = _x2;
	}
	Mirror()
	{
	}
};

int calc(int hl, int hr, const vector<vector<Mirror> > &mirrors, const vector<int> &v)
{
	int n = v.size();

	P l(0, hl);

	int res = 0;

	for (int cnt = 1; cnt <= n; cnt++) {
		vector<bool> visited(n, false);
		// cout << "TEST: " << cnt << "\n";
		P r(W, 0);
		if (cnt % 2 == 1)
			r.imag(-hr - (cnt - 1) * H);
		else
			r.imag(hr - cnt * H);
		// cout << l << "\n";
		// cout << r << "\n";
		L path(l, r);

		int cur = 0;
		bool ok = true;
		for (int i = 0; i < cnt; i++) {
			ok = false;
			int y = -H * i;
			for (auto [idx, x1, x2] : mirrors[i % 2]) {
				if (visited[idx])
					continue;
				// cout << x1 << " " << x2 << " " << y << "\n";
				L mirror(P(x1, y), P(x2, y));
				if (!intersectLS(path, mirror))
					continue;

				// cout << idx << " ";
				visited[idx] = true;
				cur += v[idx];
				ok = true;
				break;
			}
			if (ok == false)
				break;
		}
		cout << "\n";
		if (ok)
			res = max(res, cur);
	}

	return res;
}

void solve()
{
	int hl, hr;
	cin >> hl >> hr;

	int n;
	cin >> n;
	vector<int> v(n);
	vector<vector<Mirror> > mirrors(2);
	for (int i = 0; i < n; i++) {
		cin >> v[i];
		char c;
		cin >> c;
		int x1, x2;
		cin >> x1 >> x2;
		if (c == 'F') {
			mirrors[0].push_back(Mirror(i, x1, x2));
		} else {
			mirrors[1].push_back(Mirror(i, x1, x2));
		}
	}

	int res = calc(hl, hr, mirrors, v);

	swap(mirrors[0], mirrors[1]);
	res = max(res, calc(H - hl, H - hr, mirrors, v));

	cout << res << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
