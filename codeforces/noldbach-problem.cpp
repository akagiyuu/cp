#include <bits/stdc++.h>

typedef long long ll;

const ll MOD = 1000000007;

using namespace std;

constexpr int N = 10001;

constexpr array<bool, N + 1> init()
{
	array<bool, N + 1> is_prime{};
	for (int i = 2; i <= N; i++) {
		is_prime[i] = true;
	}
	for (int i = 2; i <= N; i++) {
		if (!is_prime[i]) {
			continue;
		}
		for (int j = 2 * i; j <= N; j += i) {
			is_prime[j] = false;
		}
	}
	return is_prime;
}

constexpr array<bool, N + 1> is_prime = init();

bool solve()
{
	int n, k;
	cin >> n >> k;
	if (k == 0) {
		return true;
	}
	vector<int> ps;
	for (int i = 2; i <= n; i++) {
		if (is_prime[i]) {
			ps.push_back(i);
		}
	}
	for (int i = 0; i < ps.size() - 1; i++) {
		int v = ps[i] + ps[i + 1] + 1;
		if (v > n)
			break;
		if (is_prime[v]) {
			k--;
			if (k == 0) {
				return true;
			}
		}
	}

    return false;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cout << (solve() ? "YES" : "NO");
}
