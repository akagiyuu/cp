#include <algorithm>
#include <bits/stdc++.h>

#define int long long
#define double long double

using namespace std;

const int N = 3;
const int M = 10;

const double T[N] = { 0.0L, 0.5L, 1.0L };
double POLY[N][M];
vector<double> PREFIX[M];
double C[M][M];

void build_taylor()
{
	for (int i = 0; i < N; i++) {
		POLY[i][0] = pow(1 + T[i], 0.5L);
	}

	for (int j = 1; j < M; j++) {
		double binom_diff = (3.0L - 2.0L * (double)j) / (2.0L * (double)j);
		for (int i = 0; i < N; i++) {
			POLY[i][j] = binom_diff * POLY[i][j - 1] / (1 + T[i]);
		}
	}
}

void build_prefix(const vector<double> &a)
{
	int n = a.size();
	for (int i = 0; i < M; i++) {
		PREFIX[i].assign(n, 0);
	}

	for (int j = 0; j < n; j++) {
		PREFIX[0][j] = 1;
		for (int i = 1; i < M; i++) {
			PREFIX[i][j] = PREFIX[i - 1][j] * a[j];
		}
	}
	for (int i = 0; i < M; i++) {
		for (int j = 1; j < n; j++) {
			PREFIX[i][j] += PREFIX[i][j - 1];
		}
	}
}

void build_nck()
{
	for (int i = 0; i < M; i++) {
		C[i][0] = 1;
		for (int j = 1; j <= i; j++) {
			C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
		}
	}
}

double sum_range(int l, int r, int pw)
{
	if (l == 0)
		return PREFIX[pw][r];
	return PREFIX[pw][r] - PREFIX[pw][l - 1];
}

double calc(double l, double r, double ai, double t, const double poly[M])
{
	if (l > r)
		return 0;
	double res = 0;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j <= i; j++) {
			double cur = poly[i] * C[i][j] * pow(-t, i - j) * sum_range(l, r, j) / pow(ai, j);
			res += cur;
		}
	}
	return res;
}

void solve()
{
	int n;
	cin >> n;
	vector<double> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	sort(a.begin(), a.end());
	build_taylor();
	build_prefix(a);
	build_nck();

	double res = 0;

	for (int i = 1; i < n; i++) {
		int m1 = upper_bound(a.begin(), a.end(), a[i] / 3.0L) - a.begin() - 1;
		int m2 = upper_bound(a.begin(), a.end(), a[i] * 2.0L / 3.0L) - a.begin() - 1;

		double cur = 0;
		cur += calc(0, m1, a[i], T[0], POLY[0]);
		cur += calc(m1 + 1, m2, a[i], T[1], POLY[1]);
		cur += calc(m2 + 1, i - 1, a[i], T[2], POLY[2]);
		cur *= sqrtl(a[i]);
		res += cur;
	}

	cout << fixed << setprecision(6) << res << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
