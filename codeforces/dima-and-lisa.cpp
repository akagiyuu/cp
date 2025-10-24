#include <bits/stdc++.h>

using namespace std;

#define int long long
const int N = 1e5;

vector<int> pr;

void build()
{
	bool sieve[N];
	fill(sieve, sieve + N, true);
	for (int i = 2; i < N; i++) {
		if (!sieve[i])
			continue;
		pr.push_back(i);
		for (int j = 2 * i; j < N; j += i) {
			sieve[j] = false;
		}
	}
}

int binpow(int a, int d, int n)
{
	int res = 1;
	while (d) {
		if (d & 1)
			res = (res * a) % n;
		a = (a * a) % n;
		d >>= 1;
	}
	return res;
}

bool suspect(int a, int s, int d, int n)
{
	int x = binpow(a, d, n);
	if (x == 1)
		return true;
	for (int r = 0; r < s; ++r) {
		if (x == n - 1)
			return true;
		x = x * x % n;
	}
	return false;
}
bool is_prime(int n)
{
	if (n <= 1 || (n > 2 && n % 2 == 0))
		return false;
	int test[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, -1 };
	int d = n - 1, s = 0;
	while (d % 2 == 0)
		++s, d /= 2;
	for (int i = 0; test[i] < n && test[i] != -1; ++i)
		if (!suspect(test[i], s, d, n))
			return false;
	return true;
}

void solve()
{
	int n;
	cin >> n;

	if (is_prime(n)) {
		cout << 1 << "\n";
		cout << n << "\n";
		return;
	}

	n -= 3;
	for (auto p : pr) {
		if (p >= n)
			break;
		auto q = n - p;
		if (is_prime(q)) {
			cout << 3 << "\n";
			cout << 3 << " " << p << " " << q << "\n";
			break;
		}
	}
}

signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	build();

	solve();
}
