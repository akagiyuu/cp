#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = 1e9;
const int N = 1e6;

vector<ll> pr;
int lp[N];

void build()
{
	for (ll i = 2; i < N; i++) {
		if (lp[i] == 0) {
			lp[i] = i;
			pr.push_back(i);
		}
		for (ll j = 0; i * pr[j] < N; j++) {
			lp[i * pr[j]] = pr[j];
			if (pr[j] == lp[i])
				break;
		}
	}
}

void print_edge(int i, int j, int w)
{
	cout << i << " " << j << " " << w << "\n";
}

void solve()
{
	int n, m;
	cin >> n >> m;

	ll sum = *upper_bound(pr.begin(), pr.end(), n - 2);
	cout << sum << " " << sum << "\n";
	for (ll i = 0; i < n - 2; i++) {
		print_edge(i + 1, i + 2, 1);
	}
	print_edge(n - 1, n, sum - n + 2);

	m -= n - 1;
	for (int i = 0; i < n; i++) {
		for (int j = i + 2; j < n; j++) {
			if (m == 0)
				break;
			print_edge(i + 1, j + 1, INF);
			m--;
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();
	solve();
}
