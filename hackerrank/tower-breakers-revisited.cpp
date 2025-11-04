#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 1e6 + 1;
unordered_set<int> gs[N];
int g[N];

int sum_pw(int n)
{
	int res = 0;
	for (int i = 2; i * i <= n; i++) {
		if (n % i != 0)
			continue;
		int pw = 0;
		while (n % i == 0) {
			n /= i;
			pw++;
		}
		res += pw;
	}
	if (n > 1)
		res++;
	return res;
}

void build()
{
	for (int i = 1; i < N; i++) {
		g[i] = sum_pw(i);
	}
}

bool solve()
{
	int n;
	cin >> n;
	int res = 0, tmp;
	while (n--) {
		cin >> tmp;
		res ^= g[tmp];
	}
	return res != 0;
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();

	int t;
	cin >> t;
	while (t--) {
		if (solve())
			cout << "1\n";
		else
			cout << "2\n";
	}
}
