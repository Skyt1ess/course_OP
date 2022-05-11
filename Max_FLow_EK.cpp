#include<cstdio>
#include<queue>
#include<cstring>
#include<vector>
#include<iostream>

using namespace std;

vector<vector<int>> g, flowPassed, c;
vector<int> parList, currentPathC;

int bfs(int sNode, int eNode) {
    fill(parList.begin(), parList.begin() + parList.size(), -1);
    fill(currentPathC.begin(), currentPathC.begin() + currentPathC.size(), 0);

    queue<int> q;//declare queue vector
    q.push(sNode);
    parList[sNode] = -1;//initialize parlist’s source node
    currentPathC[sNode] = 999;//initialize currentpath’s source node
    while(!q.empty()) {
        int currNode = q.front();
        q.pop();
        for(int i=0; i<g[currNode].size(); i++) {
            int to = g[currNode][i];
            if(parList[to] == -1) {
                if(c[currNode][to] - flowPassed[currNode][to] > 0) {
                    parList[to] = currNode;
                    currentPathC[to] = min(currentPathC[currNode],
                    c[currNode][to] - flowPassed[currNode][to]);
                    if(to == eNode) {
                        return currentPathC[eNode];
                    }
                    q.push(to);
                }
            }
        }
    }
    return 0;
}


int edmondsKarp(int sNode, int eNode) {
    int maxFlow = 0;
    while(true) {
        int flow = bfs(sNode, eNode);
        if (flow == 0) {
            break;
        }
        maxFlow += flow;
        int currNode = eNode;
        while(currNode != sNode) {
            int prevNode = parList[currNode];
            flowPassed[prevNode][currNode] += flow;
            flowPassed[currNode][prevNode] -= flow;
            currNode = prevNode;
        }
    }
    return maxFlow;
}


int main() {
    int nodCount, edCount;
    cin >> nodCount >> edCount;

    g.resize(nodCount);
    flowPassed.resize(nodCount);
    c.resize(nodCount);
    parList.resize(nodCount);
    currentPathC.resize(nodCount);

    for (int i = 0; i < nodCount; i++) {
        flowPassed[i].resize(nodCount);
        c[i].resize(nodCount);
    }

    int source, sink;
    cin >> source >> sink;

    for(int ed = 0; ed < edCount; ed++) {
        int from, to, cap;
        cin >> from >> to >> cap;
        c[from][to] = cap;
        g[from].push_back(to);
        g[to].push_back(from);
    }

    int maxFlow = edmondsKarp(source, sink);
    cout << maxFlow << endl;
}
