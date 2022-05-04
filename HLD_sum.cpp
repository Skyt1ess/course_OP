#pragma comment(linker,"/STACK:100000000000,100000000000")

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#include <cmath>
#include <map>
#include <stack>
#include <set>
#include <iomanip>
#include <queue>
#include <map>
#include <functional>
#include <list>
#include <sstream>
#include <ctime>
#include <climits>
#include <bitset>
#include <list>
#include <cassert>
#include <complex>

using namespace std;

int n;
vector<int> t, _size, parent, depth, heavy, arr, num, top;
vector<vector<int>> g;


void dfs(int v) {
    _size[v] = 1;
    for (int i = 0; i < g[v].size(); i++) {
        int to = g[v][i];
        if (to == parent[v]) {
            continue;
        }
        parent[to] = v;
        depth[to] = depth[v] + 1;
        dfs(to);
        _size[v] += _size[to];
        if (heavy[v] == -1 || _size[to] > _size[heavy[v]]) {
            heavy[v] = to;
        }
    }
}


void hld(int v) {
    num[v] = arr.size();
    arr.push_back(v + 1);
    if (heavy[v] != -1) {
        top[heavy[v]] = top[v];
        hld(heavy[v]);
    }

    for (int i = 0; i < g[v].size(); i++) {
        int to = g[v][i];
        if (to == parent[v] || to == heavy[v]) {
            continue;
        }
        top[to] = to;
        hld(to);
    }
}

int func(int a, int b) {
    return a + b;
}

void create_tree(int v, int l, int r) {
    if (l == r) {
        t[v] = arr[l];
        return;
    }

    int m = (l + r) / 2;
    create_tree(v * 2 + 1, l, m);
    create_tree(v * 2 + 2, m + 1, r);
    t[v] = func(t[v * 2  + 1], t[v * 2 + 2]);
}


int func_tree(int v, int vl, int vr, int L, int R) {
    if (L > R) {
        swap(L, R);
    }
    if (R < vl || L > vr) {
        return 0;
    }
    if (vl >= L && R >= vr) {
        return t[v];
    }

    int m = (vl + vr) / 2;
    return func(func_tree(v * 2 + 1, vl, m, L, R),
           func_tree(v * 2 + 2, m + 1, vr, L, R));
}

int result(int x, int y) {
    int ans = 0;
    while (top[x] != top[y]) {
        if (depth[top[x]] < depth[top[y]]) {
            swap(x, y);
        }
        int start = top[x];
        ans = func(ans, func_tree(0, 0, n - 1, num[start], num[x]));
        x = parent[start];
    }

    ans = func(ans, func_tree(0, 0, n - 1, num[x], num[y]));
    return ans;
}

void update(int v, int vl, int vr, int pos, int val) {
    if (vl == vr) {
        t[v] += val;
        return;
    }
    int m = (vl + vr) / 2;
    if (pos <= m) {
        update(v * 2 + 1, vl, m, pos, val);
    } else {
        update(v * 2 + 2, m + 1, vr, pos, val);
    }
    t[v] = func(t[v * 2 + 1], t[v * 2 + 2]);
}

int main() {
    cin >> n;
    t.resize(n * 4, 0);
    g.resize(n, vector<int>());
    parent.resize(n, -1);
    heavy.resize(n, -1);
    _size.resize(n, 0);
    depth.resize(n, 0);
    num.resize(n, 0);
    top.resize(n, 0);

    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        g[--x].push_back(--y);
        g[y].push_back(x);
    }

    dfs(0);
    hld(0);
    create_tree(0, 0, n - 1);
    /*
    int k = 1;
    for (int i = 0; i < t.size(); i++) {
        for (int j = 0; j < k; j++) {
            cout << t[i + j] << ' ';
        }
        i = i + k - 1;
        k *= 2;
        cout << endl;
    }

    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << ' ';
    }
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << i << ": " << nxt[i] << ' ' << top[i] << ' ' << num[i] << ' ' << depth[i] << ' ' << parent[i] << endl;
    }
    */

    int m;
    cin >> m;
    while(m--){
        int x, y;
        cin >> x >> y;
        result(--x, --y) << endl;
    }

}
