#include <bits/stdc++.h>

#define int long long

using namespace std;

const int MOD = 1e9 + 7;

static inline int add(int a, int b)
{
	int res = a + b;
	return res < MOD ? res : res - MOD;
}

static inline int sub(int a, int b)
{
	int res = a - b;
	return res < 0 ? res + MOD : res;
}

static inline int mul(int a, int b)
{
	return a * b % MOD;
}

pair<int, int> fib(int n)
{
	if (n == 0)
		return { 0, 1 };
	auto [a, b] = fib(n >> 1);
	int c = mul(a, sub(mul(2, b), a));
	int d = add(mul(a, a), mul(b, b));
	if (n & 1)
		return { d, add(c, d) };
	else
		return { c, d };
}

void solve()
{
	int n;
	cin >> n;
	cout << fib(n).first << "\n";
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
