#include <bits/stdc++.h>

typedef long long ll;

const ll MOD = 1000000007;

using namespace std;

const int N = 10e6;

int sieve[N + 1];

void build()
{
	vector<int> ps;
	for (int i = 2; i <= N; i++) {
		if (sieve[i] == 0) {
			sieve[i] = i;
			ps.push_back(i);
		}
		for (auto p : ps) {
			int next = i * p;
			if (next > N) {
				break;
			}
			sieve[next] = p;
			if (p == sieve[i]) {
				break;
			}
		}
	}
}

int gcd(int a, int b)
{
	if (a < b)
		swap(a, b);
	while (b > 0) {
		tie(a, b) = make_pair(b, a % b);
	}
	return a;
}

void solve()
{
	int a, b;
	cin >> a >> b;
	int g = gcd(a, b);
	ll res = 1;
	while (g > 1) {
		int count = 0;
		int factor = sieve[g];
		while (g % factor == 0) {
			count++;
			g /= factor;
		}
		res *= count + 1;
	}
	cout << res << "\n";
}

int main()
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
