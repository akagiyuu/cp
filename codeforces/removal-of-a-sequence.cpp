#include <bits/stdc++.h>
using namespace std;
using int64 = long long;
const int64 N_LIMIT = (int64)1e12;

int64 solve_one() {
    int64 x, y, k;
    if (!(cin >> x >> y >> k)) return -1;
    if (y == 1) return -1;              // impossible (division by zero / unbounded growth)

    int64 B = y - 1;                    // we'll use B = y-1
    while (x > 0) {
        if (k < y)                       // k < y is a fixed point: prev(k,y) == k
            return k;
        // compute q = floor((k-1)/B) >= 1
        int64 q = (k - 1) / B;
        if (q == 0)                      // safety (shouldn't happen because k >= y)
            return k;

        // maximum k for this q is k_max = (q+1)*B
        long long k_max = (q + 1) * B;

        // how many steps we can take while q remains the same:
        // we need largest t such that k + t*q <= k_max
        // t = floor((k_max - k) / q)
        int64 t = (k_max - k) / q;

        // do at most x steps; if t >= x we finish by adding x*q
        if (t >= x) {
            // careful about overflow: all values <= N_LIMIT so safe with 128 if needed
            __int128 add = (__int128)q * x;
            k += (int64)add;
            x = 0;
            if (k > N_LIMIT) return -1;
            break;
        } else {
            // apply t steps in one go
            if (t > 0) {
                __int128 add = (__int128)q * t;
                k += (int64)add;
                x -= t;
                if (k > N_LIMIT) return -1;
            }
            // Now either t == 0 or we are at the boundary; perform one more single step
            if (x > 0) {
                k += q;
                --x;
                if (k > N_LIMIT) return -1;
            }
        }
    }
    return (k > N_LIMIT ? -1 : k);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        cout << solve_one() << "\n";
    }
    return 0;
}
