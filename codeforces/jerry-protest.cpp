#include <bits/stdc++.h>
#include <iomanip>

using namespace std;

#define int long long

const int N = 5e3 + 7;

vector<int> multiply(const vector<int> &a, const vector<int> &b)
{
	int n = a.size(), m = b.size();
	vector<int> res(N, 0);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (i + j >= N)
				break;
			res[i + j] += a[i] * a[j];
		}
	}
	return res;
}

void solve()
{
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	vector<int> cnt(N, 0);
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++)
			cnt[abs(a[j] - a[i])]++;
	}
	auto cnt2 = multiply(cnt, cnt);
	double res = 0;
	double sum = cnt2[0];
	for (int i = 1; i < N; i++) {
		res += (double)cnt[i] * sum;
		sum += cnt2[i];
	}
	double sample = (double)n * (n - 1) / 2.;
	sample = pow(sample, 3);
	res /= sample;
	cout << fixed << setprecision(6) << res << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
