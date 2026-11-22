#include <bits/stdc++.h>

using namespace std;

#define int long long

const int MOD = 1000000007;
const int N = 2007;

int fact[N], ifact[N];

int add(int x, int y)
{
	x += y;
	if (x >= MOD)
		x -= MOD;
	return x;
}
int sub(int x, int y)
{
	x -= y;
	if (x < 0)
		x += MOD;
	return x;
}
int powmod(int x, int e)
{
	int r = 1;
	while (e) {
		if (e & 1)
			r = r * x % MOD;
		x = x * x % MOD;
		e >>= 1;
	}
	return r;
}
int inverse(int x)
{
	return powmod(x, MOD - 2);
}

void build()
{
	fact[0] = 1;
	for (int i = 1; i < N; i++)
		fact[i] = fact[i - 1] * i % MOD;
	ifact[N - 1] = inverse(fact[N - 1]);
	for (int i = N - 2; i >= 0; i--)
		ifact[i] = ifact[i + 1] * (i + 1) % MOD;
}
int C(int n, int k)
{
	if (k < 0 || k > n)
		return 0;
	return fact[n] * ifact[n - k] % MOD * ifact[k] % MOD;
}

struct dat {
	int x, y, b;
};
struct range {
	int x1, y1, x2, y2;
};

void solve()
{
	int n, m, r;
	cin >> n >> m >> r;
	vector<dat> s(n);
	vector<vector<int> > pcnt(N, vector<int>(N, 0));
	for (int i = 0; i < n; i++) {
		cin >> s[i].x >> s[i].y >> s[i].b;
		s[i].x--;
		s[i].y--;
		pcnt[s[i].x][s[i].y] = 1;
	}
	for (int x = 0; x < N; x++) {
		for (int y = 0; y < N; y++) {
			if (x > 0)
				pcnt[x][y] = add(pcnt[x][y], pcnt[x - 1][y]);
			if (y > 0)
				pcnt[x][y] = add(pcnt[x][y], pcnt[x][y - 1]);
			if (x > 0 && y > 0)
				pcnt[x][y] = sub(pcnt[x][y], pcnt[x - 1][y - 1]);
		}
	}
	auto get = [&](const range &b) {
		auto [x1, y1, x2, y2] = b;
		if (x1 > x2 || y1 > y2)
			return 0ll;
		int res = pcnt[x2][y2];
		if (x1 > 0)
			res = sub(res, pcnt[x1 - 1][y2]);
		if (y1 > 0)
			res = sub(res, pcnt[x2][y1 - 1]);
		if (x1 > 0 && y1 > 0)
			res = add(res, pcnt[x1 - 1][y1 - 1]);
		return res;
	};
	auto get_range = [&](int i) -> range {
		int x1 = max(s[i].x - r, 0ll);
		int y1 = max(s[i].y - r, 0ll);

		int x2 = min(s[i].x + r, N - 1);
		int y2 = min(s[i].y + r, N - 1);
		return { x1, y1, x2, y2 };
	};

	int total_cnt = C(n, m);
	int res = 0;
	for (int i = 0; i < n; i++) {
		int cnt = sub(total_cnt, C(n - get(get_range(i)), m));
		res = add(res, s[i].b * s[i].b % MOD * cnt % MOD);
	}
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			int cnt = total_cnt;

			auto ri = get_range(i);
			cnt = sub(cnt, C(n - get(ri), m));

			auto rj = get_range(j);
			cnt = sub(cnt, C(n - get(rj), m));

			range r = {
				.x1 = max(ri.x1, rj.x1),
				.y1 = max(ri.y1, rj.y1),
				.x2 = min(ri.x2, rj.x2),
				.y2 = min(ri.y2, rj.y2),
			};
			cnt = add(cnt, C(n - get(ri) - get(rj) + get(r), m));
			res = add(res, 2 * cnt % MOD * s[i].b % MOD * s[j].b % MOD);
		}
	}

	cout << res << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();
	solve();
}
