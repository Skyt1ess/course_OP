#include <bits/stdc++.h>

using namespace std;

const int INF = INT_MAX;

struct edge {
    int from, to, cost;
};

void Dijkstra(int v,
              const vector<vector<pair<int, int>>> &G,
              vector<vector<int>> &dist,
              vector<vector<int>> &parent) {
    set<pair<int, int>> _set;

    _set.insert({dist[v][v], v});

    while (!_set.empty()) {
        int u = _set.begin()->second;
        _set.erase(_set.begin());

        for (int i = 0; i < G[u].size(); i++) {
            int to = G[u][i].first;
            int cost = G[u][i].second;

            if (dist[v][u] + cost < dist[v][to]) {
                _set.erase({dist[v][to], to});
                dist[v][to] = dist[v][u] + cost;
                parent[v][to] = u;
                _set.insert({dist[v][to], to});
            }

        }
    }
}

void Ford_Bellman(vector<edge> E,
                  vector<int> &potential) {
    int n = potential.size();
    vector<int> dist(n + 1, INF);
    dist[n] = 0;

    for (int i = 0; i < n; i++) {
        E.push_back(edge{n, i, 0});
    }

    for (int i = 0; i < dist.size(); i++) {
        for (int j = 0; j < E.size(); j++) {
            if (dist[E[j].from] != INF &&
                dist[E[j].to] > dist[E[j].from] + E[j].cost) {
                    dist[E[j].to] = dist[E[j].from] + E[j].cost;
                }
        }
    }

    for (int i = 0; i < n; i++) {
        potential[i] = dist[i];
    }
}

void Johnson(int n,
             const vector<edge> &E,
             vector<vector<int>> &dist,
             vector<vector<int>> &parent) {
    vector<int> potential(n);
    vector<vector<pair<int, int>>> new_G(n);

    Ford_Bellman(E, potential);

    for (int i = 0; i < E.size(); i++) {
        new_G[E[i].from].push_back({E[i].to, E[i].cost +
                                             potential[E[i].from] -
                                             potential[E[i].to]});
    }

    for (int i = 0; i < n; i++) {
        Dijkstra(i, new_G, dist, parent);
    }


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] != INF) {
                dist[i][j] -= potential[i] - potential[j];
            }
        }
    }
}

vector<int> return_way(int v,
               int u,
               const vector<vector<int>> &parent) {
    vector<int> way;
    for (int i = u; i != v; i = parent[v][i]) {
        way.push_back(i);
    }
    reverse(way.begin(), way.end());
    return way;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<edge> E(m);
    vector<vector<int>> dist(n, vector<int>(n, INF));
    vector<vector<int>> parent(n, vector<int>(n, -1));

    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
    }

    for (int i = 0; i < m; i++) {
        cin >> E[i].from >> E[i].to >> E[i].cost;

    }

    Johnson(n, E, dist, parent);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << dist[i][j] << ' ';
        }
        cout << endl;
    }

    int x, y;
    cin >> x >> y;

    vector<int> way = return_way(x, y, parent);
    for (int i = 0; i < way.size(); i++) {
        cout << way[i] << ' ';
    }

}
