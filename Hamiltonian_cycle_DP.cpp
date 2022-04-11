#include <bits/stdc++.h>

using namespace std;

void ham(bool& cycle,
         const vector<vector<int>>& g) {
    vector<vector<bool>> h(pow(2, g.size()), vector<bool>(g.size()));

    h[0][0] = true;

    for (int m = 0; m < pow(2, g.size()); m++) {
        for (int u = 0; u < g.size(); u++) {
            if (h[m][u]) {
                int nm = m | (1 << u);
                for (int v = 0; v < g.size(); v++) {
                    if (g[u][v]) {
                        if ((nm & (1 << v)) == 0) {
                            h[nm][v] = true;
                        }
                        if (v == 0 && nm == (1 << g.size()) - 1) {
                            cycle = true;
                        }
                    }

                }

            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n, vector<int> (n));


    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        g[x][y] = 1;
        g[y][x] = 1;
    }

    bool cycle = false;
    ham(cycle, g);

    cout << cycle;
}
