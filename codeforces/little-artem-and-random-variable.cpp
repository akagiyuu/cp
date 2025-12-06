#include <bits/stdc++.h>

#define int long long
#define double long double

using namespace std;

const double INF = 1e18;
const double EPS = 1e-6;

pair<double, double> find_root(double a, double b, double c)
{
	double delta = b * b - 4 * a * c;
	if (delta < -EPS)
		return { -INF, -INF };
	double rt_delta = sqrtl(delta);
	return {
		(-b + rt_delta) / (2.L * a),
		(-b - rt_delta) / (2.L * a),
	};
}

vector<double> M, m, s, suffix, p;

bool backtrack(int i, double s_prob)
{
	if (i == -1) {
		return fabsl(s_prob - 1) < EPS;
	}
	auto root = find_root(-1, suffix[i + 1] - 2 * s_prob + s[i], s_prob * s[i] - m[i]);
	if (root.first >= -EPS && s[i] - root.first >= -EPS) {
		p[i] = root.first;
		if (backtrack(i - 1, s_prob + p[i]))
			return true;
	}
	if (root.second >= -EPS && s[i] - root.second >= -EPS) {
		p[i] = root.second;
		if (backtrack(i - 1, s_prob + p[i]))
			return true;
	}

	return false;
}

void solve()
{
	int n;
	cin >> n;
	M.resize(n);
	m.resize(n);
	s.resize(n);
	suffix.resize(n);
	p.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> M[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> m[i];
	}
	for (int i = 0; i < n; i++) {
		s[i] = M[i] + m[i];
	}
	suffix[n - 1] = s[n - 1];
	for (int i = n - 2; i >= 0; i--) {
		suffix[i] = suffix[i + 1] + s[i];
	}
	auto root = find_root(1.L, -s[n - 1], m[n - 1]);
	p[n - 1] = root.first;
	if(!backtrack(n - 2, p[n - 1])) {
		p[n - 1] = root.second;
		backtrack(n - 2, p[n - 1]);
	};

	for (int i = 0; i < n; i++) {
		cout << setprecision(10) << fabsl(p[i]) << " ";
	}
	cout << "\n";
	for (int i = 0; i < n; i++) {
		cout << setprecision(10) << fabsl(s[i] - p[i]) << " ";
	}
	cout << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
