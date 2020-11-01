/*
    Copyright (C) 2020, Sathira Silva.
    
    Link to the problem: https://csacademy.com/ieeextreme-practice/task/e610aba28810ebcf2d3998692269b5a0/
*/

#include <bits/stdc++.h>
 
using namespace std;

int dist[201][201], forest[201][201];
int r, c;

// For an initial health check whether the sum of values in the shortest path from (1, 1) to (r, c) is positive
// If it is positive Blue will be able to reach the Viridian city using that much of initial health of Pikachu
// The maximum sum shortest path can be found easily using dynamic programming:
int check(int health) {
    dist[0][0] = health;
    for (int i = 1; i < r; i++)
        dist[i][0] = dist[i - 1][0] > 0 ? dist[i - 1][0] + forest[i][0] : INT_MIN;
    for (int j = 1; j < c; j++)
        dist[0][j] = dist[0][j - 1] > 0 ? dist[0][j - 1] + forest[0][j] : INT_MIN;
    for (int i = 1; i < r; i++)
        for (int j = 1; j < c; j++) {
            int mx = max(dist[i - 1][j], dist[i][j - 1]);
            dist[i][j] = mx > 0 ? mx + forest[i][j] : INT_MIN;
        }
    return dist[r - 1][c - 1] > 0;
}

int main() {
    cin >> r >> c;
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            cin >> forest[i][j];
    int left = 0, right = INT_MAX, res;
    // Binary search for the minimum initial health
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (check(mid)) {
            res = mid;
            right = mid - 1;
        }
        else
            left = mid + 1;
    }
    cout << res;
}
