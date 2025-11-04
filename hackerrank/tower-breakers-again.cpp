#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 1e5 + 1;
int g[N];

int sum_pw(int n)
{
	int res = 0;
	for (int i = 2; i * i <= n; i++) {
		while (n % i == 0) {
			n /= i;
			res++;
		}
	}
	if (n > 1)
		res++;

	return res;
}

void build()
{
	g[1] = 0;
	for (int i = 2; i < N; i++) {
		int j = i;
		int cnt = 0;
		while (j % 2 == 0) {
			cnt++;
			j /= 2;
		}
		g[i] = sum_pw(j);
		if (cnt >= 1)
			g[i]++;
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
