#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> g;
vector<int> parent, depth;

int lca(int x, int y) {
    while(x != y) {
        if (depth[x] < depth[y]) {
            swap(x, y);
        }
        x = parent[x];
    }
    return x;
}

void dfs(int v) {
    for (int i = 0; i < g[v].size(); i++) {
        int to = g[v][i];
        if (to == parent[v]) {
            continue;
        }
        parent[to] = v;
        depth[to] = depth[v] + 1;
        dfs(to);
    }
}

int main() {
    int n;
    cin >> n;

    g.resize(n);
    parent.resize(n, -1);
    depth.resize(n);

    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        g[--x].push_back(--y);
        g[y].push_back(x);
    }

    dfs(0);

    int m;
    cin >> m;

    while(m--) {
        int x, y;
        cin >> x >> y;
        cout << lca(--x, --y) + 1 << endl;
    }

}
