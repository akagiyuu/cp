#include <bits/stdc++.h>

using namespace std;

int gcd(int a, int b)
{
	int new_a = max(a, b);
	int new_b = min(a, b);
	while (new_b != 0) {
		int temp = new_a % new_b;
		new_a = new_b;
		new_b = temp;
	}
	return new_a;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;

	if (n == 1) {
		cout << 1;
	} else {
		int a = 1;
		int b = 1;
		for (int i = 2; i <= n + 1; i++) {
			int c = a + b;
			a = b;
			b = c;
		}
		cout << a / gcd(a, b);
	}
}
