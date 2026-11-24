#include <bits/stdc++.h>
#include <cassert>

using namespace std;

#define int long long
#define double long double

double C(int n, int k)
{
	if (k < 0 || k > n)
		return 0;
	if (n - k < k)
		k = n - k;
	double res = 1;
	for (int i = 1; i <= k; i++)
		res = res * (double)(n - k + i) / i;
	return res;
}

void solve()
{
	int n, m, k;
	cin >> n >> m >> k;
	double total = C(n, m);

	vector<bool> ok(n + 1, false);
	queue<int> q;
	ok[k] = true;
	q.push(k);
	while (!q.empty()) {
		int x = q.front();
		q.pop();

		int l = max(0ll, m - (n - x));
		int r = min(x, m);

		for (double t = l; t <= r; t++) {
			int y = x + m - 2 * t;
			if (ok[y])
				continue;

			ok[y] = true;
			q.push(y);
		}
	}

	vector<vector<double> > A;
	vector<int> left, right;
	vector<int> id(n + 1, -1);
	auto normalize = [&](int i) {
		while (!A[i].empty() && A[i][0] == 0) {
			A[i].erase(A[i].begin());
			left[i]++;
		}
	};
	for (int x = 0; x <= n; x++) {
		if (x == k || !ok[x])
			continue;

		id[x] = A.size();
		left.push_back(max(x - m, 0ll));
		right.push_back(min(x + m, n));
		int l = left.back();
		int r = right.back();

		vector<double> eq(r - l + 1, 0);
		eq[x - l] = 1;
		for (double t = m; t >= 0; t--) {
			double p = C(x, t) * C(n - x, m - t) / total;
			int y = x + m - 2 * t;
			if (y < l || y > r)
				continue;

			if (y == k)
				eq[y - l] = 0;
			else
				eq[y - l] -= p;
		}
		A.push_back(eq);
		normalize(A.size() - 1);
	}

	vector<double> b(n, 1);
	for (int x = 0; x <= n; x++) {
		if (x == k || !ok[x])
			continue;

		int i = id[x];
		assert(left[i] == x);

		double p = A[i][0];
		int len = A[i].size();
		for (int j = 0; j < len; j++)
			A[i][j] /= p;
		b[i] /= p;

		for (int y = x + 1; y <= min(n, x + m); y++) {
			if (y == k || !ok[y])
				continue;

			int j = id[y];
			if (left[j] != x)
				continue;

			double c = A[j][0];
			for (int q = 0; q < len; q++)
				A[j][q] -= A[i][q] * c;
			b[j] -= b[i] * c;

			normalize(j);
		}
	}
	vector<double> f(n + 1, 0);
	for (int x = n; x >= 0; x--) {
		if (x == k || !ok[x])
			continue;

		int i = id[x];
		assert(left[i] == x);
		assert(A[i][0] == 1);

		int sz = A[i].size();
		f[left[i]] = b[i];
		for (int j = 1; j < sz; j++)
			f[left[i]] -= f[j + left[i]] * A[i][j];
	}
	for (int i = 0; i <= n; i++) {
		if (!ok[i])
			f[i] = 0;
		else
			f[i] += 1;
	}
	// for (int i = 0; i <= n; i++) {
	// 	cout << i << ' ' << f[i] << '\n';
	// }
	vector<double> w(n + 1);
	int mid = n / 2;
	w[mid] = 1;
	for (int i = mid + 1; i <= n; i++)
		w[i] = w[i - 1] * (n - i + 1) / i;
	for (int i = mid - 1; i >= 0; i--)
		w[i] = w[i + 1] * (i + 1) / (n - i);
	double sum = 0;
	for (int i = 0; i <= n; i++)
		sum += w[i];
	double res = 0;
	for (int i = 0; i <= n; i++)
		res += w[i] * f[i];
	res /= sum;
	cout << fixed << setprecision(10) << res << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
