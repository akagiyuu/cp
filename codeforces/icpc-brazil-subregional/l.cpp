#include <bits/stdc++.h>
#include <bitset>
#include <vector>

using namespace std;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	int freqs[32] = { 0 };

	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		bitset<32> bits(x);
		for (int i = 0; i < 32; i++) {
			freqs[i] += bits[i];
		}
	}

	for (int i = 0; i < n; i++) {
		bitset<32> bits;
		for (int i = 0; i < 32; i++) {
			if (freqs[i] > 0) {
				freqs[i]--;
				bits[i] = 1;
			}
		}
		cout << bits.to_ulong() << " ";
	}
}
