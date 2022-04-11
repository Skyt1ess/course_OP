#include <bits/stdc++.h>

using namespace std;

int cnt = 0;
int ans = INT_MAX;
int start = 0;
vector<int> path;
vector<int> visited;
vector<vector<pair<int, int>>> g;

void ham(int v, int sum) {
    visited[v] = ++cnt;

    for (int i = 0; i < g[v].size(); i++) {
        if (!visited[g[v][i].first]) {
            ham(g[v][i].first, sum + g[v][i].second);
        }
        if (g[v][i].first == start && cnt == g.size() && ans > sum + g[v][i].second) {
            ans = sum + g[v][i].second;
            cout << ans << endl;
            path = visited;
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
        int x, y, cost;
        cin >> x >> y >> cost;
        g[x].push_back({y, cost});
        g[y].push_back({x, cost});
    }

    ham(start, 0);

    for (int i = 0; i < path.size(); i++) {
        cout << path[i] << ' ';
    }

}
