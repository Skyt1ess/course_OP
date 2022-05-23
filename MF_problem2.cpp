#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Card {
    int p, c, l;
};

int n, k, s, t, ans = -1, sum = 0, N;
vector<vector<int>> g, flowPassed, cost;
vector<int> parList, currentPathCost;
vector<Card> card;
bool one;

bool check(int x) {
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}

void build(int l) {
    fill(g.begin(), g.end(), vector<int>());
    fill(cost.begin(), cost.end(), vector<int>(n));
    fill(flowPassed.begin(), flowPassed.end(), vector<int>(n));
    sum = 0;
    one = false;
    for (int i = 0; i < N; i++) {
        if (card[i].l > l || card[i].c == 1 && one) {
            continue;
        }
        sum += card[i].p;
        if (card[i].c == 1) {
            one = true;
        }
        if (card[i].c % 2) {
            g[s].push_back(i);
            g[i].push_back(s);

            cost[s][i] = card[i].p;
            for (int j = 0; j < N; j++) {
                if (check(card[i].c + card[j].c)){
                    g[i].push_back(j);
                    g[j].push_back(i);
                    cost[i][j] = 1e9;
                }
            }
        } else {
            g[i].push_back(t);
            g[t].push_back(i);
            cost[i][t] = card[i].p;
        }
    }
}


void init() {
    cin >> N >> k;
    s = N;
    t = N + 1;
    n = N + 2;
    card.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> card[i].p >> card[i].c >> card[i].l;

    }

    g.resize(n);
    flowPassed.resize(n);
    cost.resize(n);
    parList.resize(n);
    currentPathCost.resize(n);
    for (int i = 0; i < n; i++) {
        flowPassed[i].resize(n);
        cost[i].resize(n);
    }
/*
    for (int i = 0; i < m; i++) {
        int x, y, c;
        cin >> x >> y >> c;
        cost[x][y] = c;
        g[x].push_back(y);
        g[y].push_back(x);
    }*/
}



int bfs(int start, int finish) {
    fill(parList.begin(), parList.end(), -1);
    fill(currentPathCost.begin(), currentPathCost.end(), 0);

    queue<int> q;
    q.push(start);
    currentPathCost[start] = 1e9;


    while(!q.empty()) {
        int v = q.front();
        q.pop();

        for (int to: g[v]) {
            if (parList[to] == -1 &&
                cost[v][to] - flowPassed[v][to] > 0) {
                parList[to] = v;
                currentPathCost[to] = min(currentPathCost[v],
                                      cost[v][to] - flowPassed[v][to]);
                if (to == finish) {
                    return currentPathCost[finish];
                }
                q.push(to);
            }
        }
    }
    return 0;
}

int edmonds_karp(int start, int finish) {
    int ans = 0;
    while(true) {
        int flow = bfs(start, finish);
        if (flow == 0) {
            break;
        }
        ans += flow;
        int tmp = finish;
        while(tmp != start) {
            int prev = parList[tmp];
            flowPassed[prev][tmp] += flow;
            flowPassed[tmp][prev] -= flow;
            tmp = prev;
        }
    }
    return ans;
}

void solve() {
    int tmp = 1e9;
    for (int i = 0; i < N; i++) {
        if (card[i].p >= k) {
            tmp = min(tmp, card[i].l);
        }
    }
    for (int i = 1; i <= n; i++) {
        build(i);
        if (sum - edmonds_karp(s, t) >= k) {
            cout << i;
            return;
        }
    }
    cout << (tmp != 1e9?tmp:-1);
}
int main() {
    init();
    solve();
}
//https://codeforces.com/contest/808/problem/F

