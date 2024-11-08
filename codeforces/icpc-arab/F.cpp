#include <bits/stdc++.h>
using namespace std;

bool check_rows(const vector<vector<int>>& grid, int n) {
    for (int i = 0; i < n; i++) {
        set<int> row(grid[i].begin(), grid[i].end());
        if (row.size() != n || *row.begin() != 1 || *row.rbegin() != n) {
            return false;
        }
    }
    return true;
}

bool check_cols(const vector<vector<int>>& grid, int n) {
    for (int j = 0; j < n; j++) {
        set<int> col;
        for (int i = 0; i < n; i++) {
            col.insert(grid[i][j]);
        }
        if (col.size() != n || *col.begin() != 1 || *col.rbegin() != n) {
            return false;
        }
    }
    return true;
}

int main() {
    int n;
    cin >> n;
    vector<vector<int>> grid(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    if (check_rows(grid, n) && check_cols(grid, n)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}
