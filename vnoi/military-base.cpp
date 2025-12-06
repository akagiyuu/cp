#include <bits/stdc++.h>

#define int long long

using namespace std;

typedef complex<__int128> P;
typedef vector<P> G;

int cross(const P &a, const P &b)
{
	return imag(conj(a) * b);
}

void solve()
{
	int n;
	cin >> n;
	G g(n);
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		g[i].real(x);
	}
	for (int i = 0; i < n; i++) {
		int y;
		cin >> y;
		g[i].imag(y);
	}
	auto next = [&](int i) {
		int res = i + 1;
		return res < n ? res : res - n;
	};
	auto prev = [&](int i) {
		int res = i - 1;
		return res < 0 ? res + n : res;
	};
	// int res = -1;
	// for (int mask = 0; mask < (1 << n); mask++) {
	// 	int A = 0;
	// 	P prev(-1, -1);
	// 	P start;
	// 	for (int i = 0; i < n; i++) {
	// 		if (!((mask >> i) & 1))
	// 			continue;
	// 		if (prev == P(-1, -1)) {
	// 			start = g[i];
	// 			prev = g[i];
	// 			continue;
	// 		}
	// 		A += cross(prev, g[i]);
	// 		prev = g[i];
	// 	}
	// 	A += cross(prev, start);
	// 	A = abs(A);
	// 	if (A == 41)
	// 		res = mask;
	// 	break;
	// }
	// cout << res << "\n";
	int res = 0;
	for (int i = 0; i < n; i++) {
		vector<int> area(n);
		int cur = cross(g[i], g[next(i)]);
		for (int j = 2; j <= n - 1; j++) {
			int k = (i + j) % n;
			cur += cross(g[prev(k)], g[k]);
			area[j] = abs(cur + cross(g[k], g[i]));
			area[j] *= 2;
		}
		int half = area[n - 1] / 2;
		int j1 = upper_bound(area.begin(), area.end(), half) - area.begin();
		int j2 = j1 - 1;
		int j = abs(area[j1] - half) <= abs(area[j2] - half) ? j1 : j2;
		j = (i + j) % n;

		for (auto [k, left, right] : { array{ next(i), i, j }, array{ next(j), j, i } }) {
			// cout << k << "\n";
			int turn = 1;
			int cur = cross(g[right], g[left]) + cross(g[left], g[k]);
			int prev_l = k;
			int l = next(k);
			while (l != right) {
				cur += cross(g[prev_l], g[l]);
				if (turn == 0) {
					prev_l = l;
					l = next(l);
					turn = 1;
					continue;
				}

				int cnt = (right + n - l - 1 + n) % n;
				if (cnt == 0) {
					prev_l = l;
					break;
				}
				vector<int> area(cnt + 1);
				int cr = cross(g[l], g[next(l)]);
				for (int x = 1; x <= cnt; x++) {
					int y = (l + x) % n;
					cr += cross(g[prev(y)], g[y]);
					area[x] = abs(cr + cross(g[y], g[i]));
					area[x] *= 2;
				}
				int half = area[cnt] / 2;
				int x1 = lower_bound(area.begin(), area.end(), half) - area.begin();
				int x2 = x1 - 1;
				int x = 0;
				if (x2 >= 0)
					int x = abs(area[x1] - half) <= abs(area[x2] - half) ? x1 : x2;
				else
					x = x1;
				x = (l + x) % n;

				prev_l = l;
				l = next(l);
				turn = 0;
			}
			cur += cross(g[prev_l], g[right]);
			if (cur == 48) {
				cout << i << " " << j << " " << k << " " << ((right + n - next(k) - 1) % n) << "\n" << "\n";
			}
			res = max(res, abs(cur));
		}
	}
	cout << res << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;
	while (t--)
		solve();
}
