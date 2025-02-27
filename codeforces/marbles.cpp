#include <bits/stdc++.h>
using namespace std;

const int MAX = 101;
int grundy[MAX][MAX];

// Function to calculate Grundy numbers for all positions
void computeGrundy() {
    for (int l = 0; l < MAX; ++l) {
        for (int c = 0; c < MAX; ++c) {
            set<int> reachable;
            for (int u = 1; u <= max(l, c); ++u) {
                if (l - u >= 0) reachable.insert(grundy[l - u][c]);      // Vertical move
                if (c - u >= 0) reachable.insert(grundy[l][c - u]);      // Horizontal move
                if (l - u >= 0 && c - u >= 0) reachable.insert(grundy[l - u][c - u]);  // Diagonal move
            }
            int g = 0;
            while (reachable.count(g)) ++g;  // mex calculation
            grundy[l][c] = g;
        }
    }
}

int main() {
    // Precompute Grundy numbers
    computeGrundy();

    int N;
    cin >> N;
    int xor_sum = 0;
    for (int i = 0; i < N; ++i) {
        int l, c;
        cin >> l >> c;
        xor_sum ^= grundy[l][c];
    }

    // If XOR is non-zero, the Emperor wins
    cout << (xor_sum != 0 ? "Y" : "N") << endl;

    return 0;
}
