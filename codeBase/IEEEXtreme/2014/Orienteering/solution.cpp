/*
    Copyright (C) 2020, Sathira Silva.
    
    Link to the problem: https://csacademy.com/ieeextreme-practice/task/95352fd33b0e855d337b5b3ed85da3b6/
*/

#include <bits/stdc++.h>

using namespace std;

double r[601][601], h[601][601];

double calcTime(int ui, int uj, int vi, int vj) {
    return ((r[ui][uj] + r[vi][vj]) / 2.0) * exp(3.5 * abs(((h[vi][vj] - h[ui][uj]) / 10.0) + 0.05));
}

int main() {
    int n, m, p;
    cin >> n >> m >> p;
    vector<pair<int, int>> cp(p + 1);
    for (int i = 0; i <= p; i++)
        cin >> cp[i].first >> cp[i].second;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> r[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> h[i][j];
    double best = 0.0;
    int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    for (int point = 0; point < p; point++) {
        double dist[n][m];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                dist[i][j] = 1e9;
        set<pair<double, pair<int, int>>> q;
        int ux = cp[point].first, uy = cp[point].second;
        dist[ux][uy] = 0;
        q.insert({dist[ux][uy], {ux, uy}});
        while (!q.empty()) {
            ux = q.begin()->second.first, uy = q.begin()->second.second;
            q.erase(q.begin());
            for (int k = 0; k < 4; k++) {
                double t = calcTime(ux, uy, ux + dir[k][0], uy + dir[k][1]);
                if (ux + dir[k][0] >= 0 && ux + dir[k][0] < n && uy + dir[k][1] >= 0 && uy + dir[k][1] < m && dist[ux][uy] != 1e12 && dist[ux][uy] + t < dist[ux + dir[k][0]][uy + dir[k][1]]) {
                    dist[ux + dir[k][0]][uy + dir[k][1]] = dist[ux][uy] + calcTime(ux, uy, ux + dir[k][0], uy + dir[k][1]);
                    q.insert({dist[ux + dir[k][0]][uy + dir[k][1]], {ux + dir[k][0], uy + dir[k][1]}});
                }
            }
        }
        best += dist[cp[point + 1].first][cp[point + 1].second];
    }
    cout << ceil(best);
}
