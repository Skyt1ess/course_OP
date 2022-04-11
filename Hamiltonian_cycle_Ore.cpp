#include <bits/stdc++.h>

using namespace std;

void ham(deque<int>& _deque,
         const vector<vector<int>>& g) {
    int n = g.size();
    for (int i = 0; i < n; i++) {
        _deque.push_back(i);
    }

    for (int i = 0; i < n * (n - 1); i++) {
        if (!g[_deque[0]][_deque[1]]) {
            int k = 2;
            while (!g[_deque[0]][_deque[k]] ||
                   !g[_deque[1]][_deque[k + 1]]) {
                k++;
            }
            for (int j = 1; j < (k + 1) / 2; j++) {
                swap(_deque[j], _deque[k - j + 1]);
            }
        }
        _deque.push_back(_deque[0]);
        _deque.pop_front();
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n, vector<int>(n));


    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        g[x][y] = 1;
        g[y][x] = 1;
    }

    deque<int> _deque;

    ham(_deque, g);

    for (int i = 0; i < _deque.size(); i++) {
        cout << _deque[i] << ' ';
    }
}
