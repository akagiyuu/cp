#include <bits/stdc++.h>

#define int long long
#define pi pair<int, int>
#define fi first
#define se second

using namespace std;

const int N = 150;
const int INF = 1e18;
typedef array<bitset<N>, N> Matrix;

Matrix init(int n)
{
	Matrix res;
	for (int i = 0; i < n; i++) {
		res[i].reset();
	}
	return res;
}

Matrix id(int n)
{
	Matrix res;
	for (int i = 0; i < n; i++) {
		res[i].reset();
		res[i].set(i);
	}
	return res;
}

Matrix transpose(const Matrix &a, int n)
{
	Matrix res;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			res[i][j] = a[j][i];
		}
	}
	return res;
}

Matrix mul(const Matrix &a, const Matrix &b, int n)
{
	Matrix tb = transpose(b, n);
	Matrix res;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			res[i][j] = (a[i] & tb[j]).any();
		}
	}
	return res;
}

int solve()
{
	int n, m;
	cin >> n >> m;

	map<int, vector<pi> > raws;
	while (m--) {
		int a, b, d;
		cin >> a >> b >> d;
		a--;
		b--;
		raws[d].push_back({ a, b });
	}
	vector<pair<int, vector<pi> > > levels(raws.begin(), raws.end());
	levels.push_back({ INF, {} });
	int sz = levels.size();
	if (levels[0].fi > 0) {
		return -1;
	}
	int start = 0;
	int end = n - 1;

	Matrix reach;
	for (int i = 0; i < n; i++) {
		reach[i].set(i);
	}

	int k = -1;
	for (int i = 0; i < sz; i++) {
		for (auto [u, v] : levels[i].se) {
			if (reach[u].test(v))
				continue;
			for (int j = 0; j < n; j++) {
				if (reach[j].test(u))
					reach[j] |= reach[v];
			}
		}
		if (reach[start].test(end)) {
			k = i;
			break;
		}
	}
	if (k == -1)
		return -1;
	Matrix adj = init(n);
	for (auto [u, v] : levels[0].se) {
		adj[u].set(v);
	}
	Matrix transition = id(n);
	for (int i = 1; i <= k; i++) {
		int b = levels[i].fi - levels[i - 1].fi;

		Matrix tmp = adj;
		while (b) {
			if (b & 1)
				transition = mul(transition, tmp, n);
			tmp = mul(tmp, tmp, n);
			b >>= 1;
		}

		for (auto [u, v] : levels[i].se) {
			adj[u].set(v);
		}
	}
	for (int i = k + 1; i < sz; i++) {
		vector<vector<int> > d(n, vector<int>(n, INF));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (adj[i].test(j))
					d[i][j] = 1;
			}
		}
		for (int k = 0; k < n; k++) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
				}
			}
		}
		int b = levels[i].fi - levels[i - 1].fi;
		for (int j = 0; j < n; j++) {
			if (!transition[start].test(j))
				continue;
			b = min(b, d[j][end]);
		}
		int step = b;

		Matrix tmp = adj;
		while (b) {
			if (b & 1)
				transition = mul(transition, tmp, n);
			tmp = mul(tmp, tmp, n);
			b >>= 1;
		}
		if (transition[start].test(end))
			return levels[i - 1].fi + step;

		for (auto [u, v] : levels[i].se) {
			adj[u].set(v);
		}
	}

	return -1;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	auto res = solve();
	if (res == -1) {
		cout << "Impossible";
	} else {
		cout << res << "\n";
	}
}
