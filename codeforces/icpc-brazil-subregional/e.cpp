#include <bits/stdc++.h>

using namespace std;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	vector<vector<int> > grid(n, vector<int>(n, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}

	int horizontal_style = 0;
	for (int i = 0; i < n; i++) {
		if (horizontal_style != 0) {
			break;
		}

		int prev = grid[i][0];
		for (int j = 0; j < n; j++) {
			if (grid[i][j] > prev) {
				horizontal_style = 1;
				break;
			} else if (grid[i][j] < prev) {
				horizontal_style = 2;
				break;
			}
		}
	}

	int vertical_style = 0;
	for (int j = 0; j < n; j++) {
		if (vertical_style != 0) {
			break;
		}

		int prev = grid[0][j];
		for (int i = 0; i < n; i++) {
			if (grid[i][j] > prev) {
				vertical_style = 1;
				break;
			} else if (grid[i][j] < prev) {
				vertical_style = 2;
				break;
			}
		}
	}

	if (horizontal_style == 0 && vertical_style == 0) {
		cout << 0;
	} else if (horizontal_style == 0 && vertical_style == 1) {
		cout << 0;
	} else if (horizontal_style == 0 && vertical_style == 2) {
		cout << 2;
	} else if (horizontal_style == 1 && vertical_style == 0) {
		cout << 0;
	} else if (horizontal_style == 1 && vertical_style == 1) {
		cout << 0;
	} else if (horizontal_style == 1 && vertical_style == 2) {
		cout << 3;
	} else if (horizontal_style == 2 && vertical_style == 0) {
		cout << 2;
	} else if (horizontal_style == 2 && vertical_style == 1) {
		cout << 1;
	} else {
		cout << 2;
    }
}
