#pragma once

#include "jiang.h"

vector<int> assignment_hungary(int n, int m, const vector<vector<int>>& graph) {
    int INF = 1000000;
    int a[n+1][m+1];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            a[i+1][j+1] = -graph[i][j];
        }
    }
    vector<int> u (n+1), v (m+1), p (m+1), way (m+1);
    for (int i=1; i<=n; ++i) {
        p[0] = i;
        int j0 = 0;
        vector<int> minv (m+1, INF);
        vector<char> used (m+1, false);
        do {
            used[j0] = true;
            int i0 = p[j0],  delta = INF,  j1;
            for (int j=1; j<=m; ++j)
                if (!used[j]) {
                    int cur = a[i0][j]-u[i0]-v[j];
                    if (cur < minv[j])
                        minv[j] = cur,  way[j] = j0;
                    if (minv[j] < delta)
                        delta = minv[j],  j1 = j;
                }
            for (int j=0; j<=m; ++j)
                if (used[j])
                    u[p[j]] += delta,  v[j] -= delta;
                else
                    minv[j] -= delta;
            j0 = j1;
        } while (p[j0] != 0);
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
	    } while (j0);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            a[i+1][j+1] *= -1;
        }
    }
    vector<int> ans (n);
    for (int j=1; j<=m; ++j) {
        ans[p[j] - 1] = j - 1;
    }
    return ans;
}

vector<int> assignment_greedy(int n, const vector<vector<int>>& graph) {
    vector<pair<int, int>> coord;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            coord.push_back({i, j});
        }
    }
    auto sort_comp = [graph] (const pair<int, int>& p1, const pair<int, int>& p2) -> bool
    {
       return graph[p1.first][p1.second] > graph[p2.first][p2.second];
    };
    sort(coord.begin(), coord.end(), sort_comp);
    bool hor[n], vert[n];
    for (int i = 0; i < n; ++i) {
        hor[i] = false;
        vert[i] = false;
    }
    vector<int> result(n);
    for (auto [x, y] : coord) {
        if (!hor[x] && !vert[y]) {
            hor[x] = true;
            vert[y] = true;
            result[x] = y;
        }
    }
    return result;
}


string jiang(const vector<string>& S, bool adapted) {
    
    auto S_adapted = S;
    if (!adapted) {
        S_adapted = erase_sub(S_adapted);
    }   
    int n = S_adapted.size();
    vector<vector<int>> ov(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ov[i].push_back(overlap(S_adapted[i], S_adapted[j]));
        }
    }
    auto assignment = assignment_greedy(n, ov);
    bool used[n];
    for (int i = 0; i < n; ++i) used[i] = 0;
    vector<string> perm;
    for (int i = 0; i < n; ++i) {
        if (used[i]) continue;
        int mn = i;
        int cur = assignment[i];
        int cnt = 0;
        while (cur != i) {
            if (ov[mn][assignment[mn]] > ov[cur][assignment[cur]]) {
                mn = cur;
            }
            cur = assignment[cur];
        }

        int start = assignment[mn];
        do {
            used[start] = true;
            perm.push_back(S_adapted[start]);   
            start = assignment[start];
        } while (start != assignment[mn]);
    }
    return merge(perm);
}