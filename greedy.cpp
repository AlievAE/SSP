#pragma once

#include "greedy.h"

struct candidate {
    int A, B;
    int ov;
    bool operator < (const candidate& other) const {
        return ov > other.ov || (ov == other.ov && A < other.A) || 
               (ov == other.ov && A == other.A && B < other.B);
    }
};

string greedy(const vector<string>& S, bool adapted) {
    vector<string> curset = S;
    if (!adapted) {
        curset = erase_sub(curset);
    }
    int n = curset.size();
    vector<bool> used;
    used.assign(n, false);
    set<candidate> cand;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            cand.insert({i, j, overlap(curset[i], curset[j])});
        }
    }
    for (int i = n; i > 1; --i) {
        auto top = *(cand.begin());
        for (int j = 0; j < curset.size(); ++j) {
            if (!used[j]) {
                cand.erase({top.A, j, overlap(curset[top.A], curset[j])});
                cand.erase({top.B, j, overlap(curset[top.B], curset[j])});
                cand.erase({j, top.A, overlap(curset[j], curset[top.A])});
                cand.erase({j, top.B, overlap(curset[j], curset[top.B])});
            }
        }
        used[top.A] = true;
        used[top.B] = true;
        curset.push_back(merge(curset[top.A], curset[top.B]));
        used.push_back(false);
        int nw = curset.size() - 1;
        for (int j = 0; j < curset.size() - 1; ++j) {
            if (!used[j]) {
                cand.insert({nw, j, overlap(curset[nw], curset[j])});
                cand.insert({j, nw, overlap(curset[j], curset[nw])});
            }
        }
    }
    return curset.back();
}
