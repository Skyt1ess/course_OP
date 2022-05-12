#include <bits/stdc++.h>

using namespace std;

const int MaxN = 50005;

int n, k;
vector< vector<int> > g(MaxN);
vector<int> done(MaxN, 0), child(MaxN, 0);
long long Res = 0;

void PdDFS(int u, int p)
{
    child[u] = 1;
    for (auto v : g[u])
    {
        if (done[v] == 1 || v == p )
        {
            continue;
        }
        PdDFS(v, u);
        child[u] = child[u] + child[v];
    }
}

int findCen(int u, int p, int sz)
{
    for (auto v : g[u])
    {
        if (done[v] == 1 || v == p)
        {
            continue;
        }
        if (child[v] * 2 >= sz)
        {
            return findCen(v, u, sz);
        }
    }
    return u;
}

void DFS(int u, int p, int depth, vector<int> &cnt, int add)
{
    if(depth > k)
    {
        return;
    }
    if (add == 1)
    {
        cnt[depth]++;
    }
    else
    {
        Res = Res + cnt[k - depth];
    }
    for (auto v : g[u])
    {
        if (done[v] == 1 || v == p)
        {
            continue;
        }
        DFS(v, u, depth + 1, cnt, add);
    }
}

void Solve(int u, int p)
{
    PdDFS(u, p);
    int sz = child[u];
    u = findCen(u, p, sz);
    vector<int> cnt(k + 1, 0);
    cnt[0] = 1;
    for (auto v : g[u])
    {
        if (done[v] == 1)
        {
            continue;
        }
        DFS(v, u, 1, cnt, 0);
        DFS(v, u, 1, cnt, 1);
    }
    done[u] = 1;
    for (auto v : g[u])
    {
        if (done[v] == 1)
        {
            continue;
        }
        Solve(v, u);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> k;
    int u, v;
    for (int i = 1; i < n; i++)
    {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    Res = 0;
    Solve(1, 1);
    cout << Res;
    return 0;
}
//https://codeforces.com/contest/161/problem/D
