#include <bits/stdc++.h>

using namespace std;

int find_ans(int i, int mask,
              vector<vector<int>>& h,
              const vector<vector<int>>& g) {
    if (h[mask][i] != 1e9) {
        return h[mask][i];
    }

    for (int j = 0; j < g.size(); j++) {
        if (g[i][j] && (mask & (1 << j))) {
            h[mask][i] = min(h[mask][i], find_ans(j, mask - pow(2, j), h, g) + g[i][j]);
        }
    }

    return h[mask][i];
}

void find_way(const vector<vector<int>>& h,
              const vector<vector<int>>& g) {
    int i = 0;
    int mask = h.size() - 1;

    cout << i << ' ';

    while(mask) {
        for (int j = 0; j < g.size(); j++) {
            if (g[i][j] && (mask & (1 << j)) &&
                h[mask][i] == h[mask - pow(2, j)][j] + g[i][j]) {
                    i = j;
                    cout << i << ' ';
                    mask = mask - pow(2, j);
                    continue;
                }
        }
    }

}

void ham(const vector<vector<int>>& g) {
    vector<vector<int>> h(pow(2, g.size()), vector<int>(g.size(), 1e9));

    h[0][0] = 0;

    int ans = find_ans(0, pow(2, g.size()) - 1, h, g);
    cout << ans << endl;
    find_way(h, g);
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n, vector<int> (n));


    for (int i = 0; i < m; i++) {
        int x, y, cost;
        cin >> x >> y >> cost;
        g[x][y] = cost;
        g[y][x] = cost;
    }

    ham(g);
}

/*

4 6
0 1 20
0 2 42
0 3 35
1 2 30
1 3 34
2 3 12
*/
