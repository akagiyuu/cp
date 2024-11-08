#include <bits/stdc++.h>
#include <vector>

using namespace std;

bool solve(int start, int end, vector<int> &path, vector<bool> &is_visited, vector<vector<int> > &graph)
{
	if (start == end) {
		return true;
	}

	int n = graph.size();
	for (int i = 0; i < n; i++) {
		if (graph[start][i] == 0 || is_visited[i]) {
			continue;
		}
		path.push_back(i);
		is_visited[i] = true;
		if (solve(i, end, path, is_visited, graph)) {
			return true;
		}
		path.pop_back();
		is_visited[i] = false;
	}

	return false;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, movie_count;
	cin >> movie_count >> n;
	vector<vector<int> > graph(n, vector<int>(n, 0));

	for (int movie_index = 1; movie_index <= movie_count; movie_index++) {
		int n;
		cin >> n;
		vector<int> actors(n);
		for (int i = 0; i < n; i++) {
			cin >> actors[i];
			actors[i]--;
		}
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				graph[actors[i]][actors[j]] = movie_index;
				graph[actors[j]][actors[i]] = movie_index;
			}
		}
	}

	// for (int i = 0; i < n; i++) {
	// 	for (int j = 0; j < n; j++) {
	// 		cout << i << "," << j << " -> " << graph[i][j] << "\n";
	// 	}
	// }

	int q;
	cin >> q;
	while (q--) {
		int start, end;
		cin >> start >> end;
		start--;
		end--;
		vector<int> path;
		// path.push_back(start);
		vector<bool> is_visited(graph.size(), false);
		is_visited[start] = true;
		if (!solve(start, end, path, is_visited, graph)) {
			cout << -1 << "\n";
			continue;
		}

		cout << path.size() + 1 << "\n";
        cout << start + 1 << " ";
		int pre = start;
		for (auto x : path) {
			cout << graph[pre][x] << " " << x + 1 << " ";
            pre = x;
		}
		cout << "\n";
	}
}
