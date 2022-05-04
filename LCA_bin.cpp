#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> g;
vector<vector<int>> parent;
vector<int> tin, tout;
int cnt = 0;

bool upper(int v, int u) {
	return tin[v] <= tin[u] && tout[v] >= tout[u];
}

int lca(int v, int u) {
	if (upper(v, u)) {
        return v;
	}
	if (upper(u, v)) {
        return u;
	}

	for (int i = parent[v].size() - 1; i >= 0; i--) {
        if (!upper(parent[v][i], u)) {
            v = parent[v][i];
        }
	}
	return parent[v][0];
}

void dfs(int v, int p = 0) {
    tin[v] = ++cnt;
	parent[v][0] = p;

	for (int i = 1; i < parent[v].size(); i++) {
        parent[v][i] = parent[parent[v][i-1]][i-1];
	}

	for (int i = 0; i < g[v].size(); i++) {
		int to = g[v][i];
		if (to != p) {
            dfs (to, v);
		}

	}
	tout[v] = ++cnt;
}

int main() {
    int n;
    cin >> n;

    g.resize(n);
    tin.resize(n);
    tout.resize(n);
    parent.resize(n);

    int k = 1;
    while (k * 2 <= n) {
        k++;
    }

    for (int i = 0; i < n; i++) {
        parent[i].resize(k + 1);
    }

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
