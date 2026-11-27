#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 1e6 + 7;
const int INF = 1e12;

int mu[N];
vector<int> divisors[N];

void build()
{
	mu[1] = 1;
	for (int i = 1; i < N; i++)
		for (int j = 2 * i; j < N; j += i)
			mu[j] -= mu[i];
	for (int i = 1; i < N; i++)
		for (int j = i; j < N; j += i)
			divisors[j].push_back(i);
}

int f(int x, int p)
{
	int res = 0;
	for (auto d : divisors[p])
		res += mu[d] * (x / d);
	return res;
}

void solve()
{
	int x, p, k;
	cin >> x >> p >> k;
	int s = k + f(x, p);

	int l = x, r = INF;
	while (l < r) {
		int mid = l + (r - l) / 2;
		if (f(mid, p) >= s)
			r = mid;
		else
			l = mid + 1;
	}

	cout << l << '\n';
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();

	int t;
	cin >> t;
	while (t--)
		solve();
}
