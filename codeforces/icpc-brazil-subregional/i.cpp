#include <bits/stdc++.h>
#include <bitset>
#include <unordered_map>
#include <vector>

using namespace std;

typedef unsigned long long ll;

ll primes[] = { 2,   3,	  5,   7,   11,	 13,  17,  19,	23,  29,  31,  37,  41,	 43,  47,  53,
		59,  61,  67,  71,  73,	 79,  83,  89,	97,  101, 103, 107, 109, 113, 127, 131,
		137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223,
		227, 229, 264, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311 };

ll MOD = 1000000007;
ll cached_pow = (1 << 63) % MOD;

ll fast_pow(int b, int p)
{
	ll result = 1;
	while (p > 0) {
		if (p % 2 == 1) {
			result *= b;
			result %= MOD;
		}

		b *= b;
		b %= MOD;
		p /= 2;
	}
	return result;
}

ll pow2(int p)
{
	ll result = fast_pow(cached_pow, p / 63);
	result *= (1 << (p % 63)) % MOD;
	result %= MOD;
	return result;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	vector<bitset<64> > factors(n);
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		bitset<64> factor;
		for (int j = 0; j < 64; j++) {
			if (x % primes[j] == 0) {
				factor[j] = 1;
			}
		}
		factors[i] = factor;
	}

	int q;
	cin >> q;
	unordered_map<bitset<64>, ll> cached;

	while (q--) {
		ll x;
		cin >> x;
		bitset<64> factor;
		for (int i = 0; i < 64; i++) {
			if (x % primes[i] == 0) {
				factor[i] = 1;
			}
		}
		if (cached.find(factor) != cached.end()) {
			cout << cached[factor] << "\n";
			continue;
		}
		int count = 0;
		for (int i = 0; i < n; i++) {
			if ((factors[i] & factor) == 0) {
				count += 1;
			}
		}
		cached[factor] = pow2(count);
		cout << cached[factor] << "\n";
	}
}
