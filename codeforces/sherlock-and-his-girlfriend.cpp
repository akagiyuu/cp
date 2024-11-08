#include <bits/stdc++.h>

typedef long long ll;

const ll MOD = 1000000007;

using namespace std;

constexpr int N = 100001;

constexpr array<bool, N + 1> init()
{
	array<bool, N + 1> is_prime{ false };
	for (int i = 2; i <= N; i++) {
		is_prime[i] = true;
	}
	for (int i = 2; i <= N; i++) {
		if (!is_prime[i]) {
			continue;
		}
		for (int j = i * 2; j <= N; j += i) {
			is_prime[j] = false;
		}
	}
	return is_prime;
}

constexpr array<bool, N + 1> is_prime = init();

void solve()
{
	int n;
	cin >> n;
    if(n == 1) {
        cout << "1\n1\n";
        return;
    }
    if(n == 2) {
        cout << "1\n1 1\n";
        return;
    }
	cout << "2\n";
	for (int i = 2; i <= n + 1; i++) {
		cout << (is_prime[i] ? 1 : 2) << " ";
	}
	cout << "\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	solve();
}
