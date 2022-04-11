#include <bits/stdc++.h>

using namespace std;

int cnt = 0;
int ans = false;
int start = 0;
vector<int> path;
vector<bool> visited;
vector<vector<int>> g;

void ham(int v) {
    visited[v] = true;
    cnt++;
    for (int i = 0; i < g[v].size(); i++) {
        if (!visited[g[v][i]]) {
            ham(g[v][i]);
        }
        if (g[v][i] == start && cnt == g.size()) {
            ans = true;
        }
        if (ans) {
            path.push_back(g[v][i]);
            return;
        }
    }
    visited[v] = false;
    cnt--;
}

int main() {
    int n, m;
    cin >> n >> m;
    g.resize(n);
    visited.resize(n);

    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        //g[y].push_back(x);
    }

    ham(start);
    reverse(path.begin(), path.end());
    for (int i = 0; i < path.size(); i++) {
        cout << path[i] << ' ';
    }

}
