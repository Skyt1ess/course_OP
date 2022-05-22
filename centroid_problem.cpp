#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
using namespace std;

template<typename T>
using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;


long long n, L, W, ans = 0;
vector<vector<pair<int, int>>> g;
vector<pair<int, int>> tmp;
vector<int> _size, done, height, weight;

void init() {
    cin >> n >> L >> W;
    g.resize(n);
    _size.resize(n);
    done.resize(n);
    height.resize(n);
    weight.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int p, w;
        cin >> p >> w;
        g[--p].push_back({i + 1, w});
        g[i + 1].push_back({p, w});
    }
}

void dfs1(int u, int p) {
    _size[u] = 1;
    for (auto v: g[u]) {
        if (done[v.first] == 1 || v.first == p) {
            continue;
        }
        dfs1(v.first, u);
        _size[u] += _size[v.first];
    }
}

int findCen(int u, int p, int sz) {
    for (auto v: g[u]) {
        if (done[v.first] == 1 || v.first == p) {
            continue;
        }
        if (_size[v.first] * 2 >= sz) {
            return findCen(v.first, u, sz);
        }
    }
    return u;
}

void dfs2(int u, int p, int d, int w) {
    tmp.push_back({d, w});
    if (d <= L && w <= W) {
        ans++;
    }
    for (auto v: g[u]) {
        if (v.first != p && !done[v.first]) {
            dfs2(v.first, u, d + 1, w + v.second);
        }
    }
}

void solve(int u) {
    dfs1(u, -1);
    int sz = _size[u];
    u = findCen(u, -1, sz);
    done[u] = 1;
    vector<vector<pair<int, int>>> cur;
    for (auto v: g[u]) {
        if (done[v.first] == 1) {
            continue;
        }
        tmp.clear();
        dfs2(v.first, u, 1, v.second);
        cur.push_back(tmp);
    }
    vector<pair<int, int>> d;
    for (auto& x: cur) {
        sort(x.begin(), x.end());
        int l = 0;

        oset<pair<int, int>> s;
        for (int i = x.size() - 1; i >= 0; i--) {
            pair<int, int> y = x[i];
            while (l < d.size() && d[l].first <= L - y.first) {
                s.insert({d[l].second, l});
                l++;
            }
            ans += s.order_of_key({W - y.second, 1e9});
        }
        vector<pair<int, int>> res(x.size()+ d.size());
        merge(x.begin(), x.end(), d.begin(), d.end(), res.begin());
        d = res;

    }
    for (auto v: g[u]) {
        if (!done[v.first]) {
            solve(v.first);
        }
    }
}

int main() {
    init();
    solve(0);
    cout << ans;
}

//https://codeforces.com/contest/293/problem/E
