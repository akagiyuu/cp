#include <bits/stdc++.h>
#include <cassert>

using namespace std;

#define int long long

const int N = 1024;

void print(const bitset<N> &a, int n)
{
	int j = 3;
	for (int i = 0; i < n; i++) {
		cout << a[j];
		j++;
		while (__builtin_popcount(j) == 1)
			j++;
	}
	cout << '\n';
}

void solve()
{
	string turn, s;
	int n;
	cin >> turn >> n >> s;
	if (turn == "first") {
		bitset<N> a(0);
		int j = 3;
		for (int i = 0; i < n; i++) {
			a.set(j, s[i] - '0');
			j++;
			while (__builtin_popcount(j) == 1)
				j++;
		}
		for (int i = 0; i < 10; i++) {
			int cur = 0;
			for (int j = 0; j < N; j++) {
				if ((j >> i) & 1)
					cur ^= a[j];
			}
			a.set(1ll << i, cur);
		}
		int cur = 0;
		for (int i = 1; i < N; i++) {
			cur ^= a[i];
		}
		a.set(0, cur);
		for (int i = 0; i < N; i++)
			cout << a[i];
		cout << '\n';
	} else {
		bitset<N> a(0);
		for (int i = 0; i < N; i++) {
			a.set(i, s[i] - '0');
		}
		int wrong = 0;
		for (int i = 0; i < 10; i++) {
			int cur = 0;
			for (int j = 0; j < N; j++) {
				if ((j >> i) & 1)
					cur ^= a[j];
			}
			if (cur)
				wrong |= (1ll << i);
		}
		int cur = 0;
		for (int i = 0; i < N; i++)
			cur ^= a[i];
		if (cur == 0 && wrong == 0) {
			cout << 0 << '\n';
			print(a, n);
			return;
		}
		if (cur == 0 && wrong != 0) {
			cout << 2 << '\n';
			return;
		}
		cout << 1 << '\n';
		a.flip(wrong);
		print(a, n);
		return;
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
