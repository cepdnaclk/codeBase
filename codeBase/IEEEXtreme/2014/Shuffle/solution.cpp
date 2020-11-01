/*
    Copyright (C) 2020, Sathira Silva.
    
    Link to the problem: https://csacademy.com/ieeextreme-practice/task/0186cd4b3a330dc501606737e090e0da/
*/

#include <bits/stdc++.h>

using namespace std;

int leftMatch[202], rightMatch[202], level[202];
vector<vector<int>> adj;

bool bfs() {
    int n = adj.size() - 1;
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (leftMatch[i] == n) {
            level[i] = 0;
            q.push(i);
        }
        else
            level[i] = INT_MAX;
    }
    level[n] = INT_MAX;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (level[u] < level[n]) {
            for (int v : adj[u])
                if (level[rightMatch[v]] == INT_MAX) {
                    level[rightMatch[v]] = level[u] + 1;
                    q.push(rightMatch[v]);
                }
        }
    }
    return level[n] != INT_MAX;
}

bool dfs(int u) {
    int n = adj.size() - 1;
    if (u != n) {
        for (int v : adj[u])
            if (level[rightMatch[v]] == level[u] + 1)
                if (dfs(rightMatch[v])) {
                    rightMatch[v] = u;
                    leftMatch[u] = v;
                    return true;
                }
        level[u] = INT_MAX;
        return false;
    }
    return true;
}

int main() {
    int n;
    cin >> n;
    cin.ignore();
    // Build the residual graph
    bool residual[n][n];
    memset(residual, false, sizeof(residual));
    for (int i = 0; i < n; i++) {
        string s;
        getline(cin, s);
        stringstream ss(s);
        int j;
        while (ss >> j)
            residual[i][j] = true;
        residual[i][i] = true;
    }
    // Build the graph using the residual graph
    adj.resize(n + 1);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (!residual[i][j])
                adj[i].push_back(j);
    // Hopcroft - Carp Maximum Bipartite matching algorithm
    for (int i = 0; i <= n; i++)
        leftMatch[i] = rightMatch[i] = n;
    int matched = 0;
    while (bfs()) {
        for (int i = 0; i < n; i++)
            if (leftMatch[i] == n && dfs(i))
                matched++;
    }
    cout << n - matched;
}
